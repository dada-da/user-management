//
// Created by Da on 21/5/25.
//

#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

#include "../role/role.h"

class Admin : public User {
public:
    Admin(const std::string &username,
          const std::string &name,
          const std::string &email,
          const std::string &password,
          const bool active): User(username, name, email,
                                   password, UserRoles::ADMIN, active) {
    }
};

#endif //ADMIN_H
