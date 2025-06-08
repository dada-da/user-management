//
// Created by Da on 8/6/25.
//

#ifndef INTERFACE_MENU_DISPLAY_H
#define INTERFACE_MENU_DISPLAY_H

#include "../menu_controller/menu_list.h"

namespace menu {
    class IMenuDisplay {
    public:
        virtual ~IMenuDisplay() = default;

        virtual void displayMenu(const Menu &menu) = 0;

        virtual void displayUserStatus() = 0;

        virtual void displayWelcomeMessage() = 0;

        virtual void displayExitMessage() = 0;


    };
}

#endif //INTERFACE_MENU_DISPLAY_H
