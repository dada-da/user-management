//
// Created by Da on 4/6/25.
//

#include <fstream>
#include <string>
#include <sstream>
#include <functional>
#include <random>
#include <chrono>

#include "password_handler.h"

class PasswordHandler : public pw_util::IPasswordHandler {
    static constexpr int maxInteration = 1500;
    static constexpr int saltLength = 16;
    static constexpr std::string secretKey = "SecretKey:))";

    static std::string createStrongerHash(const std::string &input) {
        std::string result = input;

        for (int i = 0; i < maxInteration; ++i) {
            std::hash<std::string> hasher;
            const size_t hash1 = hasher(result);
            const size_t hash2 = hasher(result + std::to_string(i));
            const size_t hash3 = hasher(std::to_string(hash1) + std::to_string(hash2));

            std::stringstream ss;
            ss << std::hex << hash1 << hash2 << hash3;
            result = ss.str();
        }

        return result;
    }

public:
    std::string generateSalt() {
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

    std::string getHashPassword(const std::string &password, const std::string &salt) {
        const std::string saltedPassword = password + salt + secretKey;
        return createStrongerHash(saltedPassword);
    }

    bool comparePassword(const std::string &plainPassword,
                         const std::string &hashedPassword,
                         const std::string &salt) {
        const std::string hashedInput = getHashPassword(plainPassword, salt);
        return hashedInput == hashedPassword;
    }
};
