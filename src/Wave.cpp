#include "Wave.h"
#include <utility>
#include <algorithm>
#include <vcruntime.h>

using namespace wfc;

Wave::Wave(int x, int y) {
    this->x = x;
    this->y = y;

    this->entropy = 0;
    this->maxEntropy = 0;
}

void Wave::setEntropies(unsigned int entropy) {
    this->entropy = entropy;
    this->maxEntropy = entropy;
    std::pair<unsigned int, unsigned int> initial(0, entropy);
    this->superposition_indexArr = {initial};
}

unsigned int Wave::getEntropy() {
    return this->entropy;
}

void Wave::addSuperPositionByIndex(int index) {
    // Check if that index exists.
    if (this->isIndexExisting(index)) {
        return; // Do nothing if that index already exists.
    }

    // Look for the position to insert that index.
    // Partition Algorithm
    std::vector<std::pair<unsigned int, unsigned int>>::iterator pos = lookForPosToInsert(index);

    // Check if this index is one unit next to the prev or next element.
    int status = isOneUnitNextToElement(index, pos);
    switch (status) {
        case 0: {
            // Not next to any element.
            std::pair<unsigned int, unsigned int> newPair(index, index);
            superposition_indexArr.push_back(newPair);
            std::sort(superposition_indexArr.begin(), superposition_indexArr.end());
            break;
        }
        case 1: {
            // Next to the prev element
            // Get to the prev pair and change the upper bound.
            pos->second = index;
            break;
        }
        case 2: {
            // Next to the next element
            // Get to the next pair and change the lower bound.
            pos++; // Go to the nex pair
            pos->first = index;
            break;
        }
        case 3: {
            // In between two elements
            // Get the upper bound of the next pair, then change it as the upper bound of the prev pair
            auto ptr = pos;
            pos++;
            unsigned int upper_bound = pos->second;
            ptr->first = upper_bound;
            // Remove the next pair
            superposition_indexArr.erase(pos);
            break;
        }
    }
}

void Wave::removeSuperPositionByIndex(int index) {
    if (!isIndexExisting(index)) {
        return; // Do nothing if the index does not exist
    }

    // Look for the position to remove that index.
    // Partition Algorithm
    std::vector<std::pair<unsigned int, unsigned int>>::iterator pos = lookForPosToErase(index);

    if (index == 0) {
        pos->first = 1;
    } else if (index == this->maxEntropy - 1) {
        pos->second = index - 1;
    } else {
        unsigned int upper_bound = pos->second;
        pos->second = index - 1;
        // Insert a new pair
        std::pair<unsigned int, unsigned int> anotherNewPair{index+1, upper_bound};
        superposition_indexArr.push_back(anotherNewPair);
        std::sort(superposition_indexArr.begin(), superposition_indexArr.end());
    }
}

bool Wave::isIndexExisting(int index) {
    if (superposition_indexArr.empty()) {
        return false;
    }

    size_t starting_pos = superposition_indexArr.size() / 2;
    size_t lower_pos, upper_pos;
    auto mid_element = superposition_indexArr.at(starting_pos);
    if (mid_element.first <= index && mid_element.second >= index) {
        return true; // Return true if it is in the middle element
    } else if (mid_element.first > index) {
        lower_pos = 0;
        upper_pos = starting_pos - 1;
        if (upper_pos < lower_pos) {
            return false; // Return false if mid_element is the first element and does not contain index
        }
    } else {
        lower_pos = starting_pos + 1;
        upper_pos = superposition_indexArr.size() - 1;
        if (lower_pos > upper_pos) {
            return false; // Return false if mid_element is the last element and does not contain index
        }
    }

    // Keep spliting until cannot split anymore
    while (true) {
        if (lower_pos > upper_pos) {
            return false;
        }

        size_t middle_pos = (lower_pos + upper_pos) / 2;
        auto mid_element = superposition_indexArr.at(middle_pos);
        if (mid_element.first <= index && index <= mid_element.second) {
            return true;
        } else if (index < mid_element.first) {
            upper_pos = middle_pos - 1;
        } else {
            lower_pos = middle_pos + 1;
        }
    }
}

std::vector<std::pair<unsigned int, unsigned int>>::iterator Wave::lookForPosToInsert(int index) {
    size_t lower_bound = 0;
    size_t upper_bound = this->superposition_indexArr.size();

    while (true) {
        size_t middle_point = (lower_bound + upper_bound) / 2;

        auto middle_pair = this->superposition_indexArr.at(middle_point);

        if (middle_pair.first <= index && index <= middle_pair.second) {
            return superposition_indexArr.begin() + middle_point;
        } else if (index < middle_pair.first) {
            upper_bound = middle_point - 1;
        } else {
            lower_bound = middle_point + 1;
        }
    }
}