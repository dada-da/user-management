//
// Created by Da on 21/5/25.
//

#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include <mutex>
#include <memory>

#include "../user/user.h"

namespace user_mgmt {
    class UserManagement {
        static std::unique_ptr<UserManagement> pinstance;
        static std::mutex mutex;
        std::unique_ptr<User> currentUser;

    protected:
        UserManagement() = default;

    public:
        ~UserManagement() = default;

        static UserManagement *getInstance() {
            std::lock_guard lock(mutex);
            if (pinstance == nullptr) {
                pinstance = std::unique_ptr<UserManagement>(new UserManagement());
            }
            return pinstance.get();
        };

        UserManagement(const UserManagement &other) = delete;

        UserManagement &operator=(const UserManagement &other) = delete;

        UserManagement(UserManagement &&other) = delete;

        UserManagement &operator=(UserManagement &&other) = delete;

        // void setUserInfo(const std::string &username,
        //                  const std::string &name,
        //                  const std::string &email,
        //                  const std::string &password,
        //                  const std::string &role,
        //                  bool active,
        //                  int points = 0) {
        //     if (role == UserRoles::ADMIN) {
        //         currentUser = std::make_unique<Admin>(username, name, email, password, active);
        //     } else {
        //         currentUser = std::make_unique<Customer>(username, name, email, password, points, active);
        //     }
        // }

        void clearUser() {
            currentUser.reset();
        }

        std::string getUserName() {
            std::lock_guard lock(mutex);

            if (this->currentUser == nullptr) {
                throw std::runtime_error("User does not exist");
            }

            return this->currentUser->getUsername();
        }

        std::string getRole() {
            std::lock_guard lock(mutex);

            if (this->currentUser == nullptr) {
                throw std::runtime_error("User does not exist");
            }

            return this->currentUser->getRole();
        }

        bool isLoggedIn() const {
            std::lock_guard lock(mutex);


            if (this->currentUser == nullptr) {
                return false;
            }

            return this->currentUser->getUsername().empty();
        }
    };
}

#endif //USER_MANAGEMENT_H
