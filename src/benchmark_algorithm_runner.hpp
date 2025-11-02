#pragma once

#include "benchmark_data.hpp"

// Namespace for running individual algorithm benchmarks
namespace BenchmarkAlgorithmRunner {
    void runForSize(int sizeIdx, int N, BenchmarkData::Data& data, int& currentOperation, int totalOperations);
}

