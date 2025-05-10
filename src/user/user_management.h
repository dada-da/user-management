#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include <vector>
#include <string>
#include <optional>
#include <memory>
#include <mysqlx/xdevapi.h>

#include "user.h"

class UserManagement {
    std::vector<User> users;
    User *currentUser;

    User *findUser(const std::string &username);

    static bool validatePassword(const std::string &inputPassword, const std::string &storedPassword);

public:
    UserManagement();

    ~UserManagement();

    void login();

    void logout();

    static void resetPassword();

    static void registerUser();

    static void searchUser();

    void deleteUser() const;

    bool createUser(const std::string &username, const std::string &name,
                    const std::string &email, const std::string &password,
                    const std::string &role, bool active);

    static std::optional<User> findUserByUsername(const std::string &username);

    static std::optional<User> findUserByEmail(const std::string &email);

    static std::vector<User> getAllUsers();

    std::unique_ptr<mysqlx::SqlResult> updateUser(const std::string &username, const std::string &name,
                                                  const std::string &email, const std::string &role, bool active);

    std::unique_ptr<mysqlx::SqlResult> updatePassword(const std::string &username, const std::string &newPassword);

    std::unique_ptr<mysqlx::SqlResult> updateOTP(const std::string &username, const std::string &otp);

    std::unique_ptr<mysqlx::SqlResult> deactivateUser(const std::string &username);

    static std::vector<User> searchUsers(const std::string &searchTerm);

    User *getCurrentUser() const { return currentUser; }

    static std::string hashPassword(const std::string &password);
};

#endif // USER_MANAGEMENT_H
