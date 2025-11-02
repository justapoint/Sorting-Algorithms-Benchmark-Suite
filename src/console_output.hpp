#pragma once

// Namespace for console output utilities (colors, screen clearing, sizing)
namespace ConsoleOutput {
    void enableColors();
    void clearScreen();
    void setSize(int width, int height);
    void setBufferSize(int width, int height);
}

