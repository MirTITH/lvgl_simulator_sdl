#include "lvgl_thread.h"
#include "lvgl.h"
#include <mutex>
#include "FreeRTOS.h"
#include "lvgl_app.hpp"
#include "test_app.hpp"
#include <chrono>

using namespace std;

static std::mutex LvglMutex;

lv_style_t PAGE_STYLE;

void LvglLock()
{
    LvglMutex.lock();
}

void LvglUnlock()
{
    LvglMutex.unlock();
}

static void LvglAppRunnerEntry(void *argument)
{
    auto app = (LvglApp *)argument;
    LvglLock();
    switch (app->app_type) {
    case LvglAppType::Window:
        app->app_screen = lv_obj_create(lv_scr_act());
        lv_obj_remove_style_all(app->app_screen);
        lv_obj_add_style(app->app_screen, &PAGE_STYLE, 0);
        break;
    case LvglAppType::FullScreen:
        app->app_screen = lv_obj_create(lv_scr_act());
        lv_obj_add_style(app->app_screen, &PAGE_STYLE, 0);
        break;
    case LvglAppType::NoGUI:
        /* code */
        break;

    default:
        break;
    }
    LvglUnlock();
    app->Run();
    vTaskDelete(nullptr);
}

void LvglThreadEntry(void *argument)
{
    (void)argument;

    // lv_demo_benchmark();

    lv_style_init(&PAGE_STYLE);
    lv_style_set_border_width(&PAGE_STYLE, 1);
    // lv_style_set_pad_all(&PAGE_STYLE, 2);
    lv_style_set_width(&PAGE_STYLE, lv_pct(100));
    lv_style_set_height(&PAGE_STYLE, lv_pct(95));
    lv_style_set_align(&PAGE_STYLE, LV_ALIGN_BOTTOM_MID);

    LvglApp *app1 = new TestApp();

    xTaskCreate(LvglAppRunnerEntry, app1->app_name.c_str(), app1->GetStackDepth(), app1, app1->GetPriority(), nullptr);
    LvglLock();
    auto background_text = lv_textarea_create(lv_scr_act());
    lv_textarea_add_text(background_text, "This is the background text!");
    LvglUnlock();

    TickType_t PreviousWakeTime = xTaskGetTickCount();

    for (;;) {
        LvglLock();
        lv_timer_handler();
        LvglUnlock();

        // 拖动窗口时会暂停程序，但时间仍在流逝，于是用下面这行会卡住
        vTaskDelayUntil(&PreviousWakeTime, 5);
    }
}
