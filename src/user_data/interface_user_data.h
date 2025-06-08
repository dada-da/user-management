//
// Created by Da on 4/6/25.
//

#ifndef INTERFACE_USER_DATA_H
#define INTERFACE_USER_DATA_H

#include "../user/user.h"
#include <optional>

namespace db_user {
    class IUserDatabase {
    public:
        virtual ~IUserDatabase() = default;

        virtual void saveToFile() = 0;

        virtual void loadFromFile() = 0;

        virtual std::optional<data::User> findUserByUsername(const std::string &username) = 0;

        virtual void insertUser(const data::User &user) = 0;

        virtual bool updateUser(const data::User &user) = 0;

        virtual bool deleteUser(int userId) = 0;

        virtual std::optional<data::User> findUserById(int id) = 0;
    };
}

#endif //INTERFACE_USER_DATA_H
