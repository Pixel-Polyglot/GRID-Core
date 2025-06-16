#pragma once

#include "export.h"
#include "GRID_math.h"

class EXPORT GRID_Input
{
public:
    enum MouseButton
    {
        MOUSE_BUTTON_LEFT = 0,
        MOUSE_BUTTON_RIGHT = 1,
        MOUSE_BUTTON_MIDDLE = 2,
    };

    static GRID_Vec2f getMousePos();
    static bool isMouseButtonDown(MouseButton button);
    static float getMouseWheel();
};
