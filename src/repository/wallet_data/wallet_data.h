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

        static Wallet parseLine(const std::string &line) {
            Wallet wallet = {};
            std::vector<std::string> fields;
            std::stringstream ss(line);
            std::string field;

            while (std::getline(ss, field, ',')) {
                fields.push_back(field);
            }

            if (fields.size() >= 3) {
                wallet.setId(utils::Convert::convertStringToNumber<int>(fields[0]));
                wallet.setUsername((fields[1] == "null") ? "" : fields[1]);
                wallet.setBalance(std::stoll(fields[2]));
            }

            return wallet;
        }

    public:
        void saveToFile() override;

        void loadFromFile() override;

        std::optional<Wallet> find(const std::string &username) override;

        bool update(const std::string &username, long long balance) override;
    };
}


#endif //WALLET_DATA_H
