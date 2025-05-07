#pragma once

#include <string>
#include <cstdint>

enum TIFF_SAMPLEFORMAT {
    TIFF_UINT = 1,
    TIFF_INT = 2,
    TIFF_FLOAT = 3,
    TIFF_VOID = 4
};

class Tiff {
public:
    Tiff(std::string filePath);
    ~Tiff();

    uint8_t* getImage();
    uint32_t getWidth();
    uint32_t getHeight();
    uint32_t getBitsPerSample();
    uint32_t getSamplesPerPixel();
    TIFF_SAMPLEFORMAT getSampleFormat();

private:
    void load(std::string filePath);

    std::string filePath;
    uint8_t* image;
    uint32_t width;
    uint32_t height;
    uint32_t bitsPerSample;
    uint32_t samplesPerPixel;
    TIFF_SAMPLEFORMAT sampleFormat;
};