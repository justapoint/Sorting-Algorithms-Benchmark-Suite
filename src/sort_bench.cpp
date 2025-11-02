#include "sort_bench.hpp"

#include <chrono>
#include <iostream>
#include <sstream>
#include <vector>

#include "array_utils.hpp"

// Runs a sorting algorithm and measures execution time, validates result
double SortBench::runAndTime(BaseSorter* sorter, const std::vector<int>& src, bool& ok_out) {
    auto arr = src;
    SilenceCout silence;  // Suppresses output during sorting
    auto start = std::chrono::high_resolution_clock::now();
    auto sorted = sorter->sort(arr);
    auto end = std::chrono::high_resolution_clock::now();
    ok_out = ArrayUtils::isSorted(sorted);
    return std::chrono::duration<double, std::milli>(end - start).count();
}
