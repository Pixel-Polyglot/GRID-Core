#include <GRID/GRID_textures.h>
#include <textureManager.h>

GLuint GRID_Textures::writeTexture(std::string name, int width, int height, GRID_TEXTUREFORMAT format, int* data) {
    return textureManager.writeTexture(name, width, height, format, data);
}

GLuint GRID_Textures::loadFromTiff(GRID_Tiff &tiff, std::string name) {
    return textureManager.loadFromTiff(tiff, name);
}

GLuint GRID_Textures::createTexture(std::string name, int width, int height, GRID_TEXTUREFORMAT format, int* data) {
    return textureManager.createTexture(name, width, height, format, data);
}

GLuint GRID_Textures::getTexture(std::string name) {
    return textureManager.getTexture(name);
}

void GRID_Textures::saveTextureToFile(std::string textureName, std::string fileName, int width, int height, GRID_TEXTUREFORMAT format, int sizeX, int sizeY, int offsetX, int offsetY) {
    textureManager.saveTextureToFile(textureName, fileName, width, height, format, sizeX, sizeY, offsetX, offsetY);
}

void GRID_Textures::setTexture(std::string name, GLuint texture) {
    textureManager.setTexture(name, texture);
}