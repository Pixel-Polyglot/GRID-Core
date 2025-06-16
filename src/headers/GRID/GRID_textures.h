#pragma once

#include "export.h"
#include "GRID_textureFormat.h"
#include "GRID_tiff.h"
#include <string>

class EXPORT GRID_Textures {
public:
    static unsigned int writeTexture(std::string name, int width, int height, GRID_TEXTUREFORMAT format, int* data = 0);
    static unsigned int loadFromTiff(GRID_Tiff &tiff, std::string name);
    static unsigned int createTexture(std::string name, int width, int height, GRID_TEXTUREFORMAT format, int* data = 0);
    static unsigned int getTexture(std::string name);
    static void saveTextureToFile(std::string textureName, std::string fileName, int width, int height, GRID_TEXTUREFORMAT format, int sizeX=0, int sizeY=0, int offsetX=0, int offsetY=0);
    static void setTexture(std::string name, unsigned int texture);
};