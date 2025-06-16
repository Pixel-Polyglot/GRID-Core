#pragma once
#include <glm/mat4x4.hpp>
#include <tuple>

class Camera {
public:
    Camera(glm::ivec2 resolution, glm::vec2 position = glm::vec2(0.0f, 0.0f), glm::vec2 scale = glm::vec2(1.0f, 1.0f));
    void setPosition(glm::vec2 position);
    void setResolution(glm::ivec2 resolution);
    void translate(glm::vec2 offset);
    void setScale(glm::vec2 scale);

    void getResolution(glm::ivec2 &resolution);
    void getPosition(glm::vec2 &position);
    void getScale(glm::vec2 &scale);

    glm::mat4 getProjectionMatrix();
    glm::mat4 getViewMatrix();

private:
    void updateProjectionMatrix();
    void updateViewMatrix();

    glm::mat4 projection;
    glm::mat4 view;

    glm::ivec2 m_res;
    glm::vec2 m_position;
    glm::vec2 m_scale;
};