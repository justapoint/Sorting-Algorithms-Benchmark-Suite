#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include "console_output.hpp"
#include "benchmark_runner.hpp"

// Clears the current line by overwriting it with spaces and returning to beginning
static void clearCurrentLine() {
    std::cout << "\r" << std::string(120, ' ') << "\r" << std::flush;
}

// Converts a string to lowercase for case-insensitive comparison
static std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

int main() {
    // Array sizes to test
    std::vector<int> sizes = {1000, 5000, 10000, 25000, 50000};
    
    // Calculate required buffer size based on number of sizes
    // Each table: header (3 lines) + algorithm rows (6 lines) + spacing (2 lines) = ~11 lines per table
    // 3 tables (random, reversed, sorted) = ~33 lines
    // Summary: ~15 lines (5 per size)
    // Progress/other output: ~10 lines
    // Total base: ~60 lines, add extra buffer for safety
    int numSizes = static_cast<int>(sizes.size());
    int requiredBufferHeight = 150 + (numSizes * 25);  // Generous buffer for scrolling
    int requiredBufferWidth = 120;  // Width is sufficient, tables auto-wrap if needed
    
    // Initialize console window size (visible area)
    ConsoleOutput::setSize(120, 60);
    
    // Set larger buffer size to allow scrolling
    ConsoleOutput::setBufferSize(requiredBufferWidth, requiredBufferHeight);
    
    // Run sorting benchmarks with different array sizes
    std::cout << "Starting sorting benchmark..." << std::endl;
    std::cout << "Please wait while algorithms are being tested..." << std::endl << std::endl;
    BenchmarkRunner::run(sizes);

    // Wait for user input to exit the program
    std::string input;
    std::string prompt = "Type 'exit' to close the program: ";

    while (true) {
        std::cout << prompt << std::flush;
        if (!std::getline(std::cin, input)) {
            break;
        }
        std::string lowerInput = toLower(input);
        if (lowerInput == "exit") {
            break;
        }
        clearCurrentLine();
    }

    return 0;
}