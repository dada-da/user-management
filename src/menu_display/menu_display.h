//
// Created by Da on 8/6/25.
//

#ifndef MENU_DISPLAY_H
#define MENU_DISPLAY_H

#include <iostream>
#include "../menu_controller/menu_list.h"
#include "interface_menu_display.h"

namespace menu {
    class MenuDisplay : public IMenuDisplay {
    public:
        static void clearScreen() {
            std::cout << "\033[2J\033[1;1H";
            std::cout.flush();

            #ifdef _WIN32
                        system("cls");
            #else
                        system("clear");
            #endif
        }

        void displayMenu(const Menu &menu) override;

        void displayUserStatus() override;

        void displayWelcomeMessage() override;

        void displayExitMessage() override;
    };
}


#endif //MENU_DISPLAY_H
