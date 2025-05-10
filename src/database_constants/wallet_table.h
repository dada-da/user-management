//
// Created by Da on 6/5/25.
//

#ifndef WALLET_TABLE_H
#define WALLET_TABLE_H

namespace wallet_table {
    inline constexpr auto *TABLE_NAME = "wallets";

    namespace columns {
        inline constexpr auto *WALLET_ID = "wallet_id";
        inline constexpr auto *USERNAME = "username";
        inline constexpr auto *AMOUNT = "amount";
        inline constexpr auto *CREATED_AT = "created_at";
        inline constexpr auto *UPDATED_AT = "updated_at";
    }

    namespace constraints {
        inline constexpr int MAX_WALLET_ID_LENGTH = 16;
        inline constexpr double MIN_AMOUNT = 0.0;
        inline constexpr double MAX_AMOUNT = 1000000000.0; // 1 billion
    }
}

#endif //WALLET_TABLE_H
