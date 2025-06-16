#include <GRID/GRID_renderer.h>
#include <renderer.h>

void GRID_Renderer::resize(int prevWidth, int prevHeight, int width, int height) {
    renderer.resize(prevWidth, prevHeight, width, height);
}

void GRID_Renderer::render() {
    renderer.render();
}

void GRID_Renderer::setResolution(unsigned int width, unsigned int height) {
    renderer.setResolution(width, height);
}

void GRID_Renderer::getResolution(unsigned int &width, unsigned int &height) {
    renderer.getResolution(width, height);
}

GRID_Camera* GRID_Renderer::getCamera() {
    return renderer.getCamera();
}

unsigned int GRID_Renderer::getGuiTexture() {
    return renderer.getImguiTexture();
}