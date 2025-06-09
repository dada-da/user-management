//
// Created by Da on 3/6/25.
//

#ifndef AUTHENTICATION_SERVICE_H
#define AUTHENTICATION_SERVICE_H

#include "../../repository//user_data/user_data.h"
#include "../../model/user.h"
#include "./interface_authentication_service.h"

namespace auth {
    class AuthenticationService final : public IAuthenticationService {
        db_user::IUserDatabase *userDatabase;

    public:
        AuthenticationService(db_user::IUserDatabase *db) : userDatabase(db) {
        }

        data::User authenticateUser(const std::string &username, const std::string &password) override;
    };
}

#endif // AUTHENTICATION_SERVICE_H
