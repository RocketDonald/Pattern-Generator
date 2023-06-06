#include "Wave.h"

/**
 * @brief The pool consists of N*N waves.
 * The pool also stores all the possibilities of waves.
 */
namespace wfc {
    class Pool {
        public:
            Pool(int width, int height);
            
            // A function that pre-calculate all the possible connections before collapsing the waves.
            // Should be called at the beginning, right after loading all the superpositions.
            void socketConnections_preprocess();
        private:
    };
}