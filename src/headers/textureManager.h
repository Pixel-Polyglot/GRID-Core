#pragma once
#include <cstdint>
#include <GRID/GRID_tiff.h>
#include <glad/glad.h>
#include <unordered_map>
#include <GRID/GRID_textureFormat.h>

class TextureManager {
public:
    TextureManager();
    ~TextureManager();
    GLuint writeTexture(std::string name, int width, int height, GRID_TEXTUREFORMAT format, int* data = 0);
    GLuint loadFromTiff(GRID_Tiff &tiff, std::string name);
    GLuint createTexture(std::string name, int width, int height, GRID_TEXTUREFORMAT format, int* data = 0);
    GLuint getTexture(std::string name);
    void saveTextureToFile(std::string textureName, std::string fileName, int width, int height, GRID_TEXTUREFORMAT format, int sizeX = 0, int sizeY = 0, int offsetX = 0, int offsetY = 0);
    void setTexture(std::string name, GLuint texture);

private:
    std::unordered_map<std::string, GLuint> textures;
};

extern TextureManager textureManager;