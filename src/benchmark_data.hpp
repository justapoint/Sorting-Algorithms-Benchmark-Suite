#pragma once

#include <vector>
#include <string>

namespace BenchmarkData {
    // Structure to store all benchmark results
    struct Data {
        std::vector<int> sizes;                                    // Array sizes tested
        std::vector<std::string> algorithmNames;                   // Names of sorting algorithms
        std::vector<std::vector<double>> randomTimes;              // Time results for random arrays [sizeIdx][algoIdx]
        std::vector<std::vector<double>> reversedTimes;            // Time results for reversed arrays
        std::vector<std::vector<double>> sortedTimes;              // Time results for sorted arrays
        std::vector<std::vector<bool>> randomOk;                   // Validation results for random arrays
        std::vector<std::vector<bool>> reversedOk;                 // Validation results for reversed arrays
        std::vector<std::vector<bool>> sortedOk;                   // Validation results for sorted arrays
    };

    Data collect(const std::vector<int>& sizes);
}

