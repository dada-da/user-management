//
// Created by Da on 27/5/25.
//

#include <iostream>
#include <string>
#include <vector>
#include <limits>

#include "menu_controller.h"
#include "menu_list.h"
#include "../user_management/user_management.h"

namespace menu {
    void MenuController::displayMenu(const Menu &menu) {
        displayUserStatus();

        std::cout << "\n------------------------------------------------------------\n";

        for (const auto &item: menu.items) {
            std::cout << item.id << ". " << item.label << std::endl;
        }
        std::cout << "------------------------------------------------------------\n";
    }

    void MenuController::displayUserStatus() {
        std::cout << "\n------------------------------------------------------------\n";

        std::cout << "Current User: ";

        try {
            const auto userManager = user_mgmt::UserManagement::getInstance();
            if (userManager && userManager->isLoggedIn()) {
                std::cout << userManager->getUserName() << " ("
                        << userManager->getRole() << ")";
            } else {
                std::cout << "Not logged in";
            }
        } catch (const std::exception &e) {
            std::cout << "Not logged in";
        }
    }

    Menu MenuController::getMenuList(const MenuId menuId) {
        switch (menuId) {
            case MenuId::CUSTOMER_MENU:
                return CUSTOMER_MENU;
            case MenuId::CUSTOMER_ACCOUNT:
                return CUSTOMER_ACCOUNT;
            case MenuId::ADMIN_MENU:
                return ADMIN_MENU;
            case MenuId::ADMIN_ACCOUNT:
                return ADMIN_ACCOUNT;
            case MenuId::VIEW_INFO:
                return VIEW_INFO;
            case MenuId::MAIN_MENU:
            default:
                return MAIN_MENU;
        }
    }

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

    void MenuController::displayWelcomeMessage() {
        std::cout << "\n🎉 Welcome to Payment System!\n";
        std::cout << "📋 Default accounts:\n";
        std::cout << "  👑 Admin: username='root', password='root'\n";
        std::cout << "  👤 User: username='customer', password='customer'\n";
    }

    void MenuController::init() {
        displayWelcomeMessage();

        menuLog.push(MenuId::MAIN_MENU);

        while (!exitRequested) {
            try {
                runMenuLoop();
            } catch (const std::exception &e) {
                std::cerr << "❌ Error: " << e.what() << std::endl;
                std::cout << "Press Enter to continue...";
                std::cin.get();
            }
        }

        displayExitMessage();
    }

    void MenuController::runMenuLoop() {
        const Menu currentMenu = getCurrentMenu();
        displayMenu(currentMenu);

        const int choice = getUserInput();
        processChoice(choice, currentMenu);
    }

    void MenuController::displayExitMessage() const {
        std::cout << "\n👋 Thank you for using Payment System!\n";
        std::cout << "💫 Have a great day!\n";
    }

    void MenuController::exit() {
        exitRequested = true;
    }

    int MenuController::getUserInput() const {
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

    void MenuController::processChoice(int choice, const Menu &menu) {
        const auto itemIt = std::find_if(menu.items.begin(), menu.items.end(),
                                         [choice](const MenuItem &item) { return item.id == choice; });

        if (itemIt != menu.items.end()) {
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
                case ActionType::ADMIN_ACCOUNT:
                    try {
                        pMenuAction->viewAccountDetail();
                        setCurrentMenu(MenuId::ADMIN_ACCOUNT);
                    } catch (const std::exception &e) {
                        std::cerr << e.what() << std::endl;
                    }
                    break;
                case ActionType::CUSTOMER_ACCOUNT:
                    //TO DO
                    break;
                case ActionType::TRANSFER_POINTS:
                    //TO DO
                    break;
                case ActionType::LOGOUT:
                    //TO DO
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
                    //TO DO
                    break;
                case ActionType::CHANGE_PASSWORD:
                    //TO DO
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
                    //TO DO
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

    void MenuController::handleInvalidChoice(int choice) const {
        std::cout << "\n❌ Invalid choice: " << choice
                << ". Please select a valid option.\n";
    }

    bool MenuController::isExitRequested() const {
        return exitRequested;
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
