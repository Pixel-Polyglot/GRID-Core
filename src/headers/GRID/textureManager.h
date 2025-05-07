#pragma once

#include <cstdint>
#include <GRID/tiffLoader.h>
#include <glad/glad.h>
#include <unordered_map>

enum TEXTURE_FORMAT {
    R8 = 0,
    RGBA8 = 1,
    RGBA8UI = 2,
    RGBA16F = 3,
    RGBA16UI = 4,
    R8UI = 5,
    R16F = 6,
    R16UI = 7,
    RGBA32F = 8,
    R32UI = 9,
    RGBA32UI = 10
};

class TextureManager {
public:
    TextureManager();
    ~TextureManager();
    GLuint writeTexture(std::string name, int width, int height, TEXTURE_FORMAT format, int* data = 0);
    GLuint loadFromTiff(Tiff &tiff, std::string name);
    GLuint createTexture(std::string name, int width, int height, TEXTURE_FORMAT format, int* data = 0);
    GLuint getTexture(std::string name);
    void saveTextureToFile(std::string textureName, std::string fileName, int width, int height, TEXTURE_FORMAT format, int sizeX=0, int sizeY=0, int offsetX=0, int offsetY=0);
    void setTexture(std::string name, GLuint texture);

private:
    std::unordered_map<std::string, GLuint> textures;
};

extern TextureManager textureManager;