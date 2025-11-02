#include "benchmark_summary_display.hpp"

#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include "text_colors.hpp"
#include "console_output.hpp"

namespace BenchmarkSummaryDisplay {
    void print(const BenchmarkData::Data& data) {
        ConsoleOutput::enableColors();

        std::cout << TextColors::BRIGHT << TextColors::CYAN
                  << "=== BENCHMARK SUMMARY ===" << TextColors::RESET << "\n\n";

        const int numSizes = static_cast<int>(data.sizes.size());
        const int numAlgorithms = static_cast<int>(data.algorithmNames.size());

        // Lambda to find the fastest algorithm for a given size and array type
        auto findFastest = [&](int sizeIdx, const std::vector<std::vector<double>>& times) {
            int fastestIdx = -1;
            double minTime = std::numeric_limits<double>::max();
            for (int i = 0; i < numAlgorithms; ++i) {
                if (times[sizeIdx][i] > 0.0 && times[sizeIdx][i] < minTime) {
                    minTime = times[sizeIdx][i];
                    fastestIdx = i;
                }
            }
            return std::make_pair(fastestIdx, minTime);
        };

        // Display fastest algorithm for each array type
        for (int sizeIdx = 0; sizeIdx < numSizes; ++sizeIdx) {
            int size = data.sizes[sizeIdx];
            std::cout << TextColors::BRIGHT << "Size: " << size << TextColors::RESET << "\n";

            auto [fastestRandomIdx, timeRandom] = findFastest(sizeIdx, data.randomTimes);
            if (fastestRandomIdx >= 0) {
                std::cout << "  " << TextColors::GREEN << "Fastest on Random arrays: " << TextColors::RESET
                          << TextColors::BRIGHT << data.algorithmNames[fastestRandomIdx] << TextColors::RESET
                          << " (" << std::fixed << std::setprecision(3) << timeRandom << " ms)\n";
            }

            auto [fastestReversedIdx, timeReversed] = findFastest(sizeIdx, data.reversedTimes);
            if (fastestReversedIdx >= 0) {
                std::cout << "  " << TextColors::GREEN << "Fastest on Reversed arrays: " << TextColors::RESET
                          << TextColors::BRIGHT << data.algorithmNames[fastestReversedIdx] << TextColors::RESET
                          << " (" << std::fixed << std::setprecision(3) << timeReversed << " ms)\n";
            }

            auto [fastestSortedIdx, timeSorted] = findFastest(sizeIdx, data.sortedTimes);
            if (fastestSortedIdx >= 0) {
                std::cout << "  " << TextColors::GREEN << "Fastest on Sorted arrays: " << TextColors::RESET
                          << TextColors::BRIGHT << data.algorithmNames[fastestSortedIdx] << TextColors::RESET
                          << " (" << std::fixed << std::setprecision(3) << timeSorted << " ms)\n";
            }

            std::cout << "\n";
        }
    }
}

