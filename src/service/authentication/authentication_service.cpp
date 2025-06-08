//
// Created by Da on 3/6/25.
//

#include "../../utils/password_handler/password_handler.h"
#include "../authentication/authentication_service.h"

namespace auth {
    data::User AuthenticationService::authenticateUser(const std::string &username, const std::string &password) {
        auto user = userDatabase->findUserByUsername(username);
        if (!user.has_value()) {
            throw std::runtime_error("Username not found");
        }

        if (!user->isActive()) {
            throw std::runtime_error("User is not active");
        }

        if (!pw_util::PasswordHandler::comparePassword(password, user->getPassword(), user->getSalt())) {
            throw std::runtime_error("Password is wrong");
        }

        return user.value();
    }
}
