//
// Created by Da on 5/6/25.
//

#ifndef INTERFACE_MENU_ACTION_H
#define INTERFACE_MENU_ACTION_H

namespace menu {
    class IMenuAction {
    public:
        virtual ~IMenuAction() = default;

        virtual bool login() = 0;

        virtual bool registerUser() = 0;

        virtual void logout() = 0;

        virtual void viewAccountDetail() = 0;

        virtual void viewFullAccountInfo() = 0;

        virtual void updateProfile() = 0;

        virtual void searchUser() = 0;

        virtual void changePassword() = 0;

        virtual bool transfer() = 0;

        virtual void displayWalletDashboard() = 0;

        virtual void displayPointHistory() = 0;

        virtual bool createUser() = 0;
    };
}

#endif //INTERFACE_MENU_ACTION_H
