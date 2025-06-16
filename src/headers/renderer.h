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
    void setScale(float x, float y);
    void getScale(float& x, float& y);
    std::vector<float> getVertices();
    glm::mat4 getModelMatrix();
    GLuint vao;
    GLuint vbo;

private:
    glm::vec2 scale = glm::vec2(1.0f, 1.0f);
    std::vector<float> vertices = {
        -0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f,
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f
    };

    glm::mat4 model = glm::mat4(1.0f);
};

class Renderer {
public:
    Renderer();
    ~Renderer();
    void destroy();
    void init();
    void resize(int prevWidth, int prevHeight, int width, int height);
    void render();

    void setResolution(unsigned int width, unsigned int height);
    void getResolution(unsigned int &width, unsigned int &height);

    GRID_Camera* getCamera();

    GLuint getImguiTexture();

private:
    void loadShaders();
    void createRenderTexture();
    void createBuffers();
    void setQuadBufferData();

    Quad* quad;
    GRID_Camera* camera;

    RenderProgram program;

    GLuint fbo;
    GLuint rbo;
    GLuint imguiTexture;

    int resx, resy;
};

extern Renderer renderer;