//
// Created by Da on 27/5/25.
//

#include <iostream>
#include <string>
#include <vector>

#include "menu_controller.h"
#include "menu_list.h"
#include "../menu_display/menu_display.h"
#include "../user_management/user_management.h"

namespace menu {
    Menu MenuController::getCurrentMenu() const {
        const MenuId currentMenuId = menuLog.peek()->data;
        if (const auto userManager = user_mgmt::UserManagement::getInstance();
            !userManager || !userManager->isLoggedIn()) {
            return MAIN_MENU;
        }
        return getMenuList(currentMenuId);
    }

    void MenuController::setCurrentMenu(const MenuId menuId) {
        menuLog.push(menuId);
    }

    void MenuController::run() {
        pMenuDisplay->displayWelcomeMessage();

        menuLog.push(MenuId::MAIN_MENU);

        while (!exitRequested) {
            try {
                const Menu currentMenu = getCurrentMenu();
                pMenuDisplay->displayMenu(currentMenu);

                const int choice = getUserInput();
                processChoice(choice, currentMenu);
            } catch (const std::exception &e) {
                std::cerr << "❌ Error: " << e.what() << std::endl;
                std::cout << "Press Enter to continue...";
                std::cin.get();
            }
        }

        pMenuDisplay->displayExitMessage();
    }

    void MenuController::exit() {
        exitRequested = true;
    }

    void MenuController::processChoice(int choice, const Menu &menu) {
        const auto itemIt = std::find_if(menu.items.begin(), menu.items.end(),
                                         [choice](const MenuItem &item) { return item.id == choice; });

        if (itemIt != menu.items.end()) {
            MenuDisplay::clearScreen();
            executeAction(itemIt->action);
        } else {
            handleInvalidChoice(choice);
        }
    }

    void MenuController::executeAction(const ActionType actionType) {
        try {
            switch (actionType) {
                case ActionType::LOGIN:
                    try {
                        pMenuAction->login();
                        const auto userManager = user_mgmt::UserManagement::getInstance();
                        if (userManager->isAdmin()) {
                            setCurrentMenu(MenuId::ADMIN_MENU);
                        } else {
                            setCurrentMenu(MenuId::CUSTOMER_MENU);
                        }
                    } catch (const std::exception &e) {
                        std::cerr << e.what() << std::endl;
                    }
                    break;
                case ActionType::REGISTER:
                    //TO DO
                    break;
                case ActionType::EXIT:
                    exit();
                    break;
                case ActionType::ACCOUNT_DETAIL:
                    try {
                        pMenuAction->viewAccountDetail();
                        setCurrentMenu(MenuId::ACCOUNT_DETAIL);
                    } catch (const std::exception &e) {
                        std::cerr << e.what() << std::endl;
                    }
                    break;
                case ActionType::TRANSFER_POINTS:
                    //TO DO
                    break;
                case ActionType::LOGOUT:
                    try {
                        pMenuAction->logout();
                        setCurrentMenu(MenuId::MAIN_MENU);
                    } catch (const std::exception &e) {
                        std::cerr << e.what() << std::endl;
                    }
                    break;
                case ActionType::VIEW_PROFILE:
                    try {
                        pMenuAction->viewFullAccountInfo();
                        setCurrentMenu(MenuId::VIEW_INFO);
                    } catch (const std::exception &e) {
                        std::cerr << e.what() << std::endl;
                    }
                    break;
                case ActionType::UPDATE_PROFILE:
                    try {
                        pMenuAction->updateProfile();
                        setCurrentMenu(MenuId::ACCOUNT_DETAIL);
                    } catch (const std::exception &e) {
                        std::cerr << e.what() << std::endl;
                    }
                    break;
                case ActionType::CHANGE_PASSWORD:
                    try {
                        pMenuAction->changePassword();
                    } catch (const std::exception &e) {
                        std::cerr << e.what() << std::endl;
                    }
                    break;
                case ActionType::POINTS_HISTORY:
                    //TO DO
                    break;
                case ActionType::BACK:
                    try {
                        menuLog.pop();
                    } catch (const std::exception &e) {
                        std::cerr << e.what() << std::endl;
                    }
                    break;
                case ActionType::CREATE_USER:
                    //TO DO
                    break;
                case ActionType::DELETE_USER:
                    //TO DO
                    break;
                case ActionType::SEARCH_USER:
                    try {
                        pMenuAction->searchUser();
                    } catch (const std::exception &e) {
                        std::cerr << e.what() << std::endl;
                    }
                    break;
                case ActionType::RESET_PASSWORD:
                    //TO DO
                    break;
                case ActionType::NONE:
                default:
                    std::cout << "\n⚠️ Function not implemented yet.\n";
                    break;
            }
        } catch (const std::exception &e) {
            std::cerr << "\n ❌ Error executing action: " << e.what() << std::endl;
        }
    }

    void MenuController::navigateToMenu(const MenuId menuId) {
        setCurrentMenu(menuId);
        std::cout << "\n📍 Navigating to new menu...\n";
    }

    void MenuController::goBack() {
        setCurrentMenu(MenuId::MAIN_MENU);
        std::cout << "\n🔙 Returning to main menu...\n";
    }
}
