//
// Created by Da on 8/6/25.
//

#include "menu_display.h"

#include "../user_management/user_management.h"

namespace menu {
    void MenuDisplay::displayUserStatus() {
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

    void MenuDisplay::displayMenu(const Menu &menu) {
        displayUserStatus();

        std::cout << "\n------------------------------------------------------------\n";

        for (const auto &item: menu.items) {
            std::cout << item.id << ". " << item.label << std::endl;
        }
        std::cout << "------------------------------------------------------------\n";
    }

    void MenuDisplay::displayWelcomeMessage() {
        std::cout << "\n🎉 Welcome to Payment System!\n";
        std::cout << "📋 Default accounts:\n";
        std::cout << "  👑 Admin: username='root', password='root'\n";
        std::cout << "  👤 User: username='customer', password='customer'\n";
    }

    void MenuDisplay::displayExitMessage() {
        std::cout << "\n👋 Thank you for using Payment System!\n";
        std::cout << "💫 Have a great day!\n";
    }
}
