#include <camera.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

Camera::Camera(glm::ivec2 resolution, glm::vec2 position, glm::vec2 scale) : m_res(resolution), m_position(position), m_scale(scale) {
    updateProjectionMatrix();
    updateViewMatrix();
}

void Camera::setPosition(glm::vec2 position) {
    m_position = position;
    updateViewMatrix();
}

void Camera::setScale(glm::vec2 scale) {
    m_scale.x = scale.x;
    if (m_scale.x < 0.1f) m_scale.x = 0.01f;
    m_scale.y = scale.y;
    if (m_scale.y < 0.1f) m_scale.y = 0.01f;
    updateProjectionMatrix();
}

void Camera::setResolution(glm::ivec2 resolution) {
    m_res = resolution;
    updateProjectionMatrix();
}

void Camera::translate(glm::vec2 offset) {
    m_position.x += offset.x / m_scale.x;
    m_position.y += offset.y / m_scale.y;
    updateViewMatrix();
}

void Camera::getResolution(glm::ivec2 &resolution) {
    resolution = m_res;
}

void Camera::getPosition(glm::vec2& position) {
    position = m_position;
}

void Camera::getScale(glm::vec2& scale) {
    scale = m_scale;
}

void Camera::updateProjectionMatrix() {
    projection = glm::ortho(-(float)m_res.x / 2.0f, (float)m_res.x / 2.0f, (float)m_res.y / 2.0f, -(float)m_res.y / 2.0f, -1.0f, 1.0f);
    projection[0][0] *= m_scale.x;
    projection[1][1] *= m_scale.y;
}

void Camera::updateViewMatrix() {
    view = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x, m_position.y, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix() {
    return projection;
}

glm::mat4 Camera::getViewMatrix() {
    return view;
}