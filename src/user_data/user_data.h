//
// Created by Da on 28/5/25.
//

#ifndef USER_DATA_H
#define USER_DATA_H

#include <optional>
#include <vector>
#include <sstream>

#include "./interface_user_data.h"
#include "../utils/list/list.h"
#include "../user/user.h"

namespace db_user {
    class UserData final : public IUserDatabase {
        List<data::User> users;
        static const std::string filePath;

        static data::User parseLine(const std::string &line) {
            data::User user = {};
            std::vector<std::string> fields;
            std::stringstream ss(line);
            std::string field;

            while (std::getline(ss, field, ',')) {
                fields.push_back(field);
            }

            if (fields.size() >= 12) {
                user.setId((fields[0] == "null" || fields[0].empty()) ? 0 : std::stoi(fields[0]));
                user.setName((fields[1] == "null") ? "" : fields[1]);
                user.setUsername((fields[2] == "null") ? "" : fields[2]);
                user.setPoints((fields[3] == "null" || fields[3].empty()) ? 0 : std::stoi(fields[3]));
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
                user.setUpdatedAt(fields[14]);
            }

            return user;
        }

    public:
        static void initUser() {
            const data::User customer = {
                2, "customer", "11970201ac5917728656733e555c2f94605dc31ebac8880", "g&nK82RgUBcb9s0N", "null", "null",
                "null",
                "null", "null", "null", 100000,
                true, "null", "null"
            };
            const data::User admin = {
                1, "root", "6f1c4b752e621acea9a05eb451b104d23853250b93ff8d13", "g5GvcUsy@bg4Vz^S", "admin", "null",
                "null", "null",
                "null", "null", 0,
                true, "null", "null"
            };
        }

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
