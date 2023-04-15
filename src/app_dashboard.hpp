#pragma once

#include "lvgl_app.hpp"
#include <iostream>
#include <vector>
#include "lvgl_thread.h"

using namespace std;

class AppDashboard : public LvglApp
{
private:
    vector<lv_obj_t *> dashboards;
    struct Styles {
        lv_style_t dashboard;
        lv_style_t title_flex;
        lv_style_t id_indicator_arc;
        lv_style_t id_indicator_num;
        lv_style_t title;
    } styles;

    int Run() override
    {
        CreateDashboard();
        return 0;
    }

public:
    void CreateDashboard()
    {
        LvglLock();

        auto dashboard = lv_obj_create(GetAppProperty().main_page);
        lv_obj_clear_flag(dashboard, LV_OBJ_FLAG_SCROLLABLE); // 禁止滚动
        lv_obj_add_style(dashboard, &styles.dashboard, LV_PART_MAIN);

        auto title_flex = lv_obj_create(dashboard);
        lv_obj_clear_flag(title_flex, LV_OBJ_FLAG_SCROLLABLE); // 禁止滚动
        lv_obj_add_style(title_flex, &styles.title_flex, LV_PART_MAIN);
        lv_obj_set_flex_flow(title_flex, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(title_flex, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

        auto id_indicator_arc = lv_spinner_create(title_flex, 1000, 90);
        lv_arc_set_bg_angles(id_indicator_arc, 0, 360);
        lv_arc_set_angles(id_indicator_arc, 0, 180);
        lv_obj_set_style_arc_width(id_indicator_arc, 2, LV_PART_MAIN);
        lv_obj_set_style_arc_width(id_indicator_arc, 2, LV_PART_INDICATOR);
        lv_obj_remove_style(id_indicator_arc, NULL, LV_PART_KNOB);  // make the arc non-adjustable
        lv_obj_clear_flag(id_indicator_arc, LV_OBJ_FLAG_CLICKABLE); // make the arc non-adjustable
        lv_obj_add_style(id_indicator_arc, &styles.id_indicator_arc, LV_PART_MAIN);

        auto id_indicator_num = lv_label_create(id_indicator_arc);
        lv_label_set_text(id_indicator_num, "128");
        lv_obj_add_style(id_indicator_num, &styles.id_indicator_num, LV_PART_MAIN);

        auto title = lv_label_create(title_flex);
        lv_label_set_text(title, "This is a title!");
        lv_obj_add_style(title, &styles.title, LV_PART_MAIN);
        lv_obj_set_width(title, 160);
        LvglUnlock();

        while (1) {
            vTaskDelay(1000);
            LvglLock();
            lv_label_set_text(title, "This is a title! It is very long!");
            LvglUnlock();

        }
    }

    AppDashboard()
    {
        LvglLock();
        lv_style_init(&styles.dashboard);
        lv_style_set_width(&styles.dashboard, lv_pct(45));
        lv_style_set_height(&styles.dashboard, 80);
        lv_style_set_pad_all(&styles.dashboard, 4);

        lv_style_init(&styles.title_flex);
        lv_style_set_width(&styles.title_flex, lv_pct(100));
        lv_style_set_height(&styles.title_flex, 40);
        lv_style_set_pad_all(&styles.title_flex, 0);
        lv_style_set_radius(&styles.title_flex, 0);
        lv_style_set_border_width(&styles.title_flex, 0);
        lv_style_set_align(&styles.title_flex, LV_ALIGN_TOP_MID);
        lv_style_set_pad_column(&styles.title_flex, 5);

        lv_style_init(&styles.id_indicator_arc);
        // lv_style_set_align(&styles.id_indicator_arc, LV_ALIGN_LEFT_MID);
        lv_style_set_size(&styles.id_indicator_arc, 35);

        lv_style_init(&styles.id_indicator_num);
        lv_style_set_align(&styles.id_indicator_num, LV_ALIGN_CENTER);

        lv_style_init(&styles.title);
        // lv_style_set_border_width(&styles.title, 1);
        // lv_style_set_height(&styles.title, lv_pct(100));
        // lv_style_set_text_align(&styles.title, LV_TEXT_ALIGN_CENTER);
        // lv_style_set_align(&styles.title, LV_ALIGN_OUT_LEFT_MID);
        // lv_style_set_pad_all(&styles.title, 0);

        LvglUnlock();
    }
    // ~AppDashboard();
};
