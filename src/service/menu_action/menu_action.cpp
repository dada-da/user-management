//
// Created by Da on 5/6/25.
//

#include <iostream>
#include <iomanip>
#include "menu_action.h"
#include "../../utils/validator/validator.h"
#include "../../user_management/user_management.h"
#include "../../utils/print/print_data.h"

namespace menu {
    void MenuAction::login() {
        std::string usernameValue, passwordValue;

        std::cout << "Enter username: ";
        const std::string validUsername = input::Validator::getValidUserName();

        std::cout << "Enter password: ";
        const std::string validPassword = input::Validator::getPassword();

        try {
            user_mgmt::UserManagement::getInstance()->login(validUsername, validPassword);
        } catch (const std::exception &e) {
            throw std::runtime_error(e.what());
        }

        std::cout << "Logged in successfully!" << std::endl;
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
            std::cout << "👤 Name: " << std::left << user.getName() << std::endl;
            std::cout << "🏷️ Username: " << std::left << user.getUsername() << std::endl;
            std::cout << "🎯 Role: " << std::left << (user.isAdmin() ? "👑 Administrator" : "👤 Customer") << std::endl;
            if (!user.isAdmin()) {
                std::cout << "💰 Points: " << std::left << (std::to_string(user.getPoints()) + " points") << std::endl;
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
                PrintData::printField("Points Balance", user.getPoints());
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
}
