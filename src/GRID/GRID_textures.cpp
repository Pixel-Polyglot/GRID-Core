#include <GRID/GRID_textures.h>
#include <textureManager.h>
#include <glm/glm.hpp>
#include <glm_convert.h>

unsigned int GRID_Textures::writeTexture(std::string name, GRID_Vec2i resolution, GRID_TEXTUREFORMAT format, int* data) {
    return textureManager.writeTexture(name, toGLM(resolution), format, data);
}

unsigned int GRID_Textures::loadFromTiff(GRID_Tiff &tiff, std::string name) {
    return textureManager.loadFromTiff(tiff, name);
}

unsigned int GRID_Textures::createTexture(std::string name, GRID_Vec2i resolution, GRID_TEXTUREFORMAT format, int* data) {
    return textureManager.createTexture(name, toGLM(resolution), format, data);
}

void GRID_Textures::deleteTexture(std::string name) {
    textureManager.deleteTexture(name);
}

unsigned int GRID_Textures::getTexture(std::string name) {
    return textureManager.getTexture(name);
}

void GRID_Textures::saveTextureToFile(std::string textureName, std::string fileName, GRID_Vec2i textureResolution, GRID_TEXTUREFORMAT format) {
    textureManager.saveTextureToFile(textureName, fileName, toGLM(textureResolution), format);
}

void GRID_Textures::setTexture(std::string name, GLuint texture) {
    textureManager.setTexture(name, texture);
}