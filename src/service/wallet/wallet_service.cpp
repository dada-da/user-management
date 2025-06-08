//
// Created by Da on 8/6/25.
//

#include <optional>
#include "wallet_service.h"

#include "../../repository/wallet_data/wallet_data.h"
#include "../../utils/print/print_data.h"
#include "../../utils/formatter.h"

bool WalletService::transfer(const std::string &receivedUsername, const long long value) {
    initWallet();

    const long long balance = wallet->getBalance();

    if (balance == 0 || balance < value) {
        std::cout << "⚠️ Balance is not enough. Cannot proceed." << std::endl;
        return false;
    }

    const std::optional<data::Wallet> receivedWallet = walletData->find(receivedUsername);

    if (!receivedWallet.has_value()) {
        return false;
    }

    const long long newBalance = balance - value;

    const long long newReceivedBalance = receivedWallet->getBalance() + value;


    if (!walletData->update(receivedUsername, newReceivedBalance) || !walletData->update(
            wallet->getUsername(), newBalance)) {
        return false;
    }


    walletData->saveToFile();

    wallet->setBalance(newBalance);

    return true;
}

void WalletService::displayWalletDashboard() {
    initWallet();

    PrintData::printHeader("💳 DIGITAL WALLET");

    PrintData::printSectionHeader("Account Overview");
    std::cout << "│ 👤 Account Holder: " << wallet->getUsername() << std::endl;
    std::cout << "│ 💰 Current Balance: " << "\033[32m" << wallet->getBalance() <<
            "\033[0m" <<
            std::endl;

    PrintData::printSectionHeader("Recent Transactions");
    std::cout << "│ 📝 No transactions found" << std::endl;
}

long long WalletService::getBalance() {
    initWallet();

    return wallet->getBalance();
}

std::string WalletService::getFormattedBalance() {
    initWallet();

    return Formatter::formatCurrency(wallet->getBalance());
}
