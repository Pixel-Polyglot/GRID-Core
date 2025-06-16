#include <renderer.h>
#include <shaderManager.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <textureManager.h>
#include <tiffLoader.h>
#include <glm_convert.h>

Renderer renderer = Renderer();

Quad::Quad() {
}

Quad::~Quad() {
}

void Quad::destroy() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Quad::setScale(float x, float y) {
    scale = glm::vec2(x, y);
}

void Quad::getScale(float &x, float &y) {
    x = scale.x;
    y = scale.y;
}

glm::mat4 Quad::getModelMatrix() {
    return glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, 1.0f));
}

std::vector<float> Quad::getVertices() {
    return vertices;
}

Renderer::Renderer() {
}

Renderer::~Renderer() {
}

void Renderer::destroy() {
    glDeleteFramebuffers(1, &fbo);
    glDeleteRenderbuffers(1, &rbo);
    // glDeleteTextures(1, &renderTexture);
    quad->destroy();
    delete camera;
    delete quad;
}

void Renderer::createRenderTexture() {
    glGenTextures(1, &imguiTexture);
	glBindTexture(GL_TEXTURE_2D, imguiTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    textureManager.createTexture("renderTexture", 0, 0, GRID_TEXTUREFORMAT::RGBA32F, 0);
}

void Renderer::loadShaders() {
    program.setVertexShader("../shaders/vertexShader.vs");
    program.setFragmentShader("../shaders/fragmentShader.fs");

    program.compile();
}

void Renderer::createBuffers() {
    glGenFramebuffers(1, &fbo);
    glGenBuffers(1, &quad->vbo);
	glGenVertexArrays(1, &quad->vao);
    glGenRenderbuffers(1, &rbo);
}

void Renderer::setQuadBufferData() {
    glBindVertexArray(quad->vao);
    glBindBuffer(GL_ARRAY_BUFFER, quad->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * quad->getVertices().size(), &quad->getVertices()[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
}

void Renderer::init() {
    quad = new Quad();
    createBuffers();
    setQuadBufferData();
    createRenderTexture();
    loadShaders();
    camera = new GRID_Camera(1, 1);
}

GRID_Camera* Renderer::getCamera() {
    return camera;
}

void Renderer::render() {
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, imguiTexture, 0);

	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	program.use();
    glm::mat4 mvp = toGLM(camera->getProjectionMatrix()) * toGLM(camera->getViewMatrix()) * quad->getModelMatrix();
    program.setUniform("mvp", mvp);
    program.setTexture("renderTexture", "renderTexture");
    
    glBindVertexArray(quad->vao);
	glDrawArrays(GL_TRIANGLES, 0, quad->getVertices().size());
    glUseProgram(0);
    glBindVertexArray(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::resize(int prevWidth, int prevHeight, int width, int height) {
    glBindTexture(GL_TEXTURE_2D, imguiTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_HALF_FLOAT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

	glViewport(0, 0, width, height);
    camera->setResolution(width, height);

    float verticalGain = float(height) / float(prevHeight);

    float zoomX, zoomY;
    camera->getScale(zoomX, zoomY);
    camera->setScale(zoomX * verticalGain, zoomY * verticalGain);
}

void Renderer::setResolution(unsigned int width, unsigned int height) {
    quad->setScale((float)width / (float)height, 1.0f);
    glBindTexture(GL_TEXTURE_2D, textureManager.getTexture("renderTexture"));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    resx = width;
    resy = height;
}

void Renderer::getResolution(unsigned int &x, unsigned int &y) {
    x = resx;
    y = resy;
}

GLuint Renderer::getImguiTexture() {
    return imguiTexture;
}