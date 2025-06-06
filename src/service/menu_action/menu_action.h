//
// Created by Da on 5/6/25.
//

#ifndef MENU_ACTION_H
#define MENU_ACTION_H

#include "interface_menu_action.h"

namespace menu {
    class MenuAction final : public IMenuAction {
    public:
        void login() override;

        void viewAccountDetail() override;

        void viewFullAccountInfo() override;
    };
}

#endif //MENU_ACTION_H
