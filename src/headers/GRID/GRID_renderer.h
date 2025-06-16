#pragma once

#include "export.h"
#include "GRID_camera.h"

class EXPORT GRID_Renderer {
public:
    static void resize(int prevWidth, int prevHeight, int width, int height);
    static void render();

    static void setResolution(unsigned int width, unsigned int height);
    static void getResolution(unsigned int &width, unsigned int &height);

    static GRID_Camera* getCamera();

    static unsigned int getGuiTexture();
};