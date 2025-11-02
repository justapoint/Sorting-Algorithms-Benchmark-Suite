#include "table_formatter.hpp"

#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
#include <algorithm>
#include "text_colors.hpp"

namespace TableFormatter {
    // Determines color for time display based on performance relative to min/max
    static const char* getTimeColor(double time, double minTime, double maxTime) {
        if (maxTime <= minTime) return TextColors::RESET;
        double ratio = (time - minTime) / (maxTime - minTime);
        if (ratio < 0.2) return TextColors::GREEN;   // Fastest 20%
        if (ratio > 0.8) return TextColors::RED;     // Slowest 20%
        return TextColors::YELLOW;                     // Middle 60%
    }

    // Prints a formatted table with timing results for all algorithms and sizes
    void printTable(const std::string& typeName,
                    const std::vector<std::vector<double>>& times,
                    const std::vector<std::vector<bool>>& validation,
                    const std::vector<std::string>& algorithmNames,
                    const std::vector<int>& sizes) {
        const int nameWidth = 18;
        const int colWidth = 12;
        const int numSizes = static_cast<int>(sizes.size());
        const int numAlgorithms = static_cast<int>(algorithmNames.size());

        // Print table header
        std::cout << "\n" << TextColors::BRIGHT << TextColors::CYAN
                  << "[ " << typeName << " ARRAYS ]" << TextColors::RESET << "\n";
        std::cout << std::string(80, '-') << "\n";

        std::cout << std::left << std::setw(nameWidth) << "Algorithm";
        for (int i = 0; i < numSizes; ++i) {
            std::cout << std::setw(colWidth) << ("Size " + std::to_string(sizes[i]));
        }
        std::cout << "\n" << std::string(80, '-') << "\n";

        // Print each algorithm's results
        for (int algoIdx = 0; algoIdx < numAlgorithms; ++algoIdx) {
            std::cout << std::left << std::setw(nameWidth) << algorithmNames[algoIdx];

            for (int sizeIdx = 0; sizeIdx < numSizes; ++sizeIdx) {
                // Find min and max times for this size (for color coding)
                double minTime = std::numeric_limits<double>::max();
                double maxTime = 0.0;
                for (int i = 0; i < numAlgorithms; ++i) {
                    if (times[sizeIdx][i] > 0.0) {
                        minTime = std::min(minTime, times[sizeIdx][i]);
                        maxTime = std::max(maxTime, times[sizeIdx][i]);
                    }
                }

                double time = times[sizeIdx][algoIdx];
                bool isValid = validation[sizeIdx][algoIdx];

                // Print time with appropriate color and validation indicator
                if (time > 0.0) {
                    const char* color = getTimeColor(time, minTime, maxTime);
                    std::ostringstream oss;
                    oss << std::fixed << std::setprecision(3) << time << " ms";
                    if (!isValid) {
                        oss << " [!]";  // Mark invalid results
                    }
                    std::cout << color << std::setw(colWidth) << oss.str() << TextColors::RESET;
                } else {
                    std::cout << std::setw(colWidth) << "N/A";
                }
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}

