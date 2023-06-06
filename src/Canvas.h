#include "Pixel.h"
#include <string>

namespace wfc {
    class Canvas{
        public:
            Canvas();
            Canvas(unsigned int width, unsigned int height);

            unsigned int getWidth();
            unsigned int getHeight();
            Pixel getPixel(unsigned int x, unsigned int y);
            void setPixel(unsigned int x, unsigned int y, Pixel p);
            void setPixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b);

            void read(std::string fileName);
            void draw(std::string fileName);

        private:
            unsigned int width;
            unsigned int height;
            Pixel** pix_2d;

            // A method for asserting whether x and y are both in a valid range
            void checkValid(unsigned int x, unsigned int y);
            
            // A method that convert the pix_2d array into a void* array
            void* pixToDataPtr();
    };
}