//
// Created by Da on 27/5/25.
//

#include <iostream>

#include "menu_controller.h"
#include "../role/role.h"
#include "../user_management/user_management.h"

void MenuController::showGuestMenu() {
    std::cout << "\n=== Guest Menu ===" << std::endl;
    std::cout << "1. 🔐 Login" << std::endl;
    std::cout << "2. 📝 Register" << std::endl;
    std::cout << "0. 🚪 Exit" << std::endl;
}

void MenuController::displayMenu() {
    user_mgmt::UserManagement *current_user = user_mgmt::UserManagement::getInstance();

    if (current_user == nullptr || !current_user->isLoggedIn()) {
        showGuestMenu();

        return;
    }

    try {
        const std::string userRole = current_user->getRole();

        if (userRole == UserRoles::ADMIN) {
            std::cout << "\n=== Admin ===" << std::endl;
            return;
        }

        if (userRole == UserRoles::CUSTOMER) {
            std::cout << "\n=== Customer ===" << std::endl;
            return;
        }

        showGuestMenu();
    } catch (const std::runtime_error &e) {
        std::cerr << "❌ Error getting user role: " << e.what() << std::endl;
        showGuestMenu();
    }
}

void MenuController::init() {
    while (!exitRequested) {
        displayMenu();

        const int choice = getUserInput();

        processChoice(choice);
    }
}

void MenuController::exit() {
    exitRequested = true;
}

int MenuController::getUserInput() {
    int choice;
    std::cout << "\n👉 Enter your choice: ";

    while (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "❌ Invalid input! Please enter a number." << std::endl;
        std::cout << "👉 Enter your choice: ";
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

void MenuController::processChoice(const int value) {
    if (value == 1) {
        std::cout << "\n=== Hello ===" << std::endl;
    }

    if (value == 0) {
        exit();
    }
}

bool MenuController::exitRequested = false;
