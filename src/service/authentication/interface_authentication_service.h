//
// Created by Da on 4/6/25.
//

#ifndef INTERFACE_AUTHENTICATION_SERVICE_H
#define INTERFACE_AUTHENTICATION_SERVICE_H

#include <string>

namespace auth {
    enum class AuthResult {
        SUCCESS,
        USER_NOT_FOUND,
        INVALID_PASSWORD,
        ACCOUNT_NOT_ACTIVE,
        AUTHENTICATION_FAILED
    };

    class IAuthenticationService {
    public:
        virtual ~IAuthenticationService() = default;

        virtual AuthResult authenticateUser(const std::string &username, const std::string &password) = 0;
    };
}

#endif //INTERFACE_AUTHENTICATION_SERVICE_H
