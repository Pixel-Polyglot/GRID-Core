#include <textureManager.h>
#include <iostream>
#include <tinytiffwriter.h>

TextureManager textureManager = TextureManager();

TextureManager::TextureManager() {
}

TextureManager::~TextureManager() {
}

GLuint TextureManager::writeTexture(std::string name, int width, int height, GRID_TEXTUREFORMAT format, int* data) {
    if (textures.find(name) == textures.end()) {
        std::cout << "Texture with name: " << name << " doesn't exists" << std::endl;
        return 0;
    }

	glBindTexture(GL_TEXTURE_2D, textures[name]);

    int layout;
    int pixelType;
    int elementType;
    switch (format) {
        case GRID_TEXTUREFORMAT::R8:
            layout = GL_R8;
            pixelType = GL_RED;
            elementType = GL_UNSIGNED_BYTE;
            break;
        case GRID_TEXTUREFORMAT::R8UI:
            layout = GL_R8UI;
            pixelType = GL_RED_INTEGER;
            elementType = GL_UNSIGNED_BYTE;
            break;
        case GRID_TEXTUREFORMAT::RGBA8:
            layout = GL_RGBA8;
            pixelType = GL_RGBA;
            elementType = GL_UNSIGNED_BYTE;
            break;
        case GRID_TEXTUREFORMAT::RGBA8UI:
            layout = GL_RGBA8UI;
            pixelType = GL_RGBA_INTEGER;
            elementType = GL_UNSIGNED_BYTE;
            break;
        case GRID_TEXTUREFORMAT::RGBA16F:
            layout = GL_RGBA16F;
            pixelType = GL_RGBA;
            elementType = GL_HALF_FLOAT;
            break;
        case GRID_TEXTUREFORMAT::RGBA16UI:
            layout = GL_RGBA16UI;
            pixelType = GL_RGBA_INTEGER;
            elementType = GL_UNSIGNED_SHORT;
            break;
        case GRID_TEXTUREFORMAT::R16F:
            layout = GL_R16F;
            pixelType = GL_RED;
            elementType = GL_HALF_FLOAT;
            break;
        case GRID_TEXTUREFORMAT::R16UI:
            layout = GL_R16UI;
            pixelType = GL_RED_INTEGER;
            elementType = GL_UNSIGNED_SHORT;
            break;
        case GRID_TEXTUREFORMAT::RGBA32F:
            layout = GL_RGBA32F;
            pixelType = GL_RGBA;
            elementType = GL_FLOAT;
            break;
        case GRID_TEXTUREFORMAT::R32UI:
            layout = GL_R32UI;
            pixelType = GL_RED_INTEGER;
            elementType = GL_UNSIGNED_INT;
            break;
        case GRID_TEXTUREFORMAT::RGBA32UI:
            layout = GL_RGBA32UI;
            pixelType = GL_RGBA_INTEGER;
            elementType = GL_UNSIGNED_INT;
            break;
        default:
            std::cout << "Invalid texture format" << std::endl;
            return 0;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, layout, width, height, 0, pixelType, elementType, data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return textures[name];
}

void TextureManager::setTexture(std::string name, GLuint texture) {
    if (textures.find(name) != textures.end()) {
        std::cout << "Texture with name: " << name << " already exists" << std::endl;
        return;
    }

    textures[name] = texture;
}

GLuint TextureManager::createTexture(std::string name, int width, int height, GRID_TEXTUREFORMAT format, int* data) {
    if (textures.find(name) != textures.end()) {
        std::cout << "Texture with name: " << name << " already exists" << std::endl;
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    textures[name] = texture;

    return writeTexture(name, width, height, format, data);
}

GLuint TextureManager::getTexture(std::string name) {
    if (textures.find(name) == textures.end()) {
        std::cout << "Texture with name: " << name << " does not exist" << std::endl;
        return 0;
    }
    return textures[name];
}

GLuint TextureManager::loadFromTiff(GRID_Tiff &tiff, std::string name) {
    if (textures.find(name) != textures.end()) {
        std::cout << "Texture with name: " << name << " already exists" << std::endl;
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    if (tiff.getSampleFormat() == GRID_TIFFFORMAT::TIFF_UINT) {
        if (tiff.getBitsPerSample() == 16) {
            if (tiff.getSamplesPerPixel() == 3) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16UI, tiff.getWidth(), tiff.getHeight(), 0, GL_RGB_INTEGER, GL_UNSIGNED_SHORT, tiff.getImage());
            }
            else if (tiff.getSamplesPerPixel() == 1) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_R16UI, tiff.getWidth(), tiff.getHeight(), 0, GL_RED_INTEGER, GL_UNSIGNED_SHORT, tiff.getImage());
            }
            else {        
                std::cout << "Tiff is neither 3 or 1 channel" << std::endl;
            }
        }
        else {
            std::cout << "Tiff samples are not 16 bit" << std::endl;
        }
    }
    else {
        std::cout << "Tiff samples are not in UINT format" << std::endl;
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    textures[name] = texture;

    return texture;
}

