//
// Created by Da on 28/5/25.
//

#ifndef USER_DATA_H
#define USER_DATA_H

#include "./interface_user_data.h"
#include "../utils/list/list.h"
#include "../user/user.h"

#include <optional>
#include <iostream>
#include <vector>
#include <sstream>

namespace db_user {
    class UserData final : public IUserDatabase {
        List<data::User> users;
        static const std::string filePath;

        static int convertStringToInt(const std::string &str) {
            constexpr int DEFAULT_VALUE = 0;
            if (str.empty() || str == "null") {
                return DEFAULT_VALUE;
            }
            try {
                return std::stoi(str);
            } catch (const std::exception &e) {
                std::cerr << "Error converting '" << str << "' to integer: " << e.what() << std::endl;
                return DEFAULT_VALUE;
            }
        }

        static data::User parseLine(const std::string &line) {
            data::User user = {};
            std::vector<std::string> fields;
            std::stringstream ss(line);
            std::string field;

            while (std::getline(ss, field, ',')) {
                fields.push_back(field);
            }

            if (fields.size() >= 13) {
                user.setId(convertStringToInt(fields[0]));
                user.setName((fields[1] == "null") ? "" : fields[1]);
                user.setUsername((fields[2] == "null") ? "" : fields[2]);
                user.setPoints(convertStringToInt(fields[3]));
                user.setPhoneNumber(fields[4]);
                user.setOtpId(fields[5]);
                user.setRole((fields[6] == "null") ? "" : fields[6]);
                user.setPassword(fields[7]);
                user.setSalt(fields[8]);
                user.setActive(fields[9] == "true");
                user.setEmail(fields[10]);
                user.setDob(fields[11]);
                user.setCreatedAt(fields[12]);
                user.setUpdatedAt(fields[13]);
            }

            return user;
        }

        std::string getCurrentTimestamp();

    public:
        void loadFromFile() override;

        void saveToFile() override;

        std::optional<data::User> findUserByUsername(const std::string &username) override;

        void insertUser(const data::User &user) override;

        bool updateUser(const data::User &user) override;

        bool deleteUser(int userId) override;

        std::optional<data::User> findUserById(int id) override;
    };
}

#endif //USER_DATA_H
