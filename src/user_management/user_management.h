//
// Created by Da on 21/5/25.
//

#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include <mutex>
#include <memory>

#include "../user/user.h"
#include "../service/authentication/interface_authentication_service.h"

namespace user_mgmt {
    class UserManagement {
        static std::unique_ptr<UserManagement> pinstance;
        static std::mutex mutex;
        std::unique_ptr<data::User> currentUser;
        static auth::IAuthenticationService *authService;

    protected:
        UserManagement() = default;

    public:
        ~UserManagement() = default;

        static UserManagement *getInstance(auth::IAuthenticationService *authInstance = nullptr) {
            std::lock_guard lock(mutex);

            if (pinstance != nullptr && authService != nullptr) return pinstance.get();

            if (authService == nullptr && authInstance == nullptr) {
                throw std::invalid_argument("Authentication service must be provided on first initialization");
            }

            pinstance = std::unique_ptr<UserManagement>(new UserManagement());

            authService = authInstance;

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

        data::User getCurrentUser() const {
            std::lock_guard lock(mutex);
            return *currentUser;
        }

        std::string getUserName() const {
            std::lock_guard lock(mutex);

            if (this->currentUser == nullptr) {
                throw std::runtime_error("User does not exist");
            }

            return this->currentUser->getUsername();
        }

        std::string getRole() const {
            std::lock_guard lock(mutex);

            if (this->currentUser == nullptr) {
                throw std::runtime_error("User does not exist");
            }

            return this->currentUser->getRole();
        }

        bool isAdmin() const {
            std::lock_guard lock(mutex);

            return this->currentUser->isAdmin();
        }

        bool isLoggedIn() const {
            std::lock_guard lock(mutex);

            if (this->currentUser == nullptr) {
                return false;
            }

            return !this->currentUser->getUsername().empty();
        }

        void login(const std::string &username, const std::string &password) {
            std::lock_guard lock(mutex);
            try {
                if (this->currentUser != nullptr) {
                    throw std::runtime_error("User already logged in");
                }
                const data::User user = authService->authenticateUser(username, password);
                this->currentUser = std::make_unique<data::User>(user);
            } catch (const std::exception &e) {
                throw std::runtime_error(e.what());
            }
        }
    };
}

#endif //USER_MANAGEMENT_H
