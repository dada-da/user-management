//
// Created by Da on 6/5/25.
//

#ifndef USERQUERIES_H
#define USERQUERIES_H

#include <string>

#include "UserTable.h"

namespace user_queries {
    inline const std::string CREATE_TABLE =
            "CREATE TABLE IF NOT EXISTS `" + std::string(user_table::TABLE_NAME) + "` ("
            "  `" + std::string(user_table::columns::USERNAME) + "` VARCHAR(" + std::to_string(
                user_table::constraints::MAX_USERNAME_LENGTH) + ") PRIMARY KEY,"
            "  `" + std::string(user_table::columns::NAME) + "` VARCHAR(" + std::to_string(
                user_table::constraints::MAX_NAME_LENGTH) + ") NOT NULL,"
            "  `" + std::string(user_table::columns::DATE_OF_BIRTH) + "` DATE,"
            "  `" + std::string(user_table::columns::PHONE_NUMBER) + "` CHAR(" + std::to_string(
                user_table::constraints::MAX_PHONE_LENGTH) + "),"
            "  `" + std::string(user_table::columns::EMAIL) + "` VARCHAR(" + std::to_string(
                user_table::constraints::MAX_EMAIL_LENGTH) + ") NOT NULL UNIQUE,"
            "  `" + std::string(user_table::columns::PASSWORD_HASH) + "` VARCHAR(" + std::to_string(
                user_table::constraints::MAX_PASSWORD_LENGTH) + ") NOT NULL,"
            "  `" + std::string(user_table::columns::OTP_ID) + "` VARCHAR(" + std::to_string(
                user_table::constraints::MAX_OTP_LENGTH) + "),"
            "  `" + std::string(user_table::columns::ROLE) + "` ENUM('" + user_table::roles::ADMIN + "', '" +
            user_table::roles::USER
            + "', '" + "') NOT NULL DEFAULT '" + user_table::roles::USER + "',"
            "  `" + std::string(user_table::columns::ACTIVE) + "` BOOLEAN NOT NULL DEFAULT TRUE,"
            "  `" + std::string(user_table::columns::CREATED_AT) + "` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
            "  `" + std::string(user_table::columns::UPDATED_AT) +
            "` TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP"
            ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4";
}

#endif //USERQUERIES_H
