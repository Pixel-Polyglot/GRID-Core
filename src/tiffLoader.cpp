#include <tiffLoader.h>
#include <tinytiffreader.h>
#include <iostream>

Tiff::Tiff(const char* filePath) {
    load(filePath);
}

Tiff::~Tiff() {
    free(m_image);
}

uint8_t* Tiff::getImage() {
    return m_image;
}

glm::ivec2 Tiff::getResolution() {
    return m_resolution;
}

unsigned int Tiff::getBitsPerSample() {
    return m_bitsPerSample;
}

unsigned int Tiff::getSamplesPerPixel() {
    return m_samplesPerPixel;
}

GRID_TIFFFORMAT Tiff::getSampleFormat() {
    return m_sampleFormat;
}

void Tiff::load(const char* filePath) {
    TinyTIFFReaderFile* tiffr = NULL;
    tiffr = TinyTIFFReader_open(filePath); 
    if (!tiffr) { 
        std::cout << "Tiff file:" << filePath << " not existent, not accessible or not a TIFF file)" << std::endl; 
    } else { 
        m_resolution.x = TinyTIFFReader_getWidth(tiffr);
        m_resolution.y = TinyTIFFReader_getHeight(tiffr);
        m_bitsPerSample = TinyTIFFReader_getBitsPerSample(tiffr, 0);
        m_samplesPerPixel = TinyTIFFReader_getSamplesPerPixel(tiffr);
        m_sampleFormat = (GRID_TIFFFORMAT)TinyTIFFReader_getSampleFormat(tiffr);

        m_image = (uint8_t*)calloc(m_resolution.x * m_resolution.y * m_samplesPerPixel, m_bitsPerSample / 8);  
        if (!TinyTIFFReader_getSampleData(tiffr, m_image, 0)) {
            std::cout << TinyTIFFReader_getLastError(tiffr) << std::endl;
        }
    } 
    TinyTIFFReader_close(tiffr); 
}