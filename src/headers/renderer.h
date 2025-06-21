#pragma once
// #include <glad/glad.h>
#include <vector>
#include <GRID/GRID_camera.h>
#include <shaderProgram.h>

class Quad {
public:
    Quad();
    ~Quad();
    void destroy();
    void setScale(glm::vec2 scale);
    glm::vec2 getScale();
    std::vector<float> getVertices();
    glm::mat4 getModelMatrix();
    GLuint vao;
    GLuint vbo;

private:
    glm::vec2 m_scale = glm::vec2(1.0f, 1.0f);
    std::vector<float> m_vertices = {
        -0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f
    };

    glm::mat4 m_model = glm::mat4(1.0f);
};

class Renderer {
public:
    Renderer();
    ~Renderer();
    void destroy();
    void init(const char* textureName);
    void resize(glm::ivec2 prevResolution, glm::ivec2 resolution);
    void render();

    void setResolution(glm::ivec2 resolution);
    glm::ivec2 getResolution();

    const char* getTextureName();

    GRID_Camera* getCamera();

    GLuint getImguiTexture();

private:
    void loadShaders();
    void createRenderTexture();
    void createBuffers();
    void setQuadBufferData();

    Quad* m_quad;
    GRID_Camera* m_camera;

    RenderProgram m_program;

    GLuint m_fbo;
    GLuint m_rbo;
    GLuint m_imguiTexture;
    const char* m_guiTextureName;

    glm::ivec2 m_resolution;

const char* vertexSource = R"VERTEX(#version 450 core
uniform mat4 mvp;
in vec3 vert;
out vec3 pos;

void main() {
    pos = vert;
    gl_Position = mvp * vec4(vert, 1.0);
}
)VERTEX";

    const char* fragmentSource = R"FRAGMENT(#version 450 core
uniform sampler2D renderTexture;
in vec3 pos;
out vec4 color;
void main(){
    vec2 uv = vec2(pos.x+0.5, pos.y+0.5);
    vec4 texColor = texture(renderTexture, uv);
    color = texColor;
}
)FRAGMENT";
};