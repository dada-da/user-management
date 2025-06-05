#include <iostream>

#include "user_management/user_management.h"
#include "menu_controller/menu_controller.h"
#include "user_data/user_data.h"
#include "service/authentication/authentication_service.h"
#include "service/password_handler/password_handler.h"
#include "service/menu_action/menu_action.h"

using namespace std;

int main() {
    auto userData = db_user::UserData();
    auto pwHandle = pw_util::PasswordHandler();

    userData.loadFromFile();

    auto authService = auth::AuthenticationService(&userData, &pwHandle);

    user_mgmt::UserManagement::getInstance(&authService);

    menu::MenuAction menuActionService = menu::MenuAction();

    menu::MenuController controller(&menuActionService);

    controller.init();

    return 0;
}
