//
// Created by Da on 3/6/25.
//

#include "../../utils/password_handler/password_handler.h"
#include "../authentication/authentication_service.h"

namespace auth {
    AuthResult AuthenticationService::authenticateUser(const std::string &username, const std::string &password) {
        const auto user = userDatabase->findUserByUsername(username);
        if (!user.has_value()) {
            return AuthResult::USER_NOT_FOUND;
        }

        if (!user->isActive()) {
            return AuthResult::ACCOUNT_NOT_ACTIVE;
        }

        if (!passwordHandler->comparePassword(password, user->getPassword(), user->getSalt())) {
            return AuthResult::AUTHENTICATION_FAILED;
        }

        return AuthResult::SUCCESS;
    }
}
