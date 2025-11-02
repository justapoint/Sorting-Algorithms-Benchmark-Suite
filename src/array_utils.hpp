#pragma once

#include <vector>

// Utility class for generating test arrays with different characteristics
class ArrayGenerator {

    public:
        static std::vector<int> getRandomArray(int size);
        static std::vector<int> getReversedArray(int size);
        static std::vector<int> getSortedArray(int size);
};

// Utility class for array validation operations
class ArrayUtils {

    public:
        static bool isSorted(const std::vector<int>& array);
};
