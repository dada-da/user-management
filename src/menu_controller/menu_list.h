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
        ACCOUNT_DETAIL,
        ADMIN_MENU
    };

    struct MenuItem {
        int id;
        std::string label;
        std::function<void()> action;
    };

    struct Menu {
        MenuId id;
        std::vector<MenuItem> items;
        bool isAdmin;
    };

    const Menu MAIN_MENU = {
        MenuId::MAIN_MENU,
        {
            {1, "🔐 Login"},
            {2, "📝 Register"},
            {0, "🚪 Exit"}
        }
    };

    const Menu CUSTOMER_MENU = {
        MenuId::CUSTOMER_MENU,
        {
            {1, "📋 Account Detail"},
            {2, "💸 Transfer Points"},
            {3, "🔓 Logout"},
            {0, "🚪 Exit"}
        }
    };

    const Menu ACCOUNT_DETAIL = {
        MenuId::ACCOUNT_DETAIL,
        {
            {1, "👤 View Profile"},
            {2, "✏️ Update Profile"},
            {3, "🔒 Change Password"},
            {4, "📈 Points History"},
            {-1, "↩️ Back"}
        }
    };

    const Menu ADMIN_MENU = {
        MenuId::ADMIN_MENU,
        {
            {1, "➕ Create User"},
            {2, "🗑️ Delete User"},
            {3, "🔍 Search User"},
            {4, "🔁 Reset User Password"},
            {5, "🔓 Logout"},
            {0, "🚪 Exit"},
        },
        true
    };

    const Menu MENU_LIST[4] = {ACCOUNT_DETAIL, ADMIN_MENU, CUSTOMER_MENU, MAIN_MENU};
}

#endif //MENU_LIST_H
