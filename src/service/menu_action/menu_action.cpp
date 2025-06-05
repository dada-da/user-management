//
// Created by Da on 5/6/25.
//

#include <iostream>
#include "menu_action.h"
#include "../../utils/validator/validator.h"
#include "../../user_management/user_management.h"

namespace menu {
    void MenuAction::login() {
        std::string usernameValue, passwordValue;

        std::cout << "Enter username: ";
        const std::string validUsername = input::Validator::getValidUserName();

        std::cout << "Enter password: ";
        const std::string validPassword = input::Validator::getPassword();

        try {
            user_mgmt::UserManagement::getInstance()->login(validUsername, validPassword);
        } catch (const std::exception &e) {
            throw std::runtime_error(e.what());
        }

        std::cout << "Logged in successfully!" << std::endl;
        std::cout << user_mgmt::UserManagement::getInstance()->getUserName() <<std::endl;
    }
}
