#pragma once

#include <vector>
#include <string>

// Namespace for formatting and displaying benchmark result tables
namespace TableFormatter {
    void printTable(const std::string& typeName,
                    const std::vector<std::vector<double>>& times,
                    const std::vector<std::vector<bool>>& validation,
                    const std::vector<std::string>& algorithmNames,
                    const std::vector<int>& sizes);
}

