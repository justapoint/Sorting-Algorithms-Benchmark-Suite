#include "benchmark_progress.hpp"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

namespace BenchmarkProgress {
    // Enables ANSI color support on Windows console
    static void enableAnsiColors() {
#ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE) {
            DWORD dwMode = 0;
            if (GetConsoleMode(hOut, &dwMode)) {
                dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                SetConsoleMode(hOut, dwMode);
            }
        }
#endif
    }

    // Initializes progress display system
    void initialize() {
        enableAnsiColors();
    }

    // Displays current progress percentage
    void showProgress(int current, int total) {
        int percent = 0;
        if (total > 0) {
            percent = (current * 100) / total;
        }
        std::cout << "\rProgress: [" << current << "/" << total << "] (" << percent << "%)" << std::flush;
    }

    // Clears the progress line
    void clearProgress() {
        std::cout << "\r" << std::string(120, ' ') << "\r" << std::flush;
    }
}

