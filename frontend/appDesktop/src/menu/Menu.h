#pragma once
#include "MenuFunctions.h"

class Menu {
private:
    MenuFunctions functions;

public:
    Menu();
    void displayMenu();
    void run();
}; 