#include <iostream>
#include <algorithm>

#include "user_management.h"
#include "user.h"
#include "../database/db_connection.h"
#include "../database_constants/user_queries.h"
#include "../database_constants/user_table.h"

UserManagement::UserManagement() : currentUser(nullptr) {
    if (!findUserByUsername("admin")) {
        createUser(
            "admin",
            " Super Admin",
            "admin@system.com",
            "admin123",
            user_table::roles::ADMIN,
            true);
    }

    if (!findUserByUsername("user")) {
        createUser(
            "user",
            "Default User",
            "user@system.com",
            "user123",
            user_table::roles::USER,
            true);
    }
}

UserManagement::~UserManagement() = default;

std::string UserManagement::hashPassword(const std::string &password) {
    std::string hashed = password;
    for (char &c: hashed) {
        c = ((c + 5) % 128);
    }
    return hashed;
}

bool UserManagement::validatePassword(const std::string &inputPassword, const std::string &storedPassword) {
    return hashPassword(inputPassword) == storedPassword;
}

User *UserManagement::findUser(const std::string &username) {
    auto it = std::find_if(users.begin(), users.end(),
                           [&username](const User &user) { return user.getUsername() == username; });

    if (it != users.end()) {
        return &(*it);
    }
    return nullptr;
}

void UserManagement::login() {
    if (currentUser) {
        std::cout << "\nYou are already logged in as: " << currentUser->getUsername() << "\n";
        return;
    }

    std::string username, password;
    std::cout << "\n--- Login ---\n";
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    if (auto user = findUserByUsername(username); user && validatePassword(password, user->getPassword())) {
        currentUser = new User(*user);
        std::cout << "\nLogin successful! Welcome, " << username;
        if (user->getRole() == user_table::roles::ADMIN) {
            std::cout << " (Administrator)";
        }
        std::cout << "!\n";
    } else {
        std::cout << "\nInvalid credentials!\n";
    }
}

void UserManagement::registerUser() {
    // TODO
}

void UserManagement::searchUser() {
    // TODO
}

void UserManagement::deleteUser() const {
    // TODO
}

void UserManagement::logout() {
    if (currentUser) {
        std::cout << "\nLogging out... Goodbye, " << currentUser->getUsername() << "!\n";
        delete currentUser;
        currentUser = nullptr;
    } else {
        std::cout << "\nYou are not logged in!\n";
    }
}

void UserManagement::resetPassword() {
    // TODO
}

bool UserManagement::createUser(const std::string &username, const std::string &name,
                                const std::string &email, const std::string &password,
                                const std::string &role, bool active) {
    //TODO
    const std::string hashedPassword = hashPassword(password);

    const std::vector<std::string> params = {
        username,
        name,
        email,
        hashedPassword,
        role,
        active ? "1" : "0"
    };

    const auto result = DBConnection::getInstance().executePreparedStatement(user_queries::INSERT_USER, params);
    return result != nullptr;
}

std::optional<User> UserManagement::findUserByUsername(const std::string &username) {
    const std::vector<std::string> params = {username};
    const auto result = DBConnection::getInstance().executePreparedStatement(
        user_queries::SELECT_USER_BY_USERNAME, params);

    if (!result) {
        return std::nullopt;
    }

    try {
        auto row = result->fetchOne();
        if (!row) {
            return std::nullopt;
        }

        return User(
            row.get(0).get<std::string>(),
            row.get(1).get<std::string>(),
            row.get(4).get<std::string>(),
            row.get(5).get<std::string>(),
            row.get(7).get<std::string>(),
            row.get(8).get<bool>());
    } catch (const std::exception &e) {
        std::cerr << "Error parsing user data: " << e.what() << std::endl;
        return std::nullopt;
    }
}

std::optional<User> UserManagement::findUserByEmail(const std::string &email) {
    std::vector params = {email};
    auto result = DBConnection::getInstance().executePreparedStatement(user_queries::SELECT_USER_BY_EMAIL, params);
    // TODO
    return std::nullopt;
}

std::vector<User> UserManagement::getAllUsers() {
    auto result = DBConnection::getInstance().executePreparedStatement(user_queries::SELECT_ALL_USERS, {});
    // TODO
    return {};
}

std::unique_ptr<mysqlx::SqlResult> UserManagement::updateUser(const std::string &username, const std::string &name,
                                                              const std::string &email, const std::string &role,
                                                              bool active) {
    //TODO
    std::vector<std::string> params = {
        name,
        email,
        role,
        active ? "1" : "0",
        username
    };
    return DBConnection::getInstance().executePreparedStatement(user_queries::UPDATE_USER, params);
}

std::unique_ptr<mysqlx::SqlResult> UserManagement::updatePassword(const std::string &username,
                                                                  const std::string &newPassword) {
    //TODO
    std::string hashedPassword = hashPassword(newPassword);
    std::vector<std::string> params = {hashedPassword, username};
    return DBConnection::getInstance().executePreparedStatement(user_queries::UPDATE_PASSWORD, params);
}

std::unique_ptr<mysqlx::SqlResult> UserManagement::updateOTP(const std::string &username, const std::string &otp) {
    std::vector params = {otp, username};
    //TODO
    return DBConnection::getInstance().executePreparedStatement(user_queries::UPDATE_OTP, params);
}

std::unique_ptr<mysqlx::SqlResult> UserManagement::deactivateUser(const std::string &username) {
    std::vector params = {username};
    //TODO
    return DBConnection::getInstance().executePreparedStatement(user_queries::DEACTIVATE_USER, params);
}

std::vector<User> UserManagement::searchUsers(const std::string &searchTerm) {
    std::string likeTerm = "%" + searchTerm + "%";
    std::vector params = {likeTerm, likeTerm, likeTerm};
    auto result = DBConnection::getInstance().executePreparedStatement(user_queries::SEARCH_USERS, params);
    // TODO
    return {};
}
