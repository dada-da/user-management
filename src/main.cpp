#include <iostream>

#include "user_management/user_management.h"
#include "menu_controller/menu_controller.h"

using namespace std;

int main() {
    user_mgmt::UserManagement *current_user = user_mgmt::UserManagement::getInstance();

    MenuController::init();

    return 0;
}