void TextureManager::saveTextureToFile(std::string textureName, std::string fileName, int width, int height, GRID_TEXTUREFORMAT format, int sizeX, int sizeY, int offsetX, int offsetY) {
    if (sizeX == 0) {
        sizeX = width;
    }

    if (sizeY == 0) {
        sizeY = height;
    }
    
    int pixelType;
    int elementType;
    
    int bits;
    TinyTIFFWriterSampleFormat sampleFormat;
    TinyTIFFWriterSampleInterpretation sampleInterpretation;
    int channels;

    void* pixels = nullptr;

    switch (format) {
            case GRID_TEXTUREFORMAT::R8:
            pixelType = GL_RED;
            elementType = GL_UNSIGNED_BYTE;
            bits = 8;
            sampleFormat = TinyTIFFWriter_Float;
            sampleInterpretation = TinyTIFFWriter_Greyscale;
            channels = 1;
            pixels = malloc(sizeof(uint8_t)*width*height);
            break;
        case GRID_TEXTUREFORMAT::R8UI:
            pixelType = GL_RED_INTEGER;
            elementType = GL_UNSIGNED_BYTE;
            bits = 8;
            sampleFormat = TinyTIFFWriter_UInt;
            sampleInterpretation = TinyTIFFWriter_Greyscale;
            channels = 1;
            pixels = malloc(sizeof(uint8_t)*width*height);
            break;
        case GRID_TEXTUREFORMAT::RGBA8:
            pixelType = GL_RGBA;
            elementType = GL_UNSIGNED_BYTE;
            bits = 8;
            sampleFormat = TinyTIFFWriter_Float;
            sampleInterpretation = TinyTIFFWriter_RGB;
            channels = 4;
            pixels = malloc(sizeof(uint8_t)*width*height*4);
            break;
        case GRID_TEXTUREFORMAT::RGBA8UI:
            pixelType = GL_RGBA_INTEGER;
            elementType = GL_UNSIGNED_BYTE;
            bits = 8;
            sampleFormat = TinyTIFFWriter_UInt;
            sampleInterpretation = TinyTIFFWriter_RGB;
            channels = 4;
            pixels = malloc(sizeof(uint8_t)*width*height*4);
            break;
        case GRID_TEXTUREFORMAT::RGBA16F:
            pixelType = GL_RGBA;
            elementType = GL_HALF_FLOAT;
            bits = 16;
            sampleFormat = TinyTIFFWriter_Float;
            sampleInterpretation = TinyTIFFWriter_RGB;
            channels = 4;
            pixels = malloc(sizeof(uint16_t)*width*height*4);
            break;
        case GRID_TEXTUREFORMAT::RGBA16UI:
            pixelType = GL_RGBA_INTEGER;
            elementType = GL_UNSIGNED_SHORT;
            bits = 16;
            sampleFormat = TinyTIFFWriter_UInt;
            sampleInterpretation = TinyTIFFWriter_RGB;
            channels = 4;
            pixels = malloc(sizeof(uint16_t)*width*height*4);
            break;
        case GRID_TEXTUREFORMAT::R16F:
            pixelType = GL_RED;
            elementType = GL_HALF_FLOAT;
            bits = 16;
            sampleFormat = TinyTIFFWriter_Float;
            sampleInterpretation = TinyTIFFWriter_Greyscale;
            channels = 1;
            pixels = malloc(sizeof(uint16_t)*width*height);
            break;
        case GRID_TEXTUREFORMAT::R16UI:
            pixelType = GL_RED_INTEGER;
            elementType = GL_UNSIGNED_SHORT;
            bits = 16;
            sampleFormat = TinyTIFFWriter_UInt;
            sampleInterpretation = TinyTIFFWriter_Greyscale;
            channels = 1;
            pixels = malloc(sizeof(uint16_t)*width*height);
            break;
        case GRID_TEXTUREFORMAT::RGBA32F:
            pixelType = GL_RGBA;
            elementType = GL_FLOAT;
            bits = 32;
            sampleFormat = TinyTIFFWriter_Float;
            sampleInterpretation = TinyTIFFWriter_RGB;
            channels = 4;
            pixels = malloc(sizeof(uint32_t)*width*height*4);
            break;
        case GRID_TEXTUREFORMAT::R32UI:
            pixelType = GL_RED_INTEGER;
            elementType = GL_UNSIGNED_INT;
            bits = 32;
            sampleFormat = TinyTIFFWriter_UInt;
            sampleInterpretation = TinyTIFFWriter_RGB;
            channels = 1;
            pixels = malloc(sizeof(uint32_t)*width*height);
            break;
        case GRID_TEXTUREFORMAT::RGBA32UI:
            pixelType = GL_RGBA_INTEGER;
            elementType = GL_UNSIGNED_INT;
            bits = 32;
            sampleFormat = TinyTIFFWriter_UInt;
            sampleInterpretation = TinyTIFFWriter_RGB;
            channels = 4;
            pixels = malloc(sizeof(uint32_t)*width*height*4);
            break;
        default:
            std::cout << "Invalid texture format" << std::endl;
            return;
    }
    
    if (pixels == nullptr) {
        std::cout << "Failed to allocate memory for texture pixels" << std::endl;
        return;
    }

	glBindTexture(GL_TEXTURE_2D, getTexture(textureName));
    glGetTexImage(GL_TEXTURE_2D, 0, pixelType, elementType, pixels);

    TinyTIFFWriterFile* tif=TinyTIFFWriter_open(fileName.c_str(), bits, sampleFormat, channels, sizeX + offsetX, sizeY + offsetY, sampleInterpretation);
    if (tif) {
        TinyTIFFWriter_writeImage(tif, pixels);
        TinyTIFFWriter_close(tif);
    }

    free(pixels);
}