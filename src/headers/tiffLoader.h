#pragma once
#include <cstdint>
#include <GRID/GRID_tiffFormat.h>
#include <glm/glm.hpp>

class Tiff {
public:
    Tiff(const char* filePath);
    ~Tiff();

    uint8_t* getImage();
    glm::ivec2 getResolution();
    unsigned int getBitsPerSample();
    unsigned int getSamplesPerPixel();
    GRID_TIFFFORMAT getSampleFormat();

private:
    void load(const char* filePath);

    uint8_t* m_image;
    glm::ivec2 m_resolution;
    unsigned int m_bitsPerSample;
    unsigned int m_samplesPerPixel;
    GRID_TIFFFORMAT m_sampleFormat;
};