#include "console_output.hpp"

#include <iostream>
#include <cstdlib>

#ifdef _WIN32
#include <windows.h>
#endif

namespace ConsoleOutput {
    // Enables ANSI color support on Windows console
    void enableColors() {
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

    // Clears the console screen (cross-platform)
    void clearScreen() {
#ifdef _WIN32
        std::system("cls");
#else
        std::system("clear");
#endif
    }

    // Sets console window size (cross-platform)
    void setSize(int width, int height) {
#ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE) {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(hOut, &csbi);
            SHORT maxWidth = csbi.dwMaximumWindowSize.X;
            SHORT maxHeight = csbi.dwMaximumWindowSize.Y;
            COORD size;
            size.X = static_cast<SHORT>(width);
            size.Y = static_cast<SHORT>(height);
            if (size.X > maxWidth) size.X = maxWidth;
            if (size.Y > maxHeight) size.Y = maxHeight;
            SetConsoleScreenBufferSize(hOut, size);
            SMALL_RECT rect;
            rect.Left = 0;
            rect.Top = 0;
            rect.Right = static_cast<SHORT>(size.X - 1);
            rect.Bottom = static_cast<SHORT>(size.Y - 1);
            if (!SetConsoleWindowInfo(hOut, TRUE, &rect)) {
                rect.Right = maxWidth - 1;
                rect.Bottom = maxHeight - 1;
                SetConsoleWindowInfo(hOut, TRUE, &rect);
            }
        }
#else
        std::cout << "\033[8;" << height << ";" << width << "t" << std::flush;
#endif
    }

    // Sets console buffer size for scrolling (allows larger output than visible window)
    void setBufferSize(int width, int height) {
#ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut != INVALID_HANDLE_VALUE) {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            GetConsoleScreenBufferInfo(hOut, &csbi);
            SHORT maxWidth = csbi.dwMaximumWindowSize.X;
            
            COORD bufferSize;
            bufferSize.X = static_cast<SHORT>(width);
            bufferSize.Y = static_cast<SHORT>(height);
            
            // Ensure buffer is at least as wide as max window size, but clamp to maximum
            if (bufferSize.X < maxWidth) {
                bufferSize.X = maxWidth;
            } else if (bufferSize.X > maxWidth) {
                bufferSize.X = maxWidth;
            }
            
            // Maximum buffer height is typically 9999 on Windows
            const SHORT maxBufferHeight = 9999;
            if (bufferSize.Y > maxBufferHeight) {
                bufferSize.Y = maxBufferHeight;
            }
            
            SetConsoleScreenBufferSize(hOut, bufferSize);
        }
#else
        // On Unix-like systems, buffer size is typically unlimited
        // This is mainly for Windows compatibility
#endif
    }
}

