#include <GRID/GRID_tiff.h>
#include <tiffLoader.h>

GRID_Tiff::GRID_Tiff(std::string filePath) {
    tiff = new Tiff(filePath);
}

GRID_Tiff::~GRID_Tiff() {
    delete tiff;
}

uint8_t* GRID_Tiff::getImage() {
    return tiff->getImage();
}

uint32_t GRID_Tiff::getWidth() {
    return tiff->getWidth();
}

uint32_t GRID_Tiff::getHeight() {
    return tiff->getHeight();
}

uint32_t GRID_Tiff::getBitsPerSample() {
    return tiff->getBitsPerSample();
}

uint32_t GRID_Tiff::getSamplesPerPixel() {
    return tiff->getSamplesPerPixel();
}

GRID_TIFFFORMAT GRID_Tiff::getSampleFormat() {
    return tiff->getSampleFormat();
}