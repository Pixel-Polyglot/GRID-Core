#include <GRID/GRID_camera.h>
#include <camera.h>
#include <glm/glm.hpp>
#include <glm_convert.h>

GRID_Camera::GRID_Camera(GRID_Vec2i resolution, GRID_Vec2f position, GRID_Vec2f scale) {
    m_camera = new Camera(toGLM(resolution), toGLM(position), toGLM(scale));
}

GRID_Camera::~GRID_Camera() {
    delete m_camera;
}

void GRID_Camera::setPosition(GRID_Vec2f position) {
    m_camera->setPosition(toGLM(position));
}

void GRID_Camera::setResolution(GRID_Vec2i resolution) {
    m_camera->setResolution(toGLM(resolution));
}

void GRID_Camera::translate(GRID_Vec2f offset) {
    m_camera->translate(toGLM(offset));
}

void GRID_Camera::setScale(GRID_Vec2f scale) {
    m_camera->setScale(toGLM(scale));
}

GRID_Vec2i GRID_Camera::getResolution() {
    return fromGLM(m_camera->getResolution());
}

GRID_Vec2f GRID_Camera::getPosition() {
    return fromGLM(m_camera->getPosition());
}

GRID_Vec2f GRID_Camera::getScale() {
    return fromGLM(m_camera->getScale());
}

GRID_Mat4 GRID_Camera::getProjectionMatrix() {
    return fromGLM(m_camera->getProjectionMatrix());
}

GRID_Mat4 GRID_Camera::getViewMatrix() {
    return fromGLM(m_camera->getViewMatrix());
}