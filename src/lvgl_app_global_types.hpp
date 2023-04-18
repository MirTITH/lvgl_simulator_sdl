#pragma once

#include "lvgl.h"

typedef struct {
    const lv_font_t *font_small;
    const lv_font_t *font_regular;
    const lv_font_t *font_large;
} Fonts_t;

extern Fonts_t APP_FONTS;