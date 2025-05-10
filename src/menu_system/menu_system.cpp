#include <iostream>
#include <iomanip>
#include "menu_system.h"
#include "../user/user.h"
#include "../user/user_management.h"
#include "../database_constants/user_table.h"

UserManagement *MenuSystem::userMgmt = nullptr;
bool MenuSystem::exitRequested = false;
MenuSystem::MenuLevel MenuSystem::currentLevel = MenuLevel::MAIN_MENU;
std::vector<MenuSystem::MenuLevel> MenuSystem::menuStack;

const MenuSystem::MenuItem MenuSystem::MAIN_MENU_ITEMS[] = {
    {1, "Login", "", &MenuSystem::login},
    {2, "Register", "", &MenuSystem::registerUser},
    {0, "Exit", "", &MenuSystem::exit}
};

const MenuSystem::MenuItem MenuSystem::USER_MENU_ITEMS[] = {
    {1, "Account Management", user_table::roles::USER, &MenuSystem::navigateToAccountMenu},
    {2, "Transfer Points", user_table::roles::USER, &MenuSystem::transferPoints},
    {3, "Logout", user_table::roles::USER, &MenuSystem::logout},
    {0, "Exit", "", &MenuSystem::exit}
};

const MenuSystem::MenuItem MenuSystem::ADMIN_MENU_ITEMS[] = {
    {1, "Create User", user_table::roles::ADMIN, &MenuSystem::createUser},
    {2, "Delete User", user_table::roles::ADMIN, &MenuSystem::deleteUser},
    {3, "Reset User Password", user_table::roles::ADMIN, &MenuSystem::resetPassword},
    {4, "Search by Username", user_table::roles::USER, &MenuSystem::searchUser},
    {5, "Search by Email", user_table::roles::USER, &MenuSystem::searchByEmail},
    {6, "Logout", user_table::roles::USER, &MenuSystem::logout},
    {0, "Exit", "", &MenuSystem::exit}
};

const MenuSystem::MenuItem MenuSystem::ACCOUNT_MENU_ITEMS[] = {
    {1, "Change Password", user_table::roles::USER, &MenuSystem::changePassword},
    {2, "Update Profile", user_table::roles::USER, &MenuSystem::updateProfile},
    {3, "Delete My Account", user_table::roles::USER, &MenuSystem::deleteUser},
    {4, "Back to User Menu", user_table::roles::USER, &MenuSystem::goBackAction}
};

const MenuSystem::MenuItem MenuSystem::SEARCH_MENU_ITEMS[] = {
    {1, "Search by Username", user_table::roles::USER, &MenuSystem::searchUser},
    {2, "Search by Email", user_table::roles::USER, &MenuSystem::searchByEmail},
    {0, "Back to User Menu", user_table::roles::USER, &MenuSystem::goBackAction}
};

const int MenuSystem::MAIN_MENU_SIZE = std::size(MAIN_MENU_ITEMS);
const int MenuSystem::USER_MENU_SIZE = std::size(USER_MENU_ITEMS);
const int MenuSystem::ADMIN_MENU_SIZE = std::size(ADMIN_MENU_ITEMS);
const int MenuSystem::ACCOUNT_MENU_SIZE = std::size(ACCOUNT_MENU_ITEMS);
const int MenuSystem::SEARCH_MENU_SIZE = std::size(SEARCH_MENU_ITEMS);

const MenuSystem::MenuItem *MenuSystem::getCurrentMenuItems(const MenuLevel level, int &size) {
    switch (level) {
        case MenuLevel::MAIN_MENU:
            size = MAIN_MENU_SIZE;
            return MAIN_MENU_ITEMS;
        case MenuLevel::USER_MENU:
            size = USER_MENU_SIZE;
            return USER_MENU_ITEMS;
        case MenuLevel::ADMIN_MENU:
            size = ADMIN_MENU_SIZE;
            return ADMIN_MENU_ITEMS;
        case MenuLevel::ACCOUNT_MENU:
            size = ACCOUNT_MENU_SIZE;
            return ACCOUNT_MENU_ITEMS;
        case MenuLevel::SEARCH_MENU:
            size = SEARCH_MENU_SIZE;
            return SEARCH_MENU_ITEMS;
        default:
            size = MAIN_MENU_SIZE;
            return MAIN_MENU_ITEMS;
    }
}

std::string MenuSystem::getLevelName(MenuLevel level) {
    switch (level) {
        case MenuLevel::MAIN_MENU:
            return "Main Menu";
        case MenuLevel::USER_MENU:
            return "User Menu";
        case MenuLevel::ADMIN_MENU:
            return "Admin Menu";
        case MenuLevel::ACCOUNT_MENU:
            return "Account Menu";
        case MenuLevel::SEARCH_MENU:
            return "Search Menu";
        default:
            return "Unknown Menu";
    }
}

void MenuSystem::printMenu(const User *currentUser, MenuLevel level) {
    std::cout << "\n================================\n";
    std::cout << "    Payment System\n";
    std::cout << "    " << getLevelName(level) << "\n";
    std::cout << "================================\n";

    std::cout << "Current Status: ";
    if (currentUser) {
        std::cout << currentUser->getUsername() << " (";
        if (currentUser->getRole() == user_table::roles::ADMIN) {
            std::cout << "Administrator";
        } else if (currentUser->getRole() == user_table::roles::USER) {
            std::cout << "User";
        } else {
            std::cout << "Unknown";
        }
        std::cout << ")";
    } else {
        std::cout << "Not logged in";
    }

    std::cout << "\n--------------------------------\n";

    int menuSize;
    const MenuItem *menuItems = getCurrentMenuItems(level, menuSize);

    for (int i = 0; i < menuSize; ++i) {
        const MenuItem &item = menuItems[i];
        if (isMenuItemVisible(item, currentUser)) {
            std::cout << std::setw(2) << item.value << ". " << item.label << std::endl;
        }
    }

    std::cout << "--------------------------------\n";
    std::cout << "Enter your choice: ";
}

bool MenuSystem::isMenuItemVisible(const MenuItem &item, const User *currentUser) {
    if (item.requiredRole.empty())
        return true;
    if (!currentUser)
        return false;

    const std::string userRole = currentUser->getRole();
    if (userRole == user_table::roles::ADMIN)
        return true;
    if (userRole == user_table::roles::USER && item.requiredRole == user_table::roles::USER)
        return true;

    return false;
}

void MenuSystem::processChoice(const int choice, const User *currentUser) {
    int menuSize;
    const MenuItem *menuItems = getCurrentMenuItems(currentLevel, menuSize);

    for (int i = 0; i < menuSize; ++i) {
        if (const MenuItem &item = menuItems[i]; item.value == choice && isMenuItemVisible(item, currentUser)) {
            if (item.isNavigation) {
                navigateToLevel(item.nextLevel);
            } else {
                item.action(userMgmt);
            }
            return;
        }
    }
    std::cout << "\nInvalid choice or insufficient permissions!\n";
}

void MenuSystem::navigateAfterLogin(MenuLevel level) {
    menuStack.clear();
    currentLevel = level;
}

void MenuSystem::goBack() {
    if (!menuStack.empty()) {
        currentLevel = menuStack.back();
        menuStack.pop_back();
    }
}

void MenuSystem::login(UserManagement *mgmt) {
    mgmt->login();
    User *user = mgmt->getCurrentUser();

    if (user != nullptr) {
        if (user->getRole() == user_table::roles::ADMIN) {
            currentLevel = MenuLevel::ADMIN_MENU;
        } else if (user->getRole() == user_table::roles::USER) {
            currentLevel = MenuLevel::USER_MENU;
        }
    }
}

void MenuSystem::navigateToLevel(MenuLevel level) {
    if (currentLevel != MenuLevel::MAIN_MENU || !menuStack.empty()) {
        menuStack.push_back(currentLevel);
    }
    currentLevel = level;
}

void MenuSystem::run(UserManagement *mgmt) {
    userMgmt = mgmt;
    exitRequested = false;
    currentLevel = MenuLevel::MAIN_MENU;
    menuStack.clear();

    std::cout << "Welcome to Payment System!\n";
    std::cout << "Default accounts:\n";
    std::cout << "  Admin: username='admin', password='admin123'\n";
    std::cout << "  User: username='user', password='user123'\n";

    while (!exitRequested) {
        const User *currentUser = mgmt->getCurrentUser();

        printMenu(currentUser, currentLevel);

        int choice;
        std::cin >> choice;

        std::cin.clear();
        std::cin.ignore(10000, '\n');

        processChoice(choice, currentUser);

        if (!mgmt->getCurrentUser() && currentLevel != MenuLevel::MAIN_MENU) {
            currentLevel = MenuLevel::MAIN_MENU;
            menuStack.clear();
        }
    }
}

void MenuSystem::navigateToUserMenu(UserManagement *mgmt) {
    navigateToLevel(MenuLevel::USER_MENU);
}

void MenuSystem::navigateToAdminMenu(UserManagement *mgmt) {
    navigateToLevel(MenuLevel::ADMIN_MENU);
}

void MenuSystem::navigateToAccountMenu(UserManagement *mgmt) {
    navigateToLevel(MenuLevel::ACCOUNT_MENU);
}

void MenuSystem::navigateToSearchMenu(UserManagement *mgmt) {
    navigateToLevel(MenuLevel::SEARCH_MENU);
}

void MenuSystem::transferPoints(UserManagement *mgmt) {
    // TODO
}

void MenuSystem::goBackAction(UserManagement *mgmt) {
    goBack();
}

void MenuSystem::registerUser(UserManagement *mgmt) {
    mgmt->registerUser();
}

void MenuSystem::searchUser(UserManagement *mgmt) {
    mgmt->searchUser();
}

void MenuSystem::searchByEmail(UserManagement *mgmt) {
    std::cout << "\n--- Search by Email ---\n";
    std::cout << "Search by email functionality to be implemented...\n";
}

void MenuSystem::changePassword(UserManagement *mgmt) {
    std::cout << "\n--- Change Password ---\n";
    std::cout << "Change password functionality to be implemented...\n";
}

void MenuSystem::updateProfile(UserManagement *mgmt) {
    std::cout << "\n--- Update Profile ---\n";
    std::cout << "Update profile functionality to be implemented...\n";
}

void MenuSystem::deleteUser(UserManagement *mgmt) {
    mgmt->deleteUser();
}

void MenuSystem::createUser(UserManagement *mgmt) {
    // mgmt->createUser();
}

void MenuSystem::resetPassword(UserManagement *mgmt) {
    mgmt->resetPassword();
}

void MenuSystem::logout(UserManagement *mgmt) {
    mgmt->logout();
    currentLevel = MenuLevel::MAIN_MENU;
    menuStack.clear();
}

void MenuSystem::exit(UserManagement *mgmt) {
    std::cout << "\nThank you for using Payment System. Goodbye!\n";
    exitRequested = true;
}
