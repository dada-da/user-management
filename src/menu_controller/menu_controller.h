//
// Created by Da on 27/5/25.
//

#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <limits>

#include "../service/menu_action/interface_menu_action.h"
#include "../menu_display/interface_menu_display.h"
#include "../utils/stack/stack.h"
#include "menu_list.h"

namespace menu {
    class MenuController {
        bool exitRequested;
        Stack<MenuId> menuLog;
        IMenuAction *pMenuAction;
        IMenuDisplay *pMenuDisplay;


        static int getUserInput() {
            int choice;

            while (true) {
                std::cout << "\n👉 Enter your choice: ";

                if (std::cin >> choice) {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    return choice;
                }

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
                case MenuId::VIEW_INFO:
                    return VIEW_INFO;
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
