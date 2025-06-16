#include <GRID/GRID_camera.h>
#include <camera.h>
#include <glm/glm.hpp>
#include <glm_convert.h>

GRID_Camera::GRID_Camera(int width, int height, float x, float y, float scaleX, float scaleY) {
    camera = new Camera(glm::ivec2(width, height), glm::vec2(x, y), glm::vec2(scaleX, scaleY));
}

GRID_Camera::~GRID_Camera() {
    delete camera;
}

void GRID_Camera::setPosition(float x, float y) {
    camera->setPosition(glm::vec2(x, y));
}

void GRID_Camera::setResolution(int x, int y) {
    camera->setResolution(glm::ivec2(x, y));
}

void GRID_Camera::translate(float x, float y) {
    camera->translate(glm::vec2(x, y));
}

void GRID_Camera::setScale(float x, float y) {
    camera->setScale(glm::vec2(x, y));
}

void GRID_Camera::getResolution(int &x, int &y) {
    glm::ivec2 res;
    camera->getResolution(res);
    x = res.x;
    y = res.y;
}

void GRID_Camera::getPosition(float &x, float &y) {
    glm::vec2 pos;
    camera->getPosition(pos);
    x = pos.x;
    y = pos.y;
}

void GRID_Camera::getScale(float &x, float &y) {
    glm::vec2 scale;
    camera->getScale(scale);
    x = scale.x;
    y = scale.y;
}

GRID_Mat4 GRID_Camera::getProjectionMatrix() {
    return fromGLM(camera->getProjectionMatrix());
}

GRID_Mat4 GRID_Camera::getViewMatrix() {
    return fromGLM(camera->getViewMatrix());
}