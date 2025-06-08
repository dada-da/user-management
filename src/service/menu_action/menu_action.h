//
// Created by Da on 5/6/25.
//

#ifndef MENU_ACTION_H
#define MENU_ACTION_H

#include "interface_menu_action.h"
#include "../../user_data/interface_user_data.h"
#include "../authentication/interface_authentication_service.h"

namespace menu {
    class MenuAction final : public IMenuAction {
        db_user::IUserDatabase *userDatabase;
        auth::IAuthenticationService *authService;

    public:
        MenuAction(db_user::IUserDatabase *userDatabase, auth::IAuthenticationService *authService)
            : userDatabase(userDatabase), authService(authService) {
        }

        void login() override;

        void logout() override;

        void viewAccountDetail() override;

        void viewFullAccountInfo() override;

        void updateProfile() override;

        void searchUser() override;

        void changePassword() override;
    };
}

#endif //MENU_ACTION_H
