//
// Created by Da on 8/6/25.
//

#ifndef WALLET_SERVICE_H
#define WALLET_SERVICE_H

#include <optional>
#include <string>
#include <cstdint>

#include "../../repository/wallet_data/interface_wallet_data.h"
#include "../../user_management/user_management.h"

#include "interface_wallet_service.h"

class WalletService final : public IWalletService {
    data::IWalletData *walletData;
    std::optional<data::Wallet> wallet;

    void initWallet() {
        if (wallet.has_value()) return;

        const auto userManager = user_mgmt::UserManagement::getInstance();

        if (!userManager->isLoggedIn()) {
            throw std::invalid_argument("❌ Not logged in");
        }

        if (userManager->isAdmin()) {
            return;
        }


        const std::string username = userManager->getUserName();

        const std::optional<data::Wallet> data = walletData->find(username);

        if (!data.has_value()) {
            throw std::invalid_argument("❌ Cannot find wallet information");
        }

        wallet = *data;
    }

public:
    explicit WalletService(
        data::IWalletData *walletData) : walletData(walletData) {
        wallet = std::nullopt;
    }

    void displayWalletDashboard() override;

    bool transfer(const std::string &receivedUsername, long long value) override;

    long long getBalance() override;

    std::string getFormattedBalance() override;
};


#endif //WALLET_SERVICE_H
