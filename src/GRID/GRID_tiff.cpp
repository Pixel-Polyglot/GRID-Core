#include <GRID/GRID_tiff.h>
#include <tiffLoader.h>
#include "glm_convert.h"

GRID_Tiff::GRID_Tiff(const char* filePath) {
    m_tiff = new Tiff(filePath);
}

GRID_Tiff::~GRID_Tiff() {
    delete m_tiff;
}

uint8_t* GRID_Tiff::getImage() {
    return m_tiff->getImage();
}

GRID_Vec2i GRID_Tiff::getResolution() {
    return fromGLM(m_tiff->getResolution());
}

uint32_t GRID_Tiff::getBitsPerSample() {
    return m_tiff->getBitsPerSample();
}

uint32_t GRID_Tiff::getSamplesPerPixel() {
    return m_tiff->getSamplesPerPixel();
}

GRID_TIFFFORMAT GRID_Tiff::getSampleFormat() {
    return m_tiff->getSampleFormat();
}