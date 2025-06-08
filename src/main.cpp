#include <iostream>

#include "user_management/user_management.h"
#include "menu_controller/menu_controller.h"
#include "menu_display/menu_display.h"
#include "user_data/user_data.h"
#include "service/authentication/authentication_service.h"
#include "service/menu_action/menu_action.h"

using namespace std;

int main() {
    auto userData = db_user::UserData();

    // pw_util::PasswordHandler::regenerateDefaultPasswords();
    // For regenerate root and customer

    // pw_util::PasswordHandler::generateSomePassword("somepassword");
    // To get hash and salt if you want to create user directly in user.csv

    userData.loadFromFile();

    auto authService = auth::AuthenticationService(&userData);

    user_mgmt::UserManagement::getInstance(&authService);

    auto menuActionService = menu::MenuAction(&userData, &authService);

    auto menuDisplay = menu::MenuDisplay();

    menu::MenuController controller(&menuActionService, &menuDisplay);

    controller.run();

    return 0;
}
