//
// Created by Da on 5/6/25.
//

#ifndef MENU_ACTION_H
#define MENU_ACTION_H

#include "interface_menu_action.h"
#include "../../user_data/user_data.h"
#include "../password_handler/password_handler.h"

namespace menu {
    class MenuAction : public IMenuAction {
        db_user::UserData* userData;
        pw_util::PasswordHandler* pwHandler;
    public:
        MenuAction(db_user::UserData* userData, pw_util::PasswordHandler* pwHandler)
            : userData(userData), pwHandler(pwHandler) {}

        void login() override;

        void logout() override;

        void viewAccountDetail() override;

        void viewFullAccountInfo() override;

        void updateProfile() override;
    };
}

#endif //MENU_ACTION_H
