//
// Created by Da on 4/6/25.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <chrono>

#include "password_handler.h"

namespace pw_util {
    uint64_t PasswordHandler::customHash(const std::string &str) {
        uint64_t hash = 14695981039346656037ULL;

        for (const char c: str) {
            constexpr uint64_t prime = 1099511628211ULL;
            hash ^= static_cast<uint64_t>(c);
            hash *= prime;
        }

        return hash;
    }

    std::string PasswordHandler::createStrongerHash(const std::string &input) {
        std::string result = input;

        for (int i = 0; i < maxInteration; ++i) {
            const uint64_t hash1 = customHash(result);
            const uint64_t hash2 = customHash(result + std::to_string(i));
            const uint64_t hash3 = customHash(std::to_string(hash1) + std::to_string(hash2));

            std::stringstream ss;
            ss << std::hex << hash1 << hash2 << hash3;
            result = ss.str();
        }

        return result;
    }

    std::string PasswordHandler::generateSalt() {
        const std::string basicChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*";

        const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::mt19937 gen(seed);
        std::uniform_int_distribution<> dis(0, basicChars.size() - 1);

        std::string salt;
        for (int i = 0; i < saltLength; ++i) {
            salt += basicChars[dis(gen)];
        }
        return salt;
    }

    std::string PasswordHandler::getHashPassword(const std::string &password, const std::string &salt) {
        const std::string saltedPassword = password + salt + secretKey;
        return createStrongerHash(saltedPassword);
    }


    bool PasswordHandler::comparePassword(const std::string &plainPassword,
                                          const std::string &hashedPassword,
                                          const std::string &salt) {
        const std::string hashedInput = getHashPassword(plainPassword, salt);
        return hashedInput == hashedPassword;
    }

    void PasswordHandler::regenerateDefaultPasswords() {
        // Customer user
        const std::string customerSalt = generateSalt();
        const std::string customerHash = getHashPassword("customer", customerSalt);
        std::cout << "Customer - Salt: " << customerSalt << std::endl;
        std::cout << "Customer - Hash: " << customerHash << std::endl;

        // Admin user
        const std::string adminSalt = generateSalt();
        const std::string adminHash = getHashPassword("root", adminSalt);
        std::cout << "Admin - Salt: " << adminSalt << std::endl;
        std::cout << "Admin - Hash: " << adminHash << std::endl;
    }

    void PasswordHandler::generateSomePassword(const std::string &password) {
        const std::string userSalt = generateSalt();
        const std::string userHash = getHashPassword(password, userSalt);
        std::cout << "User - Salt: " << userSalt << std::endl;
        std::cout << "User - Hash: " << userHash << std::endl;
    }
}
