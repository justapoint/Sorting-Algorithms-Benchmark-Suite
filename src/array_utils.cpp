#include "array_utils.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Generates an array of random integers in range [1, size]
std::vector<int> ArrayGenerator::getRandomArray (int size) {
    std::vector<int> result(size);

    srand(time(0));

    for (int i = 0; i < size; i++) {
        result[i] = rand() % size + 1;
    }

    return result;
}

// Generates an array with values in descending order (size, size-1, ..., 1)
std::vector<int> ArrayGenerator::getReversedArray (int size) {
    std::vector<int> result(size);

    for (int i = 0; i < size; i++) {
        result[i] = size - i;
    }

    return result;
}

// Generates an array with values in ascending order (1, 2, ..., size)
std::vector<int> ArrayGenerator::getSortedArray (int size) {
    std::vector<int> result(size);
    for (int i = 0; i < size; i++) {
        result[i] = i + 1;
    }
    return result;
}

// Checks if an array is sorted in ascending order
bool ArrayUtils::isSorted(const std::vector<int>& array) {
    for (int i = 0; i < array.size() - 1; i++) {
        if (i + 1 < array.size() && array[i] > array[i + 1]) {
            return false;
        }
    }
    return true;
}

