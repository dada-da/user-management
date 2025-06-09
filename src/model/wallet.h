//
// Created by Da on 9/6/25.
//

#ifndef WALLET_H
#define WALLET_H

#include <string>

namespace data {
    class Wallet {
        int id;
        std::string username;
        long long balance;

    public:
        Wallet() = default;

        Wallet(const int id, std::string username, const long long balance) : id(id), username(std::move(username)),
                                                                              balance(balance) {
        }

        int getId() const {
            return id;
        }

        std::string getUsername() const {
            return username;
        }

        long long getBalance() const {
            return balance;
        }

        void setUsername(const std::string &username) {
            this->username = username;
        }

        void setBalance(const long long balance) {
            this->balance = balance;
        }

        void setId(const int id) {
            this->id = id;
        }
    };
}

#endif //WALLET_H
