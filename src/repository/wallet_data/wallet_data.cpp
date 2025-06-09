//
// Created by Da on 8/6/25.
//

#include <string>
#include <fstream>
#include <sstream>

#include "wallet_data.h"

namespace data {
    const std::string WalletData::WALLET_DATA_FILE_PATH = "../database/wallet.csv";
    long long WalletData::lastWalletId = 0;


    void WalletData::loadFromFile() {
        std::ifstream file(WALLET_DATA_FILE_PATH);

        if (!file.is_open()) {
            throw std::runtime_error("Could not open file " + WALLET_DATA_FILE_PATH);
        }

        std::string line;
        bool isFirstLine = true;

        while (std::getline(file, line)) {
            if (isFirstLine) {
                isFirstLine = false;
                continue;
            }

            Wallet wallet = parseLine(line);

            data.insert(wallet);
        }

        file.close();
    }

    void WalletData::saveToFile() {
        std::ofstream file(WALLET_DATA_FILE_PATH);

        if (!file.is_open()) {
            throw std::runtime_error("Error opening file for writing");
        }

        file << "id,username,balance\n";

        for (int i = 0; i < data.getSize(); i++) {
            const std::optional<Wallet> wallet = data.getDataAt(i);

            if (!wallet.has_value()) continue;

            file << wallet->getId() << ","
                    << wallet->getUsername() << ","
                    << wallet->getBalance() << "\n";
        }
    }

    std::optional<Wallet> WalletData::find(const std::string &username) {
        return data.findByProperty(&Wallet::getUsername, username);
    }

    bool WalletData::update(const std::string &username, const long long balance) {
        Wallet *wallet = data.findByPropertyPtr(&Wallet::getUsername, username);

        if (wallet == nullptr) {
            return false;
        }

        wallet->setBalance(balance);
        return true;
    }

    bool WalletData::create(const std::string &username, const long long balance) {
        auto newWallet = Wallet(getNewWalletId(), username, balance);

        std::ifstream checkFile(WALLET_DATA_FILE_PATH);
        bool fileExists = checkFile.good();
        checkFile.close();

        std::ofstream file(WALLET_DATA_FILE_PATH, std::ios::app);

        if (!file.is_open()) {
            throw std::runtime_error("Error opening file for writing");
        }

        if (!fileExists) {
            file << "id,username,balance\n";
        }

        file << newWallet.getId() << ","
                << newWallet.getUsername() << ","
                << newWallet.getBalance() << "\n";

        file.close();

        data.insert(newWallet);

        return true;
    }
}
