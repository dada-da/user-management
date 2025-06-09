//
// Created by Da on 5/6/25.
//

#include <iostream>
#include <iomanip>
#include <optional>
#include "menu_action.h"
#include "../../utils/password_handler.h"
#include "../../utils/validator/validator.h"
#include "../../user_management/user_management.h"
#include "../../utils/date_time.h"
#include "../../utils/formatter.h"
#include "../../utils/print/print_data.h"

namespace menu {
    bool MenuAction::login() {
        const std::string validUsername = input::Validator::getValidUserName();

        if (validUsername.empty()) {
            return false;
        }

        const std::string validPassword = input::Validator::getPassword();

        if (validPassword.empty()) {
            return false;
        }

        try {
            user_mgmt::UserManagement::getInstance()->login(validUsername, validPassword);
        } catch (const std::exception &e) {
            throw std::runtime_error(e.what());
        }

        return true;
    }

    bool MenuAction::registerUser() {
        std::string validUsername;
        bool isValidUsername = false;

        while (!isValidUsername) {
            validUsername = input::Validator::getValidUserName();


            const std::optional<data::User> userData = userDatabase->findUserByUsername(validUsername);

            if (userData.has_value()) {
                std::cout << "\n❌ Username " << validUsername << " already exists." << std::endl;
                continue;
            }

            if (validUsername.empty()) {
                return false;
            }

            isValidUsername = true;
        }


        const std::string validPassword = input::Validator::getPassword();

        if (validPassword.empty()) {
            return false;
        }

        const std::string name = utils::Formatter::formatForStorage(input::Validator::getValidName());

        try {
            const std::string newSalt = pw_util::PasswordHandler::generateSalt();
            const std::string newHash = pw_util::PasswordHandler::getHashPassword(validPassword, newSalt);

            const auto newUser = data::User(validUsername, newHash, newSalt, UserRoles::CUSTOMER, name);

            userDatabase->create(newUser);

            constexpr int DEFAULT_BALANCE = 100;

            walletService->create(newUser.getUsername(), DEFAULT_BALANCE);
        } catch (const std::exception &e) {
            throw std::runtime_error(e.what());
        }

        return true;
    }

    void MenuAction::logout() {
        try {
            user_mgmt::UserManagement::getInstance()->logout();
        } catch (const std::exception &e) {
            throw std::runtime_error(e.what());
        }
    }

    void MenuAction::viewAccountDetail() {
        try {
            const auto userMgmt = user_mgmt::UserManagement::getInstance();

            if (!userMgmt->isLoggedIn()) {
                std::cout << "Not logged in";
                return;
            }

            auto user = userMgmt->getCurrentUser();

            std::cout << "\n                   GENERAL INFORMATION         " << std::endl;
            std::cout << "------------------------------------------------------------" << std::endl;
            std::cout << "👤 Name: " << std::left << utils::Formatter::formatForDisplay(user.getName()) << std::endl;
            std::cout << "🏷️ Username: " << std::left << user.getUsername() << std::endl;
            std::cout << "🎯 Role: " << std::left << (user.isAdmin() ? "👑 Administrator" : "👤 Customer") << std::endl;
            if (!user.isAdmin()) {
                std::cout << "💰 Points: " << std::left << walletService->getFormattedBalance() << std::endl;
            }
        } catch (const std::exception &e) {
            std::cerr << "Error loading profile: " << e.what() << std::endl;
        }
    }

    void MenuAction::viewFullAccountInfo() {
        try {
            const auto userMgmt = user_mgmt::UserManagement::getInstance();

            if (!userMgmt->isLoggedIn()) {
                std::cout << "Not logged in";
                return;
            }

            auto user = userMgmt->getCurrentUser();

            std::cout << PrintData::centerText("👤 PERSONAL INFORMATION", PrintData::SECTION_WIDTH) << "\n";
            PrintData::printBorder('-');

            PrintData::printField("Full Name", user.getName());
            PrintData::printField("Username", user.getUsername());
            PrintData::printField("User ID", user.getId());
            PrintData::printField("Role", user.isAdmin() ? "👑 Administrator" : "👤 Customer");

            if (!user.getDob().empty() || user.getDob() != "null") {
                PrintData::printField("Date of Birth", user.getDob());
            }

            std::cout << PrintData::centerText("📞 CONTACT INFORMATION", PrintData::SECTION_WIDTH) << std::endl;
            PrintData::printBorder('-');

            PrintData::printField("Email Address", user.getEmail());

            if (!user.getPhoneNumber().empty()) {
                PrintData::printField("Phone Number", user.getPhoneNumber());
            } else {
                PrintData::printField("Phone Number", "Not provided");
            }

            std::cout << PrintData::centerText("📊 ACCOUNT STATUS", PrintData::SECTION_WIDTH) << std::endl;
            PrintData::printBorder('-');

            PrintData::printField("Status", user.isActive() ? "✅ Active" : "❌ Inactive");

            if (!user.isAdmin()) {
                PrintData::printField("Points Balance", walletService->getFormattedBalance());
            }

            if (!user.getCreatedAt().empty()) {
                PrintData::printField("Member Since", user.getCreatedAt());
            }

            if (!user.getUpdatedAt().empty()) {
                PrintData::printField("Last Updated", user.getUpdatedAt());
            }

            std::cout << PrintData::centerText("🔒 SECURITY INFORMATION", PrintData::SECTION_WIDTH) << std::endl;
            PrintData::printBorder('-');

            PrintData::printField("Two-Factor Auth", user.getOtpId().empty() ? "❌ Disabled" : "✅ Enabled");

            if (!user.getUpdatedAt().empty()) {
                PrintData::printField("Last Activity", user.getUpdatedAt());
            }

            PrintData::printField("Security Level",
                                  user.getRole() == "ADMIN" ? "🔐 Administrator" : "🔑 Standard User");
        } catch (const std::exception &e) {
            std::cerr << "Error loading profile: " << e.what() << std::endl;
        }
    }

    void MenuAction::updateProfile() {
        auto userManager = user_mgmt::UserManagement::getInstance();
        if (!userManager || !userManager->isLoggedIn()) {
            std::cout << "Ban chua dang nhap!\n";
            return;
        }

        data::User currentUser = userManager->getCurrentUser();

        std::cout << "\n🔒 Nhap lai mat khau de xac thuc: ";
        std::string password = input::Validator::getPassword();

        if (!pw_util::PasswordHandler::comparePassword(password, currentUser.getPassword(), currentUser.getSalt())) {
            std::cout << "❌ Mat khau khong dung. Huy cap nhat.\n";
            return;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "\n--- Cap nhat thong tin ca nhan ---\n";
        std::cout << "Ten hien tai: " << currentUser.getName() << "\n";
        std::cout << "Ten moi (Enter de giu nguyen): ";
        std::string newName;
        std::getline(std::cin, newName);
        if (!newName.empty()) currentUser.setName(newName);

        std::cout << "Email hien tai: " << currentUser.getEmail() << "\n";
        std::cout << "Email moi (Enter de giu nguyen): ";
        std::string newEmail;
        std::getline(std::cin, newEmail);
        if (!newEmail.empty()) currentUser.setEmail(newEmail);

        std::cout << "SDT hien tai: " << currentUser.getPhoneNumber() << "\n";
        std::cout << "SDT moi (Enter de giu nguyen): ";
        std::string newPhone;
        std::getline(std::cin, newPhone);
        if (!newPhone.empty()) currentUser.setPhoneNumber(newPhone);

        std::cout << "Ngay sinh hien tai: " << currentUser.getDob() << "\n";
        std::cout << "Ngay sinh moi (Enter de giu nguyen): ";
        std::string newDob;
        std::getline(std::cin, newDob);
        if (!newDob.empty()) currentUser.setDob(newDob);

        if (userDatabase->update(currentUser)) {
            // Lấy lại user mới nhất từ database và cập nhật vào UserManagement
            auto updatedUserOpt = userDatabase->findUserByUsername(currentUser.getUsername());
            // if (updatedUserOpt.has_value()) {
            //     userManager->setCurrentUser(updatedUserOpt.value());
            // }
            std::cout << "\n✅ Cap nhat thong tin thanh cong!\n";
        } else {
            std::cout << "\n❌ Cap nhat that bai!\n";
        }
    }

    void MenuAction::searchUser() {
        std::cout << "\nNhap tu khoa tim kiem (username hoac email): ";
        std::string keyword;
        std::getline(std::cin, keyword);

        if (keyword.empty()) {
            std::cout << "Tu khoa khong duoc de trong!\n";
            return;
        }

        auto results = userDatabase->search(keyword);

        if (results.empty()) {
            std::cout << "\nKhong tim thay nguoi dung nao phu hop voi tu khoa \"" << keyword << "\".\n";
            return;
        }

        std::cout << "\nKet qua tim kiem (" << results.size() << "):\n";
        std::cout << "-------------------------------------------------------------\n";
        std::cout << std::left << std::setw(5) << "ID"
                << std::setw(20) << "Username"
                << std::setw(25) << "Email"
                << std::setw(15) << "Role"
                << std::setw(10) << "Trang thai"
                << std::endl;
        std::cout << "-------------------------------------------------------------\n";
        for (const auto &user: results) {
            std::cout << std::left << std::setw(5) << user.getId()
                    << std::setw(20) << user.getUsername()
                    << std::setw(25) << user.getEmail()
                    << std::setw(15) << user.getRole()
                    << std::setw(10) << (user.isActive() ? "Dang hoat dong" : "Bi khoa")
                    << std::endl;
        }
        std::cout << "-------------------------------------------------------------\n";
    }

    void MenuAction::changePassword() {
        const auto userManager = user_mgmt::UserManagement::getInstance();
        if (!userManager || !userManager->isLoggedIn()) {
            std::cout << "Not logged in" << std::endl;
            return;
        }

        try {
            std::cout << "Enter your old password: ";
            const std::string oldPassword = input::Validator::getPassword();

            data::User currentUser = userManager->getCurrentUser();
            const data::User user = authService->authenticateUser(currentUser.getUsername(), oldPassword);

            std::string newPassword;
            while (true) {
                newPassword = input::Validator::getPassword("Enter your new password: ");

                if (std::string confirmPassword = input::Validator::getPassword("\nConfirm password: ");
                    newPassword == confirmPassword) {
                    break;
                }
                std::cout << "❌ Error! Confirm password not match" << std::endl;
            }

            const std::string newSalt = pw_util::PasswordHandler::generateSalt();
            const std::string newHash = pw_util::PasswordHandler::getHashPassword(newPassword, newSalt);

            currentUser.setPassword(newPassword);
            currentUser.setSalt(newSalt);

            if (userDatabase->update(currentUser)) {
                std::cout << "\n✅ Change password successfully!" << std::endl;
            } else {
                throw std::runtime_error("❌ Change password failed!");
            }
        } catch (const std::exception &e) {
            throw std::runtime_error(e.what());
        }
    }

    bool MenuAction::transfer() {
        const auto userManager = user_mgmt::UserManagement::getInstance();

        const long long currentBalance = walletService->getBalance();
        std::string validUsername;
        bool isValid = false;

        while (!isValid) {
            validUsername = input::Validator::getValidUserName("👤 Enter received username: ");
            if (validUsername == userManager->getUserName()) {
                std::cout << "⚠️ Cannot transfer for yourself" << std::endl;
                return false;
            }
            isValid = true;
        }

        const long long validAmount = input::Validator::getAmountInput(currentBalance);

        if (validAmount == -1) {
            return false;
        }

        if (!walletService->transfer(validUsername, validAmount)) {
            std::cout << "⚠️ Somthing went wrong. Try again later" << std::endl;
            return false;
        }
        std::cout << std::endl;
        std::cout << "********************************************" << std::endl;
        std::cout << "*                                          *" << std::endl;
        std::cout << "*  ✅ Your transfer has been confirmed.    *" << std::endl;
        std::cout << "*                                          *" << std::endl;
        std::cout << "********************************************" << std::endl;
        std::cout << std::endl;
        return true;
    }

    void MenuAction::displayWalletDashboard() {
        walletService->displayWalletDashboard();
    }

    void MenuAction::displayPointHistory() {
    }

    bool MenuAction::createUser() {
        std::string validUsername;
        bool isValidUsername = false;

        while (!isValidUsername) {
            validUsername = input::Validator::getValidUserName();


            const std::optional<data::User> userData = userDatabase->findUserByUsername(validUsername);

            if (userData.has_value()) {
                std::cout << "\n❌ Username " << validUsername << " already exists." << std::endl;
                continue;
            }

            if (validUsername.empty()) {
                return false;
            }

            isValidUsername = true;
        }


        const std::string validPassword = input::Validator::getPassword();

        if (validPassword.empty()) {
            return false;
        }

        const std::string name = utils::Formatter::formatForStorage(input::Validator::getValidName("Enter name:"));

        std::string line;
        bool isAdmin = false;

        while (true) {
            std::cout << "Choose (1 = 👑 Admin, 2 = 👤 Customer): ";
            std::string line;
            std::getline(std::cin, line);
            std::stringstream ss(line);
            int choice;
            if (ss >> choice && (choice == 1 || choice == 2)) {
                isAdmin = choice == 1;
                break;
            }
            std::cout << "❌ Invalid input. Try again.\n";
        }

        try {
            const std::string newSalt = pw_util::PasswordHandler::generateSalt();
            const std::string newHash = pw_util::PasswordHandler::getHashPassword(validPassword, newSalt);

            std::string role = UserRoles::CUSTOMER;

            if (isAdmin) {
                role = UserRoles::ADMIN;
            }

            const auto newUser = data::User(validUsername, newHash, newSalt, role, name);

            userDatabase->create(newUser);

            if (!isAdmin) {
                constexpr int DEFAULT_BALANCE = 100;

                walletService->create(newUser.getUsername(), DEFAULT_BALANCE);
            }
        } catch (const std::exception &e) {
            throw std::runtime_error(e.what());
        }

        return true;
    }
}
