#include <iostream>

#include "user_management/user_management.h"
#include "menu_controller/menu_controller.h"
#include "user_data/user_data.h"

using namespace std;

int main() {
    auto userData = db_user::UserData();

    userData.loadFromFile();

    // user_mgmt::UserManagement *current_user = user_mgmt::UserManagement::getInstance();

    menu::MenuController::init();

    return 0;
}
