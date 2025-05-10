#include <iostream>
#include <algorithm>

#include "user_management.h"

UserManagement::UserManagement() : currentUser(nullptr) {
    users.emplace_back("admin", hashPassword("admin123"), "admin@system.com", Role::ADMIN);
    users.emplace_back("user", hashPassword("user123"), "user@system.com", Role::USER);
}

UserManagement::~UserManagement() {
}

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

    User *user = findUser(username);
    if (user && validatePassword(password, user->getPassword())) {
        currentUser = user;
        std::cout << "\nLogin successful! Welcome, " << username;
        if (user->getRole() == Role::ADMIN) {
            std::cout << " (Administrator)";
        }
        std::cout << "!\n";
    } else {
        std::cout << "\nInvalid credentials!\n";
    }
}

void UserManagement::registerUser() {
    //TODO
}

void UserManagement::searchUser() {
    std::string username;
    std::cout << "\n--- Search User ---\n";
    std::cout << "Enter username to search: ";
    std::cin >> username;

    //TODO
}

void UserManagement::deleteUser() const {
    if (!currentUser) {
        std::cout << "\nYou must be logged in to delete an account!\n";
        return;
    }

    //TODO
}

void UserManagement::logout() {
    if (currentUser) {
        std::cout << "\nLogging out... Goodbye, " << currentUser->getUsername() << "!\n";
        currentUser = nullptr;
    } else {
        std::cout << "\nYou are not logged in!\n";
    }
}

void UserManagement::createUser() {
    //TODO
}

void UserManagement::resetPassword() {
    //TODO
}
