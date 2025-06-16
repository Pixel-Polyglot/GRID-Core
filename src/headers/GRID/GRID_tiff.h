#pragma once

#include "export.h"
#include <cstdint>
#include <string>
#include "GRID_tiffFormat.h"

class Tiff;

class EXPORT GRID_Tiff {
public:
    GRID_Tiff(std::string filePath);
    ~GRID_Tiff();

    uint8_t* getImage();
    uint32_t getWidth();
    uint32_t getHeight();
    uint32_t getBitsPerSample();
    uint32_t getSamplesPerPixel();
    GRID_TIFFFORMAT getSampleFormat();

private:
    Tiff* tiff;
};