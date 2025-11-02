#pragma once

// Namespace for displaying benchmark progress
namespace BenchmarkProgress {
    void initialize();
    void showProgress(int current, int total);
    void clearProgress();
}

