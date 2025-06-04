//
// Created by Da on 27/5/25.
//

#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include "menu_list.h"

namespace menu {
    class MenuController {
        static bool exitRequested;

    public:
        ~MenuController() = default;

        static void showMenu(const Menu &menu);

        static void displayActionMenu(MenuId value);

        static void displayMenu();

        static void showGuestMenu();

        static void showLoginMenu();

        static int getUserInput();

        static void processChoice(int value);

        static void exit();

        static void init();
    };
}

#endif //MENU_CONTROLLER_H
