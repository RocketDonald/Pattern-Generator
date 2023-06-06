#include "Canvas.h"
#include <iostream>
#include <cassert>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace wfc;
using namespace std;

Canvas::Canvas() {
    this->width = 0;
    this->height = 0;
    pix_2d = nullptr;
}

Canvas::Canvas(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;

    // Initialize 2D pixel array
    // pix_2d[x][y]
    pix_2d = new Pixel*[width];

    for(unsigned int i = 0; i < width; i++) {
        pix_2d[i] = new Pixel[height];
    }

    //  Fill the 2D pixel array with white color
    for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < height; j++) {
            pix_2d[i][j] = Pixel();
        }
    }
}


unsigned int Canvas::getWidth() {
    return this->width;
}

unsigned int Canvas::getHeight() {
    return this->height;
}

void Canvas::checkValid(unsigned int x, unsigned int y) {
    assert(x < width && "x should be smaller than the width");
    assert(y < height && "y should be smaller than the height");
}

Pixel Canvas::getPixel(unsigned int x, unsigned int y) {
    checkValid(x, y);
    return pix_2d[x][y];
}

void Canvas::setPixel(unsigned int x, unsigned int y, Pixel p) {
    checkValid(x, y);

    // Set the pixel if this is a different pixel
    if (pix_2d[x][y] != p) {
        // De-allocate the RGBPixel pointer within the Pixel class
        delete pix_2d[x][y].getPixelPtr();
        pix_2d[x][y] = p;
    }
}

void Canvas::setPixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) {
    checkValid(x, y);
    Pixel p = Pixel(r, g, b);
    setPixel(x, y, p);
}

void* Canvas::pixToDataPtr() {
    Pixel::RGBPixel* pixData = new Pixel::RGBPixel[width * height];

    for (unsigned int i = 0; i < height; i ++) {
        for (unsigned int j = 0; j < width; j++) {
            pixData[i * height + j] = *(pix_2d[j][i].getPixelPtr());
        }
    }

    return (void*) pixData;
}

void Canvas::read(std::string fileName) {
    int width, height, channels;
    unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &channels, 3);
    cout << "Width: " << width << " | Height: " << height << " | Channels: " << channels << endl;

    cout << (int) data[0] << " " << (int)data[1] << " " << (int) data[2] << endl; // [255, 255, 255]

    // Init this canvas
    this->width = width;
    this->height = height;

    // Init pix_2d
    pix_2d = new Pixel*[height];
    for (int i = 0; i < height; i++) {
        pix_2d[i] = new Pixel[width];
    } 

    // Load data into pix_2d
    int data_counter = 0; // For counting the current data index
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            unsigned char* channel_data = new unsigned char[channels];
            for (int k = 0; k < channels; k++) {
                // Read each channel 
                channel_data[k] = data[data_counter];
                data_counter++;

                // Create a pixel every 3 channels
                if (k % 3 == 2) {
                    pix_2d[j][i] = Pixel(channel_data[0], channel_data[1], channel_data[2]);

                    // cout << (int) channel_data[0] << " " << (int) channel_data[1] << " " << (int) channel_data[2] << endl;
                }
            }
        }
    }

    stbi_image_free(data);
}

void Canvas::draw(std::string fileName) {
    void* data = pixToDataPtr();
    // cout << (int) ((unsigned char*)data)[0] << " " << (int)((unsigned char*)data)[1] << " " << (int) ((unsigned char*)data)[2] << endl;
    int status = stbi_write_png(fileName.c_str(), (int) width, (int) height, 3, data, 0);
    assert(status != 0 && "Draw failed");
}

