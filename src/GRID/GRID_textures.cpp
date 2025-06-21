#include <GRID/GRID_textures.h>
#include <textureManager.h>
#include <glm/glm.hpp>
#include <glm_convert.h>

unsigned int GRID_Textures::writeTexture(const char* name, GRID_Vec2i resolution, GRID_TEXTUREFORMAT format, int* data) {
    return textureManager.writeTexture(name, toGLM(resolution), format, data);
}

unsigned int GRID_Textures::loadFromTiff(GRID_Tiff &tiff, const char* name) {
    return textureManager.loadFromTiff(tiff, name);
}

unsigned int GRID_Textures::createTexture(const char* name, GRID_Vec2i resolution, GRID_TEXTUREFORMAT format, int* data) {
    return textureManager.createTexture(name, toGLM(resolution), format, data);
}

unsigned int GRID_Textures::getTexture(const char* name) {
    return textureManager.getTexture(name);
}

void GRID_Textures::saveTextureToFile(const char* textureName, const char* fileName, GRID_Vec2i textureResolution, GRID_TEXTUREFORMAT format) {
    textureManager.saveTextureToFile(textureName, fileName, toGLM(textureResolution), format);
}

void GRID_Textures::setTexture(const char* name, GLuint texture) {
    textureManager.setTexture(name, texture);
}