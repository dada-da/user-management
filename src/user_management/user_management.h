//
// Created by Da on 21/5/25.
//

#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include <iostream>
#include <mutex>
#include <memory>

#include "../user/user.h"
#include "../user/admin.h"
#include "../user/customer.h"
#include "../role/role.h"

namespace user_mgmt {
    class UserManagement {
        static UserManagement *pinstance;
        static std::mutex mutex;
        std::unique_ptr<User> currentUser;

    protected:
        UserManagement() = default;

        ~UserManagement() = default;

    public:
        static UserManagement *getInstance() {
            std::lock_guard lock(mutex);
            if (pinstance == nullptr) {
                pinstance = new UserManagement();
            }
            return pinstance;
        };

        UserManagement(UserManagement &other) = delete;

        void operator=(const UserManagement &) = delete;

        void setUserInfo(const std::string &username,
                         const std::string &name,
                         const std::string &email,
                         const std::string &password,
                         const std::string &role,
                         bool active,
                         int points = 0) {
            if (role == UserRoles::ADMIN) {
                currentUser = std::make_unique<Admin>(username, name, email, password, active);
            } else {
                currentUser = std::make_unique<Customer>(username, name, email, password, points, active);
            }
        };

        void clearUser() {
            currentUser.reset();
        }
    };
}

#endif //USER_MANAGEMENT_H
