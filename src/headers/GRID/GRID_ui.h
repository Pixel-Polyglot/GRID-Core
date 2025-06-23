#pragma once

#include "export.h"
#include "GRID_widget.h"
#include "GRID_math.h"
#include <string>

class EXPORT GRID_UI {
public:
    static void addWidget(GRID_Widget* widget);

    static void begin(std::string name, bool padding = true);
    static void end();

    static void text(std::string text);

    static bool checkbox(std::string label, bool* v);
    static bool inputText(std::string label, char* buf, size_t buf_size);
    static bool button(std::string label);

    static void image(void* user_texture_id, const GRID_Vec2f& image_size, const GRID_Vec2f& uv0 = GRID_Vec2f(0, 0), const GRID_Vec2f& uv1 = GRID_Vec2f(1, 1));

    static bool isWindowHovered();

    static GRID_Vec2f getContentRegionAvail();

private:
    static inline int m_styles;
};