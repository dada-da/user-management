#ifndef USER_QUERIES_H
#define USER_QUERIES_H

#include <string>

#include "user_table.h"

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

    inline const std::string INIT_ROOT_USER =
            "INSERT IGNORE INTO `" + std::string(user_table::TABLE_NAME) + "` ("
            "`" + std::string(user_table::columns::USERNAME) + "`, "
            "`" + std::string(user_table::columns::NAME) + "`, "
            "`" + std::string(user_table::columns::EMAIL) + "`, "
            "`" + std::string(user_table::columns::PASSWORD_HASH) + "`, "
            "`" + std::string(user_table::columns::ROLE) + "`, "
            "`" + std::string(user_table::columns::ACTIVE) + "`) "
            "VALUES ("
            "'admin', "
            "'System Administrator', "
            "'admin@system.com', "
            "'$2a$10$YOUR_HASHED_PASSWORD_HERE', "
            "'" + user_table::roles::ADMIN + "', "
            "TRUE)";

    inline const std::string INIT_NORMAL_USER =
            "INSERT IGNORE INTO `" + std::string(user_table::TABLE_NAME) + "` ("
            "`" + std::string(user_table::columns::USERNAME) + "`, "
            "`" + std::string(user_table::columns::NAME) + "`, "
            "`" + std::string(user_table::columns::EMAIL) + "`, "
            "`" + std::string(user_table::columns::PASSWORD_HASH) + "`, "
            "`" + std::string(user_table::columns::ROLE) + "`, "
            "`" + std::string(user_table::columns::ACTIVE) + "`) "
            "VALUES ("
            "'user', "
            "'Default User', "
            "'user@system.com', "
            "'$2a$10$YOUR_HASHED_PASSWORD_HERE', "
            "'" + user_table::roles::USER + "', "
            "TRUE)";

    inline const std::string INSERT_USER =
            "INSERT INTO `" + std::string(user_table::TABLE_NAME) + "` ("
            "`" + std::string(user_table::columns::USERNAME) + "`, "
            "`" + std::string(user_table::columns::NAME) + "`, "
            "`" + std::string(user_table::columns::EMAIL) + "`, "
            "`" + std::string(user_table::columns::PASSWORD_HASH) + "`, "
            "`" + std::string(user_table::columns::ROLE) + "`, "
            "`" + std::string(user_table::columns::ACTIVE) + "`) "
            "VALUES (?, ?, ?, ?, ?, ?)";
}

#endif //USER_QUERIES_H