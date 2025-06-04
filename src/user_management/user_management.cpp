//
// Created by Da on 21/5/25.
//

#include "user_management.h"

std::unique_ptr<user_mgmt::UserManagement> user_mgmt::UserManagement::pinstance = nullptr;
auth::IAuthenticationService *user_mgmt::UserManagement::authService = nullptr;
std::mutex user_mgmt::UserManagement::mutex;
