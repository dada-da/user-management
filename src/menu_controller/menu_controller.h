//
// Created by Da on 27/5/25.
//

#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include "menu_list.h"
#include "../service/menu_action/interface_menu_action.h"

namespace menu {
    class MenuController {
        bool exitRequested;
        MenuId currentMenuId;
        IMenuAction *pMenuAction;

        void displayMenu(const Menu &menu) const;

        void displayUserStatus() const;

        void displayWelcomeMessage() const;

        void displayExitMessage() const;

        Menu getMenuList(MenuId menuId = MenuId::MAIN_MENU) const;

        Menu getCurrentMenu() const;

        void setCurrentMenu(MenuId menuId);

        int getUserInput() const;

        void processChoice(int choice, const Menu &menu);

        void executeAction(ActionType actionType);

        void handleInvalidChoice(int choice) const;

        void runMenuLoop();

    public:
        MenuController(IMenuAction *pMenuAction) : exitRequested(false), currentMenuId(MenuId::MAIN_MENU),
                                                   pMenuAction(pMenuAction) {
        }

        ~MenuController() = default;

        void init();

        void exit();

        bool isExitRequested() const;

        void navigateToMenu(MenuId menuId);

        void goBack();
    };
}

#endif // MENU_CONTROLLER_H
