#pragma once

#include "export.h"

class EXPORT GRID_Widget {
public:
    virtual ~GRID_Widget() {};
    virtual void render() = 0;
};