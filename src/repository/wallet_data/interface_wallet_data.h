//
// Created by Da on 8/6/25.
//

#ifndef INTERFACE_WALLET_DATA_H
#define INTERFACE_WALLET_DATA_H

#include <string>
#include <optional>
#include "../../model/wallet.h"

namespace data {
    class IWalletData {
    public:
        virtual ~IWalletData() = default;

        virtual void saveToFile() = 0;

        virtual void loadFromFile() = 0;

        virtual std::optional<Wallet> find(const std::string &username) = 0;

        virtual bool update(const std::string &username, long long balance) = 0;
    };
}

#endif //INTERFACE_WALLET_DATA_H
