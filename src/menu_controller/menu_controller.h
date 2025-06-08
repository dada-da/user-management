//
// Created by Da on 27/5/25.
//

#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <limits>
#include <string>
#include <sstream>

#include "../service/menu_action/interface_menu_action.h"
#include "../menu_display/interface_menu_display.h"
#include "../utils/stack.h"
#include "menu_list.h"

namespace menu {
    class MenuController {
        bool exitRequested;
        Stack<MenuId> menuLog;
        IMenuAction *pMenuAction;
        IMenuDisplay *pMenuDisplay;


        static int getUserInput() {
            int choice;
            std::string line;
            while (true) {
                std::cout << "\n👉 Enter your choice: ";
                std::getline(std::cin, line);
                std::stringstream ss(line);
                if (ss >> choice) {
                    return choice;
                }
                std::cout << "❌ Invalid input! Please enter a valid number.\n";
            }
        }

        static Menu getMenuList(const MenuId menuId = MenuId::MAIN_MENU) {
            switch (menuId) {
                case MenuId::CUSTOMER_MENU:
                    return CUSTOMER_MENU;
                case MenuId::ACCOUNT_DETAIL:
                    return ACCOUNT_DETAIL;
                case MenuId::ADMIN_MENU:
                    return ADMIN_MENU;
                case MenuId::BACK_BUTTON:
                    return BACK_BUTTON;
                case MenuId::MAIN_MENU:
                default:
                    return MAIN_MENU;
            }
        }

        static void handleInvalidChoice(const int choice) {
            std::cout << "\n❌ Invalid choice: " << choice
                    << ". Please select a valid option.\n";
        }

        Menu getCurrentMenu() const;

        void setCurrentMenu(MenuId menuId);

        void processChoice(int choice, const Menu &menu);

        void executeAction(ActionType actionType);

    public:
        explicit MenuController(IMenuAction *pMenuAction, IMenuDisplay *pMenuDisplay) : exitRequested(false),
            pMenuAction(pMenuAction), pMenuDisplay(pMenuDisplay) {
        }

        ~MenuController() = default;

        void run();

        void exit();

        void navigateToMenu(MenuId menuId);

        void goBack();
    };
}

#endif // MENU_CONTROLLER_H
