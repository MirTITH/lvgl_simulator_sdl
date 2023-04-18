#pragma once

#include "lvgl_app.hpp"
#include <sstream>
#include <map>
#include <iomanip>
#include "lvgl_thread.h"
#include "dashboard.hpp"

class AppDashboard : public LvglApp
{
private:
    Styles _default_styles;

    std::map<uint8_t, Dashboard *> dashboards;

public:
    int Init() override
    {
        lv_obj_set_flex_flow(App().main_page, LV_FLEX_FLOW_ROW_WRAP);
        lv_obj_set_flex_align(App().main_page, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
        lv_obj_set_style_pad_column(App().main_page, 0, LV_PART_MAIN);
        // lv_style_set_pad_column(App().main_page, 0);
        return 0;
    }

    Dashboard *Id(uint8_t id)
    {
        return dashboards[id];
    }

    void NewDashboard(uint8_t id, std::string title = "Untitled", std::string msg = "No message")
    {
        auto iter = dashboards.find(id);

        if (iter != dashboards.end()) {
            // dashboards 中有该 id
            delete iter->second; // 删掉已经有的
            dashboards.erase(iter);
        }

        auto dashboard = new Dashboard(App().main_page, id, lv_pct(48), 80, _default_styles);

        dashboard->SetTitle(title);
        dashboard->SetMessage(msg);

        dashboards[id] = dashboard;
    }

    void DelDashboard(uint8_t id)
    {
        dashboards.erase(id);
    }

    AppDashboard()
    {
        LvglLock();

        lv_style_init(&_default_styles.title_flex);
        lv_style_set_width(&_default_styles.title_flex, lv_pct(100));
        lv_style_set_height(&_default_styles.title_flex, 40);
        lv_style_set_pad_all(&_default_styles.title_flex, 0);
        lv_style_set_radius(&_default_styles.title_flex, 0);
        lv_style_set_border_width(&_default_styles.title_flex, 0);
        lv_style_set_align(&_default_styles.title_flex, LV_ALIGN_TOP_MID);
        lv_style_set_pad_column(&_default_styles.title_flex, 5);

        lv_style_init(&_default_styles.id_indicator_arc);
        lv_style_set_size(&_default_styles.id_indicator_arc, 35);

        lv_style_init(&_default_styles.id_indicator_num);
        lv_style_set_align(&_default_styles.id_indicator_num, LV_ALIGN_CENTER);

        lv_style_init(&_default_styles.label_msg);
        lv_style_set_text_font(&_default_styles.label_msg, APP_FONTS.font_large);

        LvglUnlock();
    }

private:
    int Run() override
    {
        // CreateDashboard();
        return 0;
    }
};
