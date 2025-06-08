//
// Created by Da on 8/6/25.
//

#ifndef WALLET_DATA_H
#define WALLET_DATA_H

#include "../../utils/list.h"
#include "interface_wallet_data.h"
#include <vector>
#include <sstream>
#include <iostream>

namespace data {
    class WalletData final : public IWalletData {
        List<Wallet> data;
        static const std::string WALLET_DATA_FILE_PATH;

        template<typename T>
        static T convertStringToNumber(const std::string &str, T defaultValue = T{}) {
            if (str.empty() || str == "null") {
                return defaultValue;
            }

            try {
                if constexpr (std::is_same_v<T, int>) {
                    return std::stoi(str);
                } else if constexpr (std::is_same_v<T, double>) {
                    return std::stod(str);
                } else if constexpr (std::is_same_v<T, float>) {
                    return std::stof(str);
                }
            } catch (const std::exception &e) {
                std::cerr << "Error converting '" << str << "': " << e.what() << std::endl;
                return defaultValue;
            }

            return defaultValue;
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
                wallet.setId(convertStringToNumber<int>(fields[0]));
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
