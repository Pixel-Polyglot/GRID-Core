#include <camera.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

Camera::Camera(glm::ivec2 resolution, glm::vec2 position, glm::vec2 scale) : m_resolution(resolution), m_position(position), m_scale(scale) {
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
    m_resolution = resolution;
    updateProjectionMatrix();
}

void Camera::translate(glm::vec2 offset) {
    m_position.x += offset.x / m_scale.x;
    m_position.y += offset.y / m_scale.y;
    updateViewMatrix();
}

glm::ivec2 Camera::getResolution() {
    return m_resolution;
}

glm::vec2 Camera::getPosition() {
    return m_position;
}

glm::vec2 Camera::getScale() {
    return m_scale;
}

void Camera::updateProjectionMatrix() {
    m_projection = glm::ortho(-(float)m_resolution.x / 2.0f, (float)m_resolution.x / 2.0f, (float)m_resolution.y / 2.0f, -(float)m_resolution.y / 2.0f, -1.0f, 1.0f);
    m_projection[0][0] *= m_scale.x;
    m_projection[1][1] *= m_scale.y;
}

void Camera::updateViewMatrix() {
    m_view = glm::translate(glm::mat4(1.0f), glm::vec3(m_position.x, m_position.y, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix() {
    return m_projection;
}

glm::mat4 Camera::getViewMatrix() {
    return m_view;
}