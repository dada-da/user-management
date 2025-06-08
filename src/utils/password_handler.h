//
// Created by Da on 4/6/25.
//

#ifndef PASSWORD_HANDLER_H
#define PASSWORD_HANDLER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>

namespace pw_util {
    class PasswordHandler final {
        static constexpr int maxInteration = 1500;
        static constexpr int saltLength = 16;
        static constexpr char secretKey[13] = "SecretKey:))";

        static std::string createStrongerHash(const std::string &input) {
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

        static uint64_t customHash(const std::string &str) {
            int64_t hash = 14695981039346656037ULL;

            for (const char c: str) {
                constexpr uint64_t prime = 1099511628211ULL;
                hash ^= static_cast<uint64_t>(c);
                hash *= prime;
            }

            return hash;
        };

    public:
        static std::string generateSalt() {
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

        static std::string getHashPassword(const std::string &password, const std::string &salt) {
            const std::string saltedPassword = password + salt + secretKey;
            return createStrongerHash(saltedPassword);
        }

        static bool comparePassword(const std::string &plainPassword,
                                    const std::string &hashedPassword,
                                    const std::string &salt) {
            const std::string hashedInput = getHashPassword(plainPassword, salt);
            return hashedInput == hashedPassword;
        }

        void regenerateDefaultPasswords() {
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

        static void generateSomePassword(const std::string &password) {
            const std::string userSalt = generateSalt();
            const std::string userHash = getHashPassword(password, userSalt);
            std::cout << "User - Salt: " << userSalt << std::endl;
            std::cout << "User - Hash: " << userHash << std::endl;
        };
    };
}


#endif //PASSWORD_HANDLER_H
