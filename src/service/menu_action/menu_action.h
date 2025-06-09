//
// Created by Da on 5/6/25.
//

#ifndef MENU_ACTION_H
#define MENU_ACTION_H

#include "interface_menu_action.h"
#include "../../repository//user_data/interface_user_data.h"
#include "../authentication/interface_authentication_service.h"
#include "../wallet/interface_wallet_service.h"

namespace menu {
    class MenuAction final : public IMenuAction {
        db_user::IUserDatabase *userDatabase;
        auth::IAuthenticationService *authService;
        IWalletService *walletService;

    public:
        MenuAction(db_user::IUserDatabase *userDatabase, auth::IAuthenticationService *authService,
                   IWalletService *walletService)
            : userDatabase(userDatabase), authService(authService), walletService(walletService) {
        }

        bool login() override;

        void logout() override;

        void viewAccountDetail() override;

        void viewFullAccountInfo() override;

        void updateProfile() override;

        void searchUser() override;

        void changePassword() override;

        void displayWalletDashboard() override;

        bool transfer() override;
    };
}

#endif //MENU_ACTION_H
