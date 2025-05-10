#ifndef WALLET_QUERIES_H
#define WALLET_QUERIES_H

#include <string>

#include "wallet_table.h"
#include "user_table.h"

namespace wallet_queries {
    inline const std::string CREATE_TABLE =
            "CREATE TABLE IF NOT EXISTS `" + std::string(wallet_table::TABLE_NAME) + "` ("
            "  `" + std::string(wallet_table::columns::WALLET_ID) + "` VARCHAR(" + std::to_string(
                wallet_table::constraints::MAX_WALLET_ID_LENGTH) + ") PRIMARY KEY,"
            "  `" + std::string(wallet_table::columns::USERNAME) + "` VARCHAR(" + std::to_string(
                user_table::constraints::MAX_USERNAME_LENGTH) + ") NOT NULL UNIQUE,"
            "  `" + std::string(wallet_table::columns::AMOUNT) + "` DECIMAL(18,2) NOT NULL DEFAULT 0.00,"
            "  `" + std::string(wallet_table::columns::CREATED_AT) + "` TIMESTAMP DEFAULT CURRENT_TIMESTAMP,"
            "  `" + std::string(wallet_table::columns::UPDATED_AT) +
            "` TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,"
            "  FOREIGN KEY (`" + std::string(wallet_table::columns::USERNAME) + "`) REFERENCES `" +
            std::string(user_table::TABLE_NAME) + "`(`" + std::string(user_table::columns::USERNAME) + "`)"
            ") ENGINE=InnoDB DEFAULT CHARSET=utf8mb4";
}

#endif //WALLET_QUERIES_H
