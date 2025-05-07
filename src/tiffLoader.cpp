#include <GRID/tiffLoader.h>
#include <tinytiffreader.h>
#include <iostream>

Tiff::Tiff(std::string filePath) {
    load(filePath);
}

Tiff::~Tiff() {
    free(image);
}

uint8_t* Tiff::getImage() {
    return image;
}

uint32_t Tiff::getWidth() {
    return width;
}

uint32_t Tiff::getHeight() {
    return height;
}

uint32_t Tiff::getBitsPerSample() {
    return bitsPerSample;
}

uint32_t Tiff::getSamplesPerPixel() {
    return samplesPerPixel;
}

TIFF_SAMPLEFORMAT Tiff::getSampleFormat() {
    return sampleFormat;
}

void Tiff::load(std::string filePath) {
    TinyTIFFReaderFile* tiffr = NULL;
    tiffr = TinyTIFFReader_open(filePath.c_str()); 
    if (!tiffr) { 
        std::cout << "Tiff file:" << filePath.c_str() << " not existent, not accessible or not a TIFF file)" << std::endl; 
    } else { 
        width = TinyTIFFReader_getWidth(tiffr);
        height = TinyTIFFReader_getHeight(tiffr);
        bitsPerSample = TinyTIFFReader_getBitsPerSample(tiffr, 0);
        samplesPerPixel = TinyTIFFReader_getSamplesPerPixel(tiffr);
        sampleFormat = (TIFF_SAMPLEFORMAT)TinyTIFFReader_getSampleFormat(tiffr);

        image = (uint8_t*)calloc(width * height * samplesPerPixel, bitsPerSample / 8);  
        if (!TinyTIFFReader_getSampleData(tiffr, image, 0)) {
            std::cout << TinyTIFFReader_getLastError(tiffr) << std::endl;
        }
    } 
    TinyTIFFReader_close(tiffr); 
}