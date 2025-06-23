#pragma once

#include "export.h"
#include "GRID_camera.h"
#include <string>

class Renderer;

class EXPORT GRID_Renderer {
public:
    GRID_Renderer();
    ~GRID_Renderer();

    void init(std::string textureName);
    void destroy();

    void resize(GRID_Vec2i prevResolution, GRID_Vec2i resolution);
    void render();

    void setResolution(GRID_Vec2i resolution);
    GRID_Vec2i getResolution();

    GRID_Camera* getCamera();

    unsigned int getGuiTexture();
    std::string getTextureName();

private:
    Renderer* m_renderer;
};