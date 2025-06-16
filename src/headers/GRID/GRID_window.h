#pragma once

#include "export.h"

class EXPORT GRID_Window {
public:
    static void enableVsync(bool enable);
    static double getDeltaTime();
};