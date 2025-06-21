#include <GRID/GRID_renderer.h>
#include <renderer.h>
#include <glm_convert.h>

GRID_Renderer::GRID_Renderer() {
    m_renderer = new Renderer();
}

GRID_Renderer::~GRID_Renderer() {
    delete m_renderer;
}

void GRID_Renderer::init(const char* textureName) {
    m_renderer->init(textureName);
}

void GRID_Renderer::destroy() {
    m_renderer->destroy();
}

void GRID_Renderer::resize(GRID_Vec2i prevResolution, GRID_Vec2i resolution) {
    m_renderer->resize(toGLM(prevResolution), toGLM(resolution));
}

void GRID_Renderer::render() {
    m_renderer->render();
}

void GRID_Renderer::setResolution(GRID_Vec2i resolution) {
    m_renderer->setResolution(toGLM(resolution));
}

GRID_Vec2i GRID_Renderer::getResolution() {
    return fromGLM(m_renderer->getResolution());
}

GRID_Camera* GRID_Renderer::getCamera() {
    return m_renderer->getCamera();
}

unsigned int GRID_Renderer::getGuiTexture() {
    return m_renderer->getImguiTexture();
}

const char* GRID_Renderer::getTextureName() {
    return m_renderer->getTextureName();
}