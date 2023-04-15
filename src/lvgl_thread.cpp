#include "lvgl_thread.h"
#include "lvgl.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "lvgl_app.hpp"
#include "app_dashboard.hpp"
#include "lvgl/demos/lv_demos.h"
#include <chrono>

using namespace std;

static SemaphoreHandle_t LvglMutex;

lv_style_t PAGE_STYLE;

void LvglLock()
{
    xSemaphoreTakeRecursive(LvglMutex, portMAX_DELAY);
}

void LvglUnlock()
{
    xSemaphoreGiveRecursive(LvglMutex);
}

static void LvglAppRunnerEntry(void *argument)
{
    auto app            = (LvglApp *)argument;
    lv_obj_t *main_page = nullptr;
    LvglLock();
    switch (app->GetAppProperty().type) {
    case LvglApp::Type::Normal:
        main_page = lv_obj_create(lv_scr_act());
        lv_obj_add_style(main_page, &PAGE_STYLE, 0);

        break;
    case LvglApp::Type::FullScreen:
        /* code */
        break;
    case LvglApp::Type::NoGUI:
        /* code */
        break;

    default:
        break;
    }

    LvglUnlock();
    app->SetAppMainPage(main_page);
    app->Run();
    vTaskDelete(nullptr);
}

void LvglThreadEntry(void *argument)
{
    (void)argument;

    LvglMutex = xSemaphoreCreateRecursiveMutex();

    // lv_demo_benchmark();

    lv_style_init(&PAGE_STYLE);
    lv_style_set_border_width(&PAGE_STYLE, 1);
    lv_style_set_pad_all(&PAGE_STYLE, 0);
    lv_style_set_width(&PAGE_STYLE, lv_pct(100));
    lv_style_set_height(&PAGE_STYLE, lv_pct(95));
    lv_style_set_radius(&PAGE_STYLE, 0);
    lv_style_set_align(&PAGE_STYLE, LV_ALIGN_BOTTOM_MID);

    LvglApp *app1 = new AppDashboard();

    auto app_property = app1->GetAppProperty();

    xTaskCreate(LvglAppRunnerEntry, app_property.name.c_str(), app1->GetStackDepth(), app1, app1->GetPriority(), nullptr);

    TickType_t PreviousWakeTime = xTaskGetTickCount();

    for (;;) {
        LvglLock();
        lv_timer_handler();
        LvglUnlock();

        // 拖动窗口时会暂停程序，但时间仍在流逝，于是用下面这行会卡住
        vTaskDelayUntil(&PreviousWakeTime, 5);
    }
}
