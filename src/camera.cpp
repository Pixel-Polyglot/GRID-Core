#include <GRID/camera.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

Camera::Camera(int width, int height, float posX, float posY, float scaleX, float scaleY) : xRes(width), yRes(height), xPos(posX), yPos(posY), xScale(scaleX), yScale(scaleY) {
    updateProjectionMatrix();
    updateViewMatrix();
}

void Camera::setPosition(float x, float y) {
    xPos = x;
    yPos = y;
    updateViewMatrix();
}

void Camera::setScale(float x, float y) {
    xScale = x;
    if (xScale < 0.1f) xScale = 0.01f;
    yScale = y;
    if (yScale < 0.1f) yScale = 0.01f;
    updateProjectionMatrix();
}

void Camera::setResolution(int x, int y) {
    xRes = x;
    yRes = y;
    updateProjectionMatrix();
}

void Camera::translate(float x, float y) {
    xPos += x/xScale;
    yPos += y/yScale;
    updateViewMatrix();
}

void Camera::getResolution(int &x, int &y) {
    x = xRes;
    y = yRes;
}

void Camera::getPosition(float &x, float &y) {
    x = xPos;
    y = yPos;
}

void Camera::getScale(float &x, float &y) {
    x = xScale;
    y = yScale;
}

void Camera::updateProjectionMatrix() {
    projection = glm::ortho(-(float)xRes / 2.0f, (float)xRes / 2.0f, (float)yRes / 2.0f, -(float)yRes / 2.0f, -1.0f, 1.0f);
    projection[0][0] *= xScale;
    projection[1][1] *= yScale;
}

void Camera::updateViewMatrix() {
    view = glm::translate(glm::mat4(1.0f), glm::vec3(xPos, yPos, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix() {
    return projection;
}

glm::mat4 Camera::getViewMatrix() {
    return view;
}