#include "Pixel.h"
#include <iostream>

using namespace std;
using namespace wfc;

Pixel::Pixel() {
    pix = new RGBPixel{255, 255, 255};
}

Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b) {
    pix = new RGBPixel{r, g, b};
}

bool Pixel::operator==(Pixel &that) {
    return  this->get_r() == that.get_r()
    &&      this->get_g() == that.get_g()
    &&      this->get_b() == that.get_b();
}

bool Pixel::operator!=(Pixel &that) {
    return !(*this == that);
}

unsigned char Pixel::get_r() {
    return this->pix->r;
}

unsigned char Pixel::get_g() {
    return this->pix->g;
}

unsigned char Pixel::get_b() {
    return this->pix->b;
}

Pixel::RGBPixel* Pixel::getPixelPtr() {
    return this->pix;
}

void Pixel::setPixel(unsigned char r, unsigned char g, unsigned char b) {
    this->pix->r = r;
    this->pix->g = g;
    this->pix->b = b;
}

/**
 * @brief This operator de-allocate the memory allowed for RGBPixel.
 * Be caution that this operator does not set the RGBPixel to nullptr, which may cause dangling pointer.
 * @param p 
 */
void Pixel::operator delete(void *p) {
    Pixel* tmp = (Pixel*)p;
    delete tmp->getPixelPtr();
}