//
// Created by Da on 21/5/25.
//

#include "user_management.h"

user_mgmt::UserManagement *user_mgmt::UserManagement::pinstance = nullptr;
std::mutex user_mgmt::UserManagement::mutex;
