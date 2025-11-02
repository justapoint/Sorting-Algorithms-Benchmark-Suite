#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include "sorting/base_sorter.hpp"

namespace SortBench {
    // RAII helper to suppress cout output during sorting operations
    struct SilenceCout {
        std::ostringstream sink;
        std::streambuf* oldBuf;
        SilenceCout() : sink(), oldBuf(std::cout.rdbuf(sink.rdbuf())) {}
        ~SilenceCout() { std::cout.rdbuf(oldBuf); }
    };

    double runAndTime(BaseSorter* sorter, const std::vector<int>& src, bool& ok_out);
}
