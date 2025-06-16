#pragma once
#include <string>
#include <cstdint>
#include <GRID/GRID_tiffFormat.h>

class Tiff {
public:
    Tiff(std::string filePath);
    ~Tiff();

    uint8_t* getImage();
    uint32_t getWidth();
    uint32_t getHeight();
    uint32_t getBitsPerSample();
    uint32_t getSamplesPerPixel();
    GRID_TIFFFORMAT getSampleFormat();

private:
    void load(std::string filePath);

    std::string filePath;
    uint8_t* image;
    uint32_t width;
    uint32_t height;
    uint32_t bitsPerSample;
    uint32_t samplesPerPixel;
    GRID_TIFFFORMAT sampleFormat;
};