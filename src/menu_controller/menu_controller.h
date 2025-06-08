//
// Created by Da on 27/5/25.
//

#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

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


        static Menu getMenuList(MenuId menuId = MenuId::MAIN_MENU);

        Menu getCurrentMenu() const;

        void setCurrentMenu(MenuId menuId);

        int getUserInput() const;

        void processChoice(int choice, const Menu &menu);

        void executeAction(ActionType actionType);

        void handleInvalidChoice(int choice) const;

        void runMenuLoop();

    public:
        explicit MenuController(IMenuAction *pMenuAction, IMenuDisplay *pMenuDisplay) : exitRequested(false),
            pMenuAction(pMenuAction), pMenuDisplay(pMenuDisplay) {
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
