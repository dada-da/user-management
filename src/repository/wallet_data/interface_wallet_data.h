//
// Created by Da on 8/6/25.
//

#ifndef INTERFACE_WALLET_DATA_H
#define INTERFACE_WALLET_DATA_H

#include <string>
#include <optional>
#include <utility>

namespace data {
    class Wallet {
        int id;
        std::string username;
        double balance;

    public:
        Wallet() = default;

        Wallet(const int id, std::string username, const double balance) : id(id), username(std::move(username)),
                                                                           balance(balance) {
        }

        int getId() const {
            return id;
        }

        std::string getUsername() const {
            return username;
        }

        double getBalance() const {
            return balance;
        }

        void setUsername(const std::string &username) {
            this->username = username;
        }

        void setBalance(const double balance) {
            this->balance = balance;
        }

        void setId(const int id) {
            this->id = id;
        }
    };

    class IWalletData {
    public:
        virtual ~IWalletData() = default;

        virtual void saveToFile() = 0;

        virtual void loadFromFile() = 0;

        virtual std::optional<Wallet> find(const std::string &username) = 0;

        virtual bool update(const std::string &username, double balance) = 0;
    };
}

#endif //INTERFACE_WALLET_DATA_H
