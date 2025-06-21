#pragma once

#include "export.h"
#include "GRID_widget.h"
#include "GRID_math.h"

class EXPORT GRID_UI {
public:
    static void addWidget(GRID_Widget* widget);

    static void begin(const char* name, bool padding = true);
    static void end();

    static void text(const char* fmt, ...);

    static bool checkbox(const char* label, bool* v);
    static bool inputText(const char* label, char* buf, size_t buf_size);
    static bool button(const char* label);

    static void image(void* user_texture_id, const GRID_Vec2f& image_size, const GRID_Vec2f& uv0 = GRID_Vec2f(0, 0), const GRID_Vec2f& uv1 = GRID_Vec2f(1, 1));

    static bool isWindowHovered();

    static GRID_Vec2f getContentRegionAvail();

private:
    static inline int m_styles;
};