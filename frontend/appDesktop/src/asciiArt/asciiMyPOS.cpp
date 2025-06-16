#include <iostream>
#include <string>
#include "asciiMyPOS.h"

void printAsciiMyPOS()
{
    const std::string BLUE = "\033[38;2;4;143;250m";
    const std::string GRAY = "\033[90m";
    const std::string RESET = "\033[0m";
    const std::string asciiArt[] = {
        "                         /$$$$$$$   /$$$$$$   /$$$$$$ ",
        "                        | $$__  $$ /$$__  $$ /$$__  $$",
        " /$$$$$$/$$$$  /$$   /$$| $$  \\ $$| $$  \\ $$| $$  \\__/",
        "| $$_  $$_  $$| $$  | $$| $$$$$$$/| $$  | $$|  $$$$$$ ",
        "| $$ \\ $$ \\ $$| $$  | $$| $$____/ | $$  | $$ \\____  $$",
        "| $$ | $$ | $$| $$  | $$| $$      | $$  | $$ /$$  \\ $$",
        "| $$ | $$ | $$|  $$$$$$$| $$      |  $$$$$$/|  $$$$$$/",
        "|__/ |__/ |__/ \\____  $$|__/       \\______/  \\______/ ",
        "               /$$  | $$                              ",
        "              |  $$$$$$/                              ",
        "               \\______/                               "
    };

    const int numRows = sizeof(asciiArt) / sizeof(asciiArt[0]);

    for (int i = 0; i < numRows; i++)
    {
        for (size_t j = 0; j < asciiArt[i].size(); j++)
        {
            std::cout << (j < 24 ? BLUE : GRAY) << asciiArt[i][j];
        }
        std::cout << RESET << std::endl;
    }
}