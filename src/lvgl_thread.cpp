#include "lvgl_thread.h"
#include "lvgl.h"
#include <mutex>
#include "FreeRTOS.h"
#include "lvgl_app.hpp"
#include "test_app.hpp"
#include <chrono>

using namespace std;

static std::mutex LvglMutex;

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
        lv_obj_set_align(app->app_screen, LV_ALIGN_CENTER);
        break;
    case LvglAppType::FullScreen:
        app->app_screen = lv_obj_create(nullptr);
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

    LvglApp *app1 = new TestApp();

    xTaskCreate(LvglAppRunnerEntry, app1->app_name.c_str(), app1->GetStackDepth(), app1, app1->GetPriority(), nullptr);
    LvglLock();
    auto background_text = lv_textarea_create(lv_scr_act());
    lv_textarea_add_text(background_text, "This is the background text!");
    LvglUnlock();

    // uint32_t PreviousWakeTime = xTaskGetTickCount();

    for (;;) {
        LvglLock();
        lv_timer_handler();
        LvglUnlock();

        vTaskDelay(5);

        // 拖动窗口时会暂停程序，但时间仍在流逝，于是用下面这行会卡住
        // vTaskDelayUntil(&PreviousWakeTime, 5);
    }
}
