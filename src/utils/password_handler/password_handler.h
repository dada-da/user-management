//
// Created by Da on 4/6/25.
//

#ifndef PASSWORD_HANDLER_H
#define PASSWORD_HANDLER_H

#include <string>

namespace pw_util {
    class IPasswordHandler {
    public:
        virtual ~IPasswordHandler() = default;

        virtual std::string generateSalt() = 0;

        virtual std::string getHashPassword(const std::string &password, const std::string &salt) = 0;

        virtual bool comparePassword(const std::string &plainPassword,
                                     const std::string &hashedPassword,
                                     const std::string &salt) = 0;
    };

    class PasswordHandler : public IPasswordHandler {
        static constexpr int maxInteration = 1500;
        static constexpr int saltLength = 16;
        static constexpr std::string secretKey = "SecretKey:))";

        static std::string createStrongerHash(const std::string &input);

    public:
        std::string generateSalt() override;

        std::string getHashPassword(const std::string &password, const std::string &salt) override;

        bool comparePassword(const std::string &plainPassword,
                             const std::string &hashedPassword,
                             const std::string &salt) override;
    };
}


#endif //PASSWORD_HANDLER_H
