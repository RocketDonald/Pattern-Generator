#include "Pixel.h"

/**
 * @brief Each superposition represents a tile. 
 * Each tile has sockets that allow it to connect with other superpositions.
 * A socket has an index and a color pixel. Superposition can connect if both sockets have the same color.
 */
namespace wfc{
    class SuperPosition {
        public:
            // The input tile will be read by tile_reader.cpp
            SuperPosition(Pixel** tile);

        private:
            Pixel** tile;
    };
}