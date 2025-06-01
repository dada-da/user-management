//
// Created by Da on 27/5/25.
//

#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <string>
#include <vector>
#include <functional>

class MenuController {
    static bool exitRequested;

public:
    ~MenuController() = default;

    static void displayMenu();

    static void showGuestMenu();

    static void showLoginMenu();

    static int getUserInput();

    static void processChoice(int value);

    static void exit();

    static void init();
};


#endif //MENU_CONTROLLER_H
