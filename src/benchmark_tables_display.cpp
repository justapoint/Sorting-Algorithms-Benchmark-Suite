#include "benchmark_tables_display.hpp"

#include "table_formatter.hpp"
#include "console_output.hpp"

namespace BenchmarkTablesDisplay {
    // Displays detailed benchmark tables for all array types
    void print(const BenchmarkData::Data& data) {
        ConsoleOutput::enableColors();

        TableFormatter::printTable("RANDOM", data.randomTimes, data.randomOk,
                                   data.algorithmNames, data.sizes);
        TableFormatter::printTable("REVERSED", data.reversedTimes, data.reversedOk,
                                   data.algorithmNames, data.sizes);
        TableFormatter::printTable("SORTED", data.sortedTimes, data.sortedOk,
                                   data.algorithmNames, data.sizes);
    }
}
