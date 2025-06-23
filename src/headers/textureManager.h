#pragma once
#include <cstdint>
#include <GRID/GRID_tiff.h>
#include <glad/glad.h>
#include <unordered_map>
#include <GRID/GRID_textureFormat.h>
#include <glm/glm.hpp>

class TextureManager {
public:
    TextureManager();
    ~TextureManager();
    GLuint writeTexture(std::string name, glm::ivec2 resolution, GRID_TEXTUREFORMAT format, int* data = 0);
    GLuint loadFromTiff(GRID_Tiff &tiff, std::string name);
    GLuint createTexture(std::string name, glm::ivec2 resolution, GRID_TEXTUREFORMAT format, int* data = 0);
    GLuint getTexture(std::string name);
    void saveTextureToFile(std::string textureName, std::string fileName, glm::ivec2 textureResolution, GRID_TEXTUREFORMAT format);
    void setTexture(std::string name, GLuint texture);

private:
    std::unordered_map<std::string, GLuint> m_textures;
};

extern TextureManager textureManager;