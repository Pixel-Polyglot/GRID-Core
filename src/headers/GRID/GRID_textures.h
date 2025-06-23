#pragma once

#include "export.h"
#include "GRID_textureFormat.h"
#include "GRID_tiff.h"
#include "GRID_math.h"
#include <string>

class EXPORT GRID_Textures {
public:
    static unsigned int writeTexture(std::string name, GRID_Vec2i resolution, GRID_TEXTUREFORMAT format, int* data = 0);
    static unsigned int loadFromTiff(GRID_Tiff &tiff, std::string name);
    static unsigned int createTexture(std::string name, GRID_Vec2i resolution, GRID_TEXTUREFORMAT format, int* data = 0);
    static unsigned int getTexture(std::string name);
    static void saveTextureToFile(std::string textureName, std::string fileName, GRID_Vec2i textureResolution, GRID_TEXTUREFORMAT format);
    static void setTexture(std::string name, unsigned int texture);
};