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

        virtual std::string generateSalt() const = 0;

        virtual std::string getHashPassword(const std::string &password, const std::string &salt) const = 0;

        virtual bool comparePassword(const std::string &plainPassword,
                                     const std::string &hashedPassword,
                                     const std::string &salt) const = 0;
    };
}


#endif //PASSWORD_HANDLER_H
