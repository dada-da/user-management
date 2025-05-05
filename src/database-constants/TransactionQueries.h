//
// Created by Da on 6/5/25.
//

#ifndef TRANSACTIONQUERIES_H
#define TRANSACTIONQUERIES_H

#include <string>

#include "TransactionTable.h"
#include "UserTable.h"

namespace transaction_queries {
    inline const std::string CREATE_TABLE =
            "CREATE TABLE IF NOT EXISTS `" + std::string(transaction_table::TABLE_NAME) + "` ("
            "  `" + std::string(transaction_table::columns::TRANSACTION_ID) + "` VARCHAR(" + std::to_string(
                transaction_table::constraints::MAX_TRANSACTION_ID_LENGTH) + ") PRIMARY KEY,"
            "  `" + std::string(transaction_table::columns::USERNAME) + "` VARCHAR(" + std::to_string(
                user_table::constraints::MAX_USERNAME_LENGTH) + ") NOT NULL,"
            "  `" + std::string(transaction_table::columns::AMOUNT) + "` DECIMAL(18,2) NOT NULL,"
            "  `" + std::string(transaction_table::columns::CREATED_AT) +
            "` DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,"
            "  `" + std::string(transaction_table::columns::RECEIVER_USERNAME) + "` VARCHAR(" + std::to_string(
                user_table::constraints::MAX_USERNAME_LENGTH) + ") NOT NULL,"
            "  `" + std::string(transaction_table::columns::STATUS) + "` ENUM('" + transaction_table::status::PENDING
            + "', '" +
            transaction_table::status::COMPLETED + "', '" +
            transaction_table::status::FAILED + "', '" + "') NOT NULL DEFAULT '" +
            transaction_table::status::PENDING + "',"
            "  `" + std::string(transaction_table::columns::DESCRIPTION) + "` VARCHAR(" + std::to_string(
                transaction_table::constraints::MAX_DESCRIPTION_LENGTH) + "),"
            "  FOREIGN KEY (`" + std::string(transaction_table::columns::USERNAME) + "`) REFERENCES `" +
            std::string(user_table::TABLE_NAME) + "`(`" + std::string(user_table::columns::USERNAME) + "`),"
            "  FOREIGN KEY (`" + std::string(transaction_table::columns::RECEIVER_USERNAME) + "`) REFERENCES `" +
            std::string(user_table::TABLE_NAME) + "`(`" + std::string(user_table::columns::USERNAME) + "`)"
            ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4";
}

#endif //TRANSACTIONQUERIES_H
