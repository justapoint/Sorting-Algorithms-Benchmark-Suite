#include "benchmark_runner.hpp"

#include <iostream>
#include "benchmark_data.hpp"
#include "benchmark_summary_display.hpp"
#include "benchmark_tables_display.hpp"
#include "console_output.hpp"

namespace BenchmarkRunner {
    // Main benchmark runner: collects data and displays results
    void run(const std::vector<int>& sizes) {
        BenchmarkData::Data data = BenchmarkData::collect(sizes);
        ConsoleOutput::clearScreen();
        BenchmarkSummaryDisplay::print(data);
        std::cout << "\n" << std::string(80, '=') << "\n\n";
        BenchmarkTablesDisplay::print(data);
    }
}

