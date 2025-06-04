#include <iostream>

#include "user_management/user_management.h"
#include "menu_controller/menu_controller.h"
#include "user_data/user_data.h"
#include "service/authentication/authentication_service.h"
#include "utils/password_handler/password_handler.h"

using namespace std;

int main() {
    auto userData = db_user::UserData();
    auto pwHandle = pw_util::PasswordHandler();

    userData.loadFromFile();

    auto authService = auth::AuthenticationService(&userData, &pwHandle);

    user_mgmt::UserManagement::getInstance(&authService);

    menu::MenuController controller;

    controller.init();

    return 0;
}
