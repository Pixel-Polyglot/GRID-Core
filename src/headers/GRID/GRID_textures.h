#pragma once

#include "export.h"
#include "GRID_textureFormat.h"
#include "GRID_tiff.h"
#include "GRID_math.h"

class EXPORT GRID_Textures {
public:
    static unsigned int writeTexture(const char* name, GRID_Vec2i resolution, GRID_TEXTUREFORMAT format, int* data = 0);
    static unsigned int loadFromTiff(GRID_Tiff &tiff, const char* name);
    static unsigned int createTexture(const char* name, GRID_Vec2i resolution, GRID_TEXTUREFORMAT format, int* data = 0);
    static unsigned int getTexture(const char* name);
    static void saveTextureToFile(const char* textureName, const char* fileName, GRID_Vec2i textureResolution, GRID_TEXTUREFORMAT format);
    static void setTexture(const char* name, unsigned int texture);
};