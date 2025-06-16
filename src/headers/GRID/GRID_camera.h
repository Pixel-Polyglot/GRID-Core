#pragma once

#include "export.h"
#include "GRID_math.h"

class Camera;

class EXPORT GRID_Camera {
public:
    GRID_Camera(int width, int height, float x = 0.0f, float y = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f);
    ~GRID_Camera();
    void setPosition(float x, float y);
    void setResolution(int x, int y);
    void translate(float x, float y);
    void setScale(float x, float y);

    void getResolution(int &x, int &y);
    void getPosition(float &x, float &y);
    void getScale(float &x, float &y);

    GRID_Mat4 getProjectionMatrix();
    GRID_Mat4 getViewMatrix();

private:
    Camera* camera;
};