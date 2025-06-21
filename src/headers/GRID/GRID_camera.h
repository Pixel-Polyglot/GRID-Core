#pragma once

#include "export.h"
#include "GRID_math.h"

class Camera;

class EXPORT GRID_Camera {
public:
    GRID_Camera(GRID_Vec2i resolution, GRID_Vec2f position = GRID_Vec2f(0.0f, 0.0f), GRID_Vec2f scale = GRID_Vec2f(1.0f, 1.0f));
    ~GRID_Camera();
    void setPosition(GRID_Vec2f position);
    void setResolution(GRID_Vec2i resolution);
    void translate(GRID_Vec2f offset);
    void setScale(GRID_Vec2f scale);

    GRID_Vec2i getResolution();
    GRID_Vec2f getPosition();
    GRID_Vec2f getScale();

    GRID_Mat4 getProjectionMatrix();
    GRID_Mat4 getViewMatrix();

private:
    Camera* m_camera;
};