#pragma once
#include <string>
#include <iostream>
#include <windows.h>

namespace ConsoleUtils {
    enum class Color {
        Red = FOREGROUND_RED | FOREGROUND_INTENSITY,
        Green = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        Yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
    };

    inline void clearScreen() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        SMALL_RECT scrollRect;
        COORD scrollTarget;
        CHAR_INFO fill;

        // Get the number of character cells in the current buffer
        if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;

        // Fill the entire buffer with spaces
        fill.Char.AsciiChar = ' ';
        fill.Attributes = csbi.wAttributes;

        // Get the current window size and position
        scrollRect.Left = 0;
        scrollRect.Top = 0;
        scrollRect.Right = csbi.dwSize.X;
        scrollRect.Bottom = csbi.dwSize.Y;

        // Scroll the window up by its height
        scrollTarget.X = 0;
        scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

        // First scroll the window up to move content out of view
        ScrollConsoleScreenBuffer(hConsole, &scrollRect, nullptr, scrollTarget, &fill);

        // Reset cursor position to top-left
        csbi.dwCursorPosition.X = 0;
        csbi.dwCursorPosition.Y = 0;
        SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);

        // Clear any remaining content
        DWORD written;
        FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X * csbi.dwSize.Y, {0, 0}, &written);
        FillConsoleOutputAttribute(hConsole, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, {0, 0}, &written);
    }

    inline void setColor(Color color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
    }

    inline void resetColor() {
        setColor(Color::White);
    }

    inline void printStatus(const std::string& message, bool success) {
        setColor(success ? Color::Green : Color::Yellow);
        std::cout << "\n" << message << "\n";
        resetColor();
    }
} 