//
// Created by Da on 4/6/25.
//

#ifndef MENU_LIST_H
#define MENU_LIST_H

#include <string>
#include <vector>

namespace menu {
    enum class MenuId {
        MAIN_MENU,
        CUSTOMER_MENU,
        ADMIN_MENU,
        ACCOUNT_DETAIL,
        VIEW_INFO
    };

    enum class ActionType {
        NONE,
        LOGIN,
        REGISTER,
        EXIT,
        TRANSFER_POINTS,
        LOGOUT,
        VIEW_PROFILE,
        UPDATE_PROFILE,
        CHANGE_PASSWORD,
        POINTS_HISTORY,
        BACK,
        CREATE_USER,
        DELETE_USER,
        SEARCH_USER,
        RESET_PASSWORD,
        ACCOUNT_DETAIL
    };

    struct MenuItem {
        int id;
        std::string label;
        ActionType action;

        MenuItem(const int id, const std::string &label, const ActionType action = ActionType::NONE)
            : id(id), label(label), action(action) {
        }
    };

    struct Menu {
        MenuId id;
        std::vector<MenuItem> items;
        bool isAdmin;
    };

    const Menu MAIN_MENU = {
        MenuId::MAIN_MENU,
        {
            {1, "🔐 Login", ActionType::LOGIN},
            {2, "📝 Register", ActionType::REGISTER},
            {0, "🚪 Exit", ActionType::EXIT}
        }
    };

    const Menu CUSTOMER_MENU = {
        MenuId::CUSTOMER_MENU,
        {
            {1, "📋 Account Detail", ActionType::ACCOUNT_DETAIL},
            {2, "💸 Transfer Points", ActionType::TRANSFER_POINTS},
            {3, "➕ Deposit Points", ActionType::TRANSFER_POINTS},
            {5, "📈 Points History", ActionType::POINTS_HISTORY},
            {4, "🔓 Logout", ActionType::LOGOUT},
            {0, "🚪 Exit", ActionType::EXIT}
        }
    };

    const Menu ACCOUNT_DETAIL = {
        MenuId::ACCOUNT_DETAIL,
        {
            {1, "👤 View Full Account Details", ActionType::VIEW_PROFILE},
            {2, "✏️ Update Profile", ActionType::UPDATE_PROFILE},
            {3, "🔒 Change Password", ActionType::CHANGE_PASSWORD},
            {4, "↩️ Back", ActionType::BACK}
        }
    };

    const Menu ADMIN_MENU = {
        MenuId::ADMIN_MENU,
        {
            {1, "📋 Account Detail", ActionType::ACCOUNT_DETAIL},
            {2, "➕ Create User", ActionType::CREATE_USER},
            {3, "🗑️ Delete User", ActionType::DELETE_USER},
            {4, "🔍 Search User", ActionType::SEARCH_USER},
            {5, "🔁 Reset User Password", ActionType::RESET_PASSWORD},
            {6, "🔓 Logout", ActionType::LOGOUT},
            {0, "🚪 Exit", ActionType::EXIT}
        },
        true
    };

    const Menu VIEW_INFO = {
        MenuId::VIEW_INFO,
        {
            {1, "↩️ Back", ActionType::BACK}
        }
    };

    const Menu MENU_LIST[4] = {ACCOUNT_DETAIL, ADMIN_MENU, CUSTOMER_MENU, MAIN_MENU};
}

#endif //MENU_LIST_H
