#pragma once

#include "export.h"
#include <cstdint>
#include "GRID_tiffFormat.h"
#include "GRID_math.h"

class Tiff;

class EXPORT GRID_Tiff {
public:
    GRID_Tiff(const char* filePath);
    ~GRID_Tiff();

    uint8_t* getImage();
    GRID_Vec2i getResolution();
    unsigned int getBitsPerSample();
    unsigned int getSamplesPerPixel();
    GRID_TIFFFORMAT getSampleFormat();

private:
    Tiff* m_tiff;
};