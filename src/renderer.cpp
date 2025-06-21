#include <renderer.h>
#include <shaderManager.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <textureManager.h>
#include <tiffLoader.h>
#include <glm_convert.h>

Quad::Quad() {
}

Quad::~Quad() {
}

void Quad::destroy() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Quad::setScale(glm::vec2 scale) {
    m_scale = scale;
}

glm::vec2 Quad::getScale() {
    return m_scale;
}

glm::mat4 Quad::getModelMatrix() {
    return glm::scale(glm::mat4(1.0f), glm::vec3(m_scale, 1.0f));
}

std::vector<float> Quad::getVertices() {
    return m_vertices;
}

Renderer::Renderer() {
}

Renderer::~Renderer() {
}

void Renderer::destroy() {
    glDeleteFramebuffers(1, &m_fbo);
    glDeleteRenderbuffers(1, &m_rbo);
    // glDeleteTextures(1, &renderTexture);
    m_quad->destroy();
    delete m_camera;
    delete m_quad;
}

void Renderer::createRenderTexture() {
    glGenTextures(1, &m_imguiTexture);
	glBindTexture(GL_TEXTURE_2D, m_imguiTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    textureManager.createTexture(m_guiTextureName, glm::ivec2(0, 0), GRID_TEXTUREFORMAT::RGBA32F, 0);
}

void Renderer::loadShaders() {
    m_program.setVertexShader("rendererVertex", vertexSource);
    m_program.setFragmentShader("rendererFragment", fragmentSource);

    m_program.compile();
}

void Renderer::createBuffers() {
    glGenFramebuffers(1, &m_fbo);
    glGenBuffers(1, &m_quad->vbo);
	glGenVertexArrays(1, &m_quad->vao);
    glGenRenderbuffers(1, &m_rbo);
}

void Renderer::setQuadBufferData() {
    glBindVertexArray(m_quad->vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_quad->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_quad->getVertices().size(), &m_quad->getVertices()[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
}

void Renderer::init(const char* textureName) {
    m_guiTextureName = textureName;
    m_quad = new Quad();
    createBuffers();
    setQuadBufferData();
    createRenderTexture();
    loadShaders();
    m_camera = new GRID_Camera(GRID_Vec2i(1, 1));
}

GRID_Camera* Renderer::getCamera() {
    return m_camera;
}

void Renderer::render() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_imguiTexture, 0);

	glClearColor(0.1, 0.1, 0.1, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_program.use();
    glm::mat4 mvp = toGLM(m_camera->getProjectionMatrix()) * toGLM(m_camera->getViewMatrix()) * m_quad->getModelMatrix();
    m_program.setUniform("mvp", mvp);
    m_program.setTexture("renderTexture", m_guiTextureName);
    
    glBindVertexArray(m_quad->vao);
	glDrawArrays(GL_TRIANGLES, 0, m_quad->getVertices().size());
    glUseProgram(0);
    glBindVertexArray(0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::resize(glm::ivec2 prevResolution, glm::ivec2 resolution) {
    glBindTexture(GL_TEXTURE_2D, m_imguiTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, resolution.x, resolution.y, 0, GL_RGB, GL_HALF_FLOAT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

	glViewport(0, 0, resolution.x, resolution.y);
    m_camera->setResolution(fromGLM(resolution));

    float verticalGain = float(resolution.y) / float(prevResolution.y);

    glm::vec2 zoom = toGLM(m_camera->getScale());
    m_camera->setScale(fromGLM(zoom * verticalGain));
}

void Renderer::setResolution(glm::ivec2 resolution) {
    m_quad->setScale((glm::vec2((float)resolution.x / (float)resolution.y, 1.0f)));
    glBindTexture(GL_TEXTURE_2D, textureManager.getTexture(m_guiTextureName));
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, resolution.x, resolution.y, 0, GL_RGBA, GL_FLOAT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_resolution = resolution;
}

glm::ivec2 Renderer::getResolution() {
    return m_resolution;
}

GLuint Renderer::getImguiTexture() {
    return m_imguiTexture;
}

const char* Renderer::getTextureName() {
    return m_guiTextureName;
}