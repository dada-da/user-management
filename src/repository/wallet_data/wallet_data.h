//
// Created by Da on 8/6/25.
//

#ifndef WALLET_DATA_H
#define WALLET_DATA_H

#include "../../utils/list.h"
#include "../../utils/convert.h"
#include "../../model/wallet.h"
#include "interface_wallet_data.h"
#include <vector>
#include <sstream>
#include <iostream>

namespace data {
    class WalletData final : public IWalletData {
        List<Wallet> data;
        static const std::string WALLET_DATA_FILE_PATH;
        static long long lastWalletId;

        static void setLastWalletId(const long long id) {
            lastWalletId = id;
        }

        static Wallet parseLine(const std::string &line) {
            Wallet wallet = {};
            std::vector<std::string> fields;
            std::stringstream ss(line);
            std::string field;

            while (std::getline(ss, field, ',')) {
                fields.push_back(field);
            }

            if (fields.size() >= 3) {
                wallet.setId(std::stoll(fields[0]));
                wallet.setUsername((fields[1] == "null") ? "" : fields[1]);
                wallet.setBalance(std::stoll(fields[2]));
            }

            if (lastWalletId < std::stoll(fields[0])) {
                long long maxId = std::max(maxId, std::stoll(fields[0]));

                setLastWalletId(maxId);
            }

            return wallet;
        }

    public:
        static long long getNewWalletId() {
            return ++lastWalletId;
        }

        void saveToFile() override;

        void loadFromFile() override;

        std::optional<Wallet> find(const std::string &username) override;

        bool update(const std::string &username, long long balance) override;

        bool create(const std::string &username, long long balance) override;
    };
}


#endif //WALLET_DATA_H
