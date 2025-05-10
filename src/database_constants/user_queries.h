#ifndef USER_QUERIES_H
#define USER_QUERIES_H

#include <string>

#include "user_table.h"

namespace user_queries {
    inline const std::string CREATE_TABLE =
            "CREATE TABLE IF NOT EXISTS `" + std::string(user_table::TABLE_NAME) + "` ("
            "  `" +
            std::string(user_table::columns::USERNAME) + "` VARCHAR(" + std::to_string(
                user_table::constraints::MAX_USERNAME_LENGTH) + ") PRIMARY KEY,"
            "  `" +
            std::string(user_table::columns::NAME) + "` VARCHAR(" + std::to_string(
                user_table::constraints::MAX_NAME_LENGTH) + ") NOT NULL,"
            "  `" +
            std::string(user_table::columns::DATE_OF_BIRTH) + "` DATE,"
            "  `" +
            std::string(user_table::columns::PHONE_NUMBER) + "` CHAR(" + std::to_string(
                user_table::constraints::MAX_PHONE_LENGTH) + "),"
            "  `" +
            std::string(user_table::columns::EMAIL) + "` VARCHAR(" + std::to_string(
                user_table::constraints::MAX_EMAIL_LENGTH) + ") NOT NULL UNIQUE,"
            "  `" +
            std::string(user_table::columns::PASSWORD_HASH) + "` VARCHAR(" + std::to_string(
                user_table::constraints::MAX_PASSWORD_LENGTH) + ") NOT NULL,"
            "  `" +
            std::string(user_table::columns::OTP_ID) + "` VARCHAR(" + std::to_string(
                user_table::constraints::MAX_OTP_LENGTH) + "),"
            "  `" +
            std::string(user_table::columns::ROLE) + "` ENUM('" + user_table::roles::ADMIN + "', '" +
            user_table::roles::USER + "') NOT NULL DEFAULT '" + user_table::roles::USER + "',"
            "  `" +
            std::string(user_table::columns::ACTIVE) + "` BOOLEAN NOT NULL DEFAULT TRUE,"
            "  `" +
            std::string(user_table::columns::CREATED_AT) + "` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
            "  `" +
            std::string(user_table::columns::UPDATED_AT) +
            "` TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP"
            ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4";

    inline const std::string INSERT_USER =
            "INSERT INTO `" + std::string(user_table::TABLE_NAME) + "` ("
            "`" +
            std::string(user_table::columns::USERNAME) + "`, "
            "`" +
            std::string(user_table::columns::NAME) + "`, "
            "`" +
            std::string(user_table::columns::EMAIL) + "`, "
            "`" +
            std::string(user_table::columns::PASSWORD_HASH) + "`, "
            "`" +
            std::string(user_table::columns::ROLE) + "`, "
            "`" +
            std::string(user_table::columns::ACTIVE) + "`) "
            "VALUES (?, ?, ?, ?, ?, ?)";

    inline const std::string SELECT_USER_BY_USERNAME =
            "SELECT * FROM `" + std::string(user_table::TABLE_NAME) + "` "
            "WHERE `" +
            std::string(user_table::columns::USERNAME) + "` = ?";

    inline const std::string SELECT_USER_BY_EMAIL =
            "SELECT * FROM `" + std::string(user_table::TABLE_NAME) + "` "
            "WHERE `" +
            std::string(user_table::columns::EMAIL) + "` = ?";

    inline const std::string SELECT_ALL_USERS =
            "SELECT * FROM `" + std::string(user_table::TABLE_NAME) + "` "
            "WHERE `" +
            std::string(user_table::columns::ACTIVE) + "` = TRUE";

    inline const std::string UPDATE_USER =
            "UPDATE `" + std::string(user_table::TABLE_NAME) + "` SET "
            "`" +
            std::string(user_table::columns::NAME) + "` = ?, "
            "`" +
            std::string(user_table::columns::EMAIL) + "` = ?, "
            "`" +
            std::string(user_table::columns::PASSWORD_HASH) + "` = ?, "
            "`" +
            std::string(user_table::columns::ROLE) + "` = ?, "
            "`" +
            std::string(user_table::columns::ACTIVE) + "` = ? "
            "WHERE `" +
            std::string(user_table::columns::USERNAME) + "` = ?";

    inline const std::string UPDATE_PASSWORD =
            "UPDATE `" + std::string(user_table::TABLE_NAME) + "` SET "
            "`" +
            std::string(user_table::columns::PASSWORD_HASH) + "` = ? "
            "WHERE `" +
            std::string(user_table::columns::USERNAME) + "` = ?";

    inline const std::string UPDATE_OTP =
            "UPDATE `" + std::string(user_table::TABLE_NAME) + "` SET "
            "`" +
            std::string(user_table::columns::OTP_ID) + "` = ? "
            "WHERE `" +
            std::string(user_table::columns::USERNAME) + "` = ?";

    inline const std::string DEACTIVATE_USER =
            "UPDATE `" + std::string(user_table::TABLE_NAME) + "` SET "
            "`" +
            std::string(user_table::columns::ACTIVE) + "` = FALSE "
            "WHERE `" +
            std::string(user_table::columns::USERNAME) + "` = ?";

    inline const std::string SEARCH_USERS =
            "SELECT * FROM `" + std::string(user_table::TABLE_NAME) + "` "
            "WHERE `" +
            std::string(user_table::columns::USERNAME) + "` LIKE ? "
            "OR `" +
            std::string(user_table::columns::NAME) + "` LIKE ? "
            "OR `" +
            std::string(user_table::columns::EMAIL) + "` LIKE ? "
            "AND `" +
            std::string(user_table::columns::ACTIVE) + "` = TRUE";
}

#endif // USER_QUERIES_H
