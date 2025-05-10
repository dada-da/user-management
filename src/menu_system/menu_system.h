#ifndef MENU_SYSTEM_H
#define MENU_SYSTEM_H

#include <string>
#include <vector>
#include "../user/user.h"

class UserManagement;

class MenuSystem {
public:
    enum class MenuLevel {
        MAIN_MENU,
        USER_MENU,
        ADMIN_MENU,
        ACCOUNT_MENU,
        SEARCH_MENU
    };

    struct MenuItem {
        int value;
        std::string label;
        Role requiredRole;

        void (*action)(UserManagement *);

        MenuLevel nextLevel;
        bool isNavigation;

        MenuItem(const int val, const std::string &lbl, const Role role, void (*act)(UserManagement *),
                 const MenuLevel next = MenuLevel::MAIN_MENU, const bool isNav = false)
            : value(val), label(lbl), requiredRole(role), action(act),
              nextLevel(next), isNavigation(isNav) {
        }
    };

private:
    static UserManagement *userMgmt;
    static bool exitRequested;
    static MenuLevel currentLevel;
    static std::vector<MenuLevel> menuStack;

    static const MenuItem MAIN_MENU_ITEMS[];
    static const MenuItem USER_MENU_ITEMS[];
    static const MenuItem ADMIN_MENU_ITEMS[];
    static const MenuItem ACCOUNT_MENU_ITEMS[];
    static const MenuItem SEARCH_MENU_ITEMS[];

    static const int MAIN_MENU_SIZE;
    static const int USER_MENU_SIZE;
    static const int ADMIN_MENU_SIZE;
    static const int ACCOUNT_MENU_SIZE;
    static const int SEARCH_MENU_SIZE;


    static void printMenu(const User *currentUser, MenuLevel level);

    static const MenuItem *getCurrentMenuItems(MenuLevel level, int &size);

    static bool isMenuItemVisible(const MenuItem &item, const User *currentUser);

    static void processChoice(int choice, const User *currentUser);

    static std::string getLevelName(MenuLevel level);

    static void navigateToLevel(MenuLevel level);

    static void navigateAfterLogin(MenuLevel level);

    static void goBack();

public:
    static void navigateToUserMenu(UserManagement *mgmt);

    static void navigateToAdminMenu(UserManagement *mgmt);

    static void navigateToAccountMenu(UserManagement *mgmt);

    static void navigateToSearchMenu(UserManagement *mgmt);

    static void goBackAction(UserManagement *mgmt);

    static void login(UserManagement *mgmt);

    static void registerUser(UserManagement *mgmt);

    static void createUser(UserManagement *mgmt);

    static void deleteUser(UserManagement *mgmt);

    static void resetPassword(UserManagement *mgmt);

    static void searchUser(UserManagement *mgmt);

    static void searchByEmail(UserManagement *mgmt);

    static void transferPoints(UserManagement *mgmt);

    static void changePassword(UserManagement *mgmt);

    static void updateProfile(UserManagement *mgmt);

    static void logout(UserManagement *mgmt);

    static void exit(UserManagement *mgmt);

    static void run(UserManagement *mgmt);

    static bool isExitRequested() { return exitRequested; }
};

#endif // MENU_SYSTEM_H
