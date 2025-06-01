#include <iostream>

#include "user_management/user_management.h"
#include "menu_controller/menu_controller.h"
#include "user_data/user_data.h"

using namespace std;

int main() {
    user_mgmt::UserManagement *current_user = user_mgmt::UserManagement::getInstance();

    auto userData = db_user::UserData();

    userData.readUsersFromFile();

    MenuController::init();

    return 0;
}
