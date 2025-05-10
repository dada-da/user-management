#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#include <vector>
#include <string>

#include "user.h"

class UserManagement {
    std::vector<User> users;
    User *currentUser;

    User *findUser(const std::string &username);

    static std::string hashPassword(const std::string &password);

    static bool validatePassword(const std::string &inputPassword, const std::string &storedPassword);

public:
    UserManagement();

    ~UserManagement();

    void login();

    static void registerUser();

    static void searchUser();

    void createUser();

    static void resetPassword();

    void deleteUser() const;

    void logout();

    User *getCurrentUser() const { return currentUser; }

    const std::vector<User> &getAllUsers() const { return users; }
};

#endif // USER_MANAGEMENT_H
