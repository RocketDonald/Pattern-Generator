namespace wfc {
    class Pixel {
        public:
            struct RGBPixel {
                unsigned char r;
                unsigned char g;
                unsigned char b;
            };

            Pixel();    // Default empty constructor constructs a white pixel {255, 255, 255}
            Pixel(unsigned char r, unsigned char g, unsigned char b);

            bool operator == (Pixel& that);
            bool operator != (Pixel& that);

            unsigned char get_r();
            unsigned char get_g();
            unsigned char get_b();

            RGBPixel* getPixelPtr();

            void setPixel(unsigned char r, unsigned char g, unsigned char b);

            void operator delete(void* p);
        private:
            RGBPixel* pix = nullptr;
    };
}