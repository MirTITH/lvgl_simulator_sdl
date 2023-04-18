#pragma once
#include <string>
#include "lvgl_thread.h"

struct Styles {
    lv_style_t title_flex;
    lv_style_t id_indicator_arc;
    lv_style_t id_indicator_num;
    lv_style_t label_msg;
};

class Dashboard
{
private:
    std::string _msg;
    uint8_t _id;
    Styles _styles;
    lv_obj_t *_frame;
    lv_obj_t *_title_flex;
    lv_obj_t *_id_indicator_arc;
    lv_obj_t *_id_indicator_num;
    lv_obj_t *_title;
    lv_obj_t *_label_msg;

public:
    Dashboard(lv_obj_t *parent, uint8_t id, lv_coord_t width, lv_coord_t height, Styles &styles)
        : _id(id), _styles(styles)
    {
        LvglLock();

        _frame = lv_obj_create(parent);
        lv_obj_clear_flag(_frame, LV_OBJ_FLAG_SCROLLABLE); // 禁止滚动
        lv_obj_set_size(_frame, width, height);
        lv_obj_set_style_pad_all(_frame, 4, LV_PART_MAIN);

        _title_flex = lv_obj_create(_frame);
        lv_obj_clear_flag(_title_flex, LV_OBJ_FLAG_SCROLLABLE); // 禁止滚动
        lv_obj_add_style(_title_flex, &_styles.title_flex, LV_PART_MAIN);
        lv_obj_set_flex_flow(_title_flex, LV_FLEX_FLOW_ROW);
        lv_obj_set_flex_align(_title_flex, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

        _id_indicator_arc = lv_spinner_create(_title_flex, 1000, 90);
        lv_arc_set_bg_angles(_id_indicator_arc, 0, 360);
        lv_arc_set_angles(_id_indicator_arc, 0, 180);
        lv_obj_set_style_arc_width(_id_indicator_arc, 2, LV_PART_MAIN);
        lv_obj_set_style_arc_width(_id_indicator_arc, 2, LV_PART_INDICATOR);
        lv_obj_remove_style(_id_indicator_arc, NULL, LV_PART_KNOB);  // make the arc non-adjustable
        lv_obj_clear_flag(_id_indicator_arc, LV_OBJ_FLAG_CLICKABLE); // make the arc non-adjustable
        lv_obj_add_style(_id_indicator_arc, &_styles.id_indicator_arc, LV_PART_MAIN);

        _id_indicator_num = lv_label_create(_id_indicator_arc);
        lv_label_set_text(_id_indicator_num, std::to_string((int)id).c_str());
        lv_obj_add_style(_id_indicator_num, &styles.id_indicator_num, LV_PART_MAIN);

        _title = lv_label_create(_title_flex);
        lv_label_set_text(_title, "This is a title!");
        lv_obj_set_width(_title, 160);

        _label_msg = lv_label_create(_frame);
        lv_obj_add_style(_label_msg, &styles.label_msg, LV_PART_MAIN);
        lv_obj_align(_label_msg, LV_ALIGN_BOTTOM_RIGHT, -5, -5);
        LvglUnlock();
    }

    void SetTitle(const std::string &title)
    {
        LvglLock();
        lv_label_set_text(_title, title.c_str());
        LvglUnlock();
    }

    template <typename T>
    void SetMessage(const T &msg, int precision = 8)
    {
        std::stringstream ss;
        ss << std::setprecision(precision) << msg;
        LvglLock();
        lv_label_set_text(_label_msg, ss.str().c_str());
        LvglUnlock();
    }

    ~Dashboard()
    {
        if (_frame != nullptr) {
            LvglLock();
            lv_obj_del(_frame);
            LvglUnlock();
        }
    }
};