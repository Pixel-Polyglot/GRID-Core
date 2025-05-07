#pragma once
#include <glm/mat4x4.hpp>
#include <tuple>

class Camera {
public:
    Camera(int width, int height, float x = 0.0f, float y = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f);
    void setPosition(float x, float y);
    void setResolution(int x, int y);
    void translate(float x, float y);
    void setScale(float x, float y);

    void getResolution(int &x, int &y);
    void getPosition(float &x, float &y);
    void getScale(float &x, float &y);

    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();

private:
    void updateProjectionMatrix();
    void updateViewMatrix();

    glm::mat4 projection;
    glm::mat4 view;

    int xRes;
    int yRes;
    float xPos;
    float yPos;
    float xScale;
    float yScale;
};