//
// Created by Da on 5/6/25.
//

#include <iostream>
#include <string>
#include <sstream>
#include "validator.h"
#include "../formatter.h"

namespace input {
    std::string Validator::trimSpace(const std::string &str) {
        const size_t start = str.find_first_not_of(" \t\n\r");
        if (start == std::string::npos) return "";

        const size_t end = str.find_last_not_of(" \t\n\r");
        return str.substr(start, end - start + 1);
    }

    bool Validator::isValidUserName(const std::string &username) {
        constexpr auto rules = UsernameRules{};

        if (username.length() < rules.minLength || username.length() > rules.maxLength) {
            std::cout << "❌ Username must be between 3 and 20 characters.\n";
            return false;
        }

        if (!std::isalpha(username[0])) {
            std::cout << "❌ Username must start with alpha character.\n";
            return false;
        }

        for (size_t i = 0; i < username.length(); i++) {
            const char c = username[i];

            if (std::isspace(c)) {
                std::cout << "❌ Username must not contain space character.\n";
                return false;
            }

            if (c == '_' && !rules.allowUnderscore) {
                std::cout << "❌ Username must not contain underscore (_) character.\n";
                return false;
            }

            if (c == '-' && !rules.allowDash) {
                std::cout << "❌ Username must not contain dash (-) character.\n";
                return false;
            }
        }

        return true;
    }

    bool Validator::isValidName(const std::string &name) {
        if (name.length() < NameRules::minLength || name.length() > NameRules::maxLength) {
            std::cout << "❌ Name must be between " << NameRules::minLength
                    << " and " << NameRules::maxLength << " characters.\n";
            return false;
        }

        if constexpr (!NameRules::allowLeadingTrailingSpaces) {
            if (!name.empty() && (name.front() == ' ' || name.back() == ' ')) {
                std::cout << "❌ Name cannot start or end with spaces.\n";
                return false;
            }
        }

        bool hasConsecutiveSpaces = false;
        bool hasValidChar = false;

        for (size_t i = 0; i < name.length(); i++) {
            const char c = name[i];

            if (!std::isalpha(c) && c != ' ') {
                std::cout << "❌ Name can only contain letters and spaces.\n";
                return false;
            }

            if (c == ' ') {
                if (i > 0 && name[i - 1] == ' ' && !NameRules::allowMultipleSpaces) {
                    hasConsecutiveSpaces = true;
                }
            } else {
                hasValidChar = true;
            }
        }

        if (hasConsecutiveSpaces) {
            std::cout << "❌ Name cannot contain multiple consecutive spaces.\n";
            return false;
        }

        if (!hasValidChar) {
            std::cout << "❌ Name must contain at least one letter.\n";
            return false;
        }

        return true;
    }

    std::string Validator::getValidName(const std::string &label) {
        std::string name;
        bool isValid = false;

        while (!isValid) {
            std::cout << "\nPress enter to go back." << std::endl;
            std::cout << label;
            std::getline(std::cin, name);

            if (name.empty()) {
                return name;
            }

            name = utils::Formatter::normalizeSpaces(name);

            if (isValidName(name)) {
                std::transform(name.begin(), name.end(), name.begin(), ::tolower);
                isValid = true;
            }
        }

        return name;
    }


    std::string Validator::getValidUserName(const std::string &label) {
        std::string username;
        bool isValid = false;

        while (!isValid) {
            std::cout << "\nPress enter to go back." << std::endl;
            std::cout << label;
            std::getline(std::cin, username);

            if (username.empty()) {
                return username;
            }

            if (isValidUserName(username)) {
                isValid = true;
            }
        }

        return username;
    }

    std::string Validator::getPassword(const std::string &label) {
        std::string password;

        while (true) {
            std::cout << "\nPress enter to go back." << std::endl;
            std::cout << label;
            std::getline(std::cin, password);

            if (password.empty()) {
                return password;
            }

            if (password.length() < 4) {
                std::cout << "❌ Password must be at least 4 characters long!\n";
                continue;
            }

            if (password.length() > 20) {
                std::cout << "❌ Password too long! Maximum 20 characters.\n";
                continue;
            }

            break;
        }

        return password;
    }

    long long Validator::getAmountInput(const long long maxAmount) {
        std::string input;
        long long amount;
        while (true) {
            std::cout << "\nPress enter to go back." << std::endl;
            std::cout << "\n💰 " << "Enter amount";

            if (maxAmount > 0) {
                std::cout << " (Max: " << utils::Formatter::formatCurrency(maxAmount) << ")";
            }
            std::cout << ": ";

            if (std::getline(std::cin, input)) {
                if (input.empty()) {
                    return -1;
                }

                try {
                    amount = std::stoll(input);

                    if (amount > 0 && (maxAmount < 0 || amount <= maxAmount)) {
                        return amount;
                    }
                    std::cout << "❌ Invalid amount. Please try again." << std::endl;
                } catch (const std::exception &) {
                    std::cout << "❌ Please enter a valid number." << std::endl;
                }
            }
        }
    }
}
