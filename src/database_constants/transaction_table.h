//
// Created by Da on 6/5/25.
//

#ifndef TRANSACTION_TABLE_H
#define TRANSACTION_TABLE_H

#include <array>

namespace transaction_table {
    inline constexpr auto *TABLE_NAME = "transactions";

    namespace columns {
        inline constexpr auto *TRANSACTION_ID = "transaction_id";
        inline constexpr auto *USERNAME = "username";
        inline constexpr auto *AMOUNT = "amount";
        inline constexpr auto *CREATED_AT = "created_at";
        inline constexpr auto *RECEIVER_USERNAME = "receiver_username";
        inline constexpr auto *STATUS = "status";
        inline constexpr auto *DESCRIPTION = "description";
    }

    namespace status {
        inline constexpr auto *PENDING = "pending";
        inline constexpr auto *COMPLETED = "completed";
        inline constexpr auto *FAILED = "failed";

        inline constexpr std::array<const char *, 4> ALL = {PENDING, COMPLETED, FAILED};
    }

    namespace constraints {
        inline constexpr int MAX_TRANSACTION_ID_LENGTH = 16;
        inline constexpr int MAX_DESCRIPTION_LENGTH = 255;
        inline constexpr double MIN_AMOUNT = 0.01;
        inline constexpr double MAX_AMOUNT = 1000000.0;
    }
}

#endif //TRANSACTION_TABLE_H
