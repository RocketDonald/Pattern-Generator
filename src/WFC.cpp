#include "Wave.h"

using namespace wfc;

Wave::WFC(unsigned int width, unsigned int height, unsigned int N) {
    this->width = width;
    this->height = height;
    this->N = N;

    // Init state_arr to the dimensions of the output
    state_arr = new NxN*[height];
    for (int i = 0; i < height; i++) {
        state_arr[i] = new NxN[width];
    }

    // Initialize the wave in the completely unobserved state
    // i.e., with all the boolean coefficients being true
    bool_coefficients = new bool*[height];
    for (int i = 0; i < height; i++) {
        bool_coefficients[i] = new bool[width];
        for (int j = 0; j < width; j++) {
            bool_coefficients[i][j] = true;
        }
    }    
}