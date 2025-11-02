#include "benchmark_data.hpp"

#include "benchmark_progress.hpp"
#include "benchmark_algorithm_runner.hpp"
#include "console_output.hpp"

namespace BenchmarkData {
    // Collects benchmark data by running all sorting algorithms on all array sizes and types
    Data collect(const std::vector<int>& sizes) {
        ConsoleOutput::clearScreen();
        BenchmarkProgress::initialize();

        Data data;
        data.sizes = sizes;
        data.algorithmNames = {"Merge", "Quick", "Insertion", "Selection", "Revised bubble", "Bubble"};

        const int numAlgorithms = static_cast<int>(data.algorithmNames.size());
        const int numSizes = static_cast<int>(sizes.size());
        const int totalOperations = numSizes * numAlgorithms * 3; // 3 array types per algorithm

        // Initialize data structures to store timing and validation results
        data.randomTimes.resize(numSizes, std::vector<double>(numAlgorithms, 0.0));
        data.reversedTimes.resize(numSizes, std::vector<double>(numAlgorithms, 0.0));
        data.sortedTimes.resize(numSizes, std::vector<double>(numAlgorithms, 0.0));
        data.randomOk.resize(numSizes, std::vector<bool>(numAlgorithms, false));
        data.reversedOk.resize(numSizes, std::vector<bool>(numAlgorithms, false));
        data.sortedOk.resize(numSizes, std::vector<bool>(numAlgorithms, false));

        int currentOperation = 0;

        // Run benchmarks for each array size
        for (int sizeIdx = 0; sizeIdx < numSizes; ++sizeIdx) {
            int N = sizes[sizeIdx];
            BenchmarkAlgorithmRunner::runForSize(sizeIdx, N, data, currentOperation, totalOperations);
        }

        BenchmarkProgress::clearProgress();
        return data;
    }
}
