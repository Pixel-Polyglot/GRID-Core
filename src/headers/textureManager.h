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
    GLuint writeTexture(const char* name, glm::ivec2 resolution, GRID_TEXTUREFORMAT format, int* data = 0);
    GLuint loadFromTiff(GRID_Tiff &tiff, const char* name);
    GLuint createTexture(const char* name, glm::ivec2 resolution, GRID_TEXTUREFORMAT format, int* data = 0);
    GLuint getTexture(const char* name);
    void saveTextureToFile(const char* textureName, const char* fileName, glm::ivec2 textureResolution, GRID_TEXTUREFORMAT format);
    void setTexture(const char* name, GLuint texture);

private:
    std::unordered_map<const char*, GLuint> m_textures;
};

extern TextureManager textureManager;