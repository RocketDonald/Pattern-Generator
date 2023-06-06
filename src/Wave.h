/**
 * @file Wave.h
 * @author 
 * @brief Create an array with the dimensions of the output (called "wave" in the source).
 * Each element of this array represents a state of an NxN region in the output
 * @version 0.1
 * @date 2023-05-31
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <vector>
#include <iterator>
#include "SuperPosition.h"

/**
 * @brief This wave contains all the superposition of the tiles.
 * All superpositions will be loaded in a static const arr.
 * Each wave will contain an index array to identify which superposition is availiable.
 */
 namespace wfc{
    class Wave {
        public:
            bool explored; 

            Wave(int x, int y);

            void setEntropies(unsigned int entropy);

            unsigned int getEntropy(); // Returns the total entropy for priority queue

            void addSuperPositionByIndex(int index);
            void removeSuperPositionByIndex(int index);

        private:
            // Coordinate x and y
            int x;
            int y;

            // Entropy == Num of available superpositions
            unsigned int entropy;
            unsigned int maxEntropy; // To record the max entropy for looking for the max index

            // superposition index array with the dimensions of the output
            // The indexs will be stored in a data structure that only indicate the range of int that in the domain.
            // For example, if index 0-24 and 26-52 are in the wave, this data structure will represent the index
            // by {<0, 24>, <26, 52>}. 
            // This data structure must always be sorted.
            std::vector<std::pair<unsigned int, unsigned int>> superposition_indexArr; 

            // Time Complexity: O(log n)
            bool isIndexExisting(int index);

            // Helper function that look for the position to insert the index.
            // It uses recurrsive partition algorithm.
            // Returns an iterator of the prev element.
            // Pre-condition: index does not exist in the arr
            std::vector<std::pair<unsigned int, unsigned int>>::iterator lookForPosToInsert(int index);

            // Pre-condition: index exists in the arr
            std::vector<std::pair<unsigned int, unsigned int>>::iterator lookForPosToErase(int index);

            // Return 0 if not next to any element.
            // Return 1 if next to prev element.
            // Return 2 if next to next element.
            // Return 3 if in between two elements.
            int isOneUnitNextToElement(int index,  std::vector<std::pair<unsigned int, unsigned int>>::iterator pos);
    };
 }