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
    class UserData : public IUserDatabase {
        List<User> users;
        static const std::string filePath;

        static User parseLine(const std::string &line) {
            User user = {};
            std::vector<std::string> fields;
            std::stringstream ss(line);
            std::string field;

            while (std::getline(ss, field, ',')) {
                fields.push_back(field);
            }

            if (fields.size() >= 12) {
                user.id = (fields[0] == "null" || fields[0].empty()) ? 0 : std::stoi(fields[0]);
                user.name = (fields[1] == "null") ? "" : fields[1];
                user.username = (fields[2] == "null") ? "" : fields[2];
                user.points = (fields[3] == "null" || fields[3].empty()) ? 0 : std::stoi(fields[3]);
                user.phoneNumber = fields[4];
                user.otpId = fields[5];
                user.role = (fields[6] == "null") ? "" : fields[6];
                user.passwordHash = fields[7];
                user.salt = fields[8];
                user.email = fields[9];
                user.dob = fields[10];
                user.createdAt = fields[11];
                user.updatedAt = fields[12];
                user.active = (fields.size() > 13 && fields[13] == "true");
            }

            return user;
        }

    public:
        static void initUser() {
            const User customer = {
                2, "customer", "11970201ac5917728656733e555c2f94605dc31ebac8880", "g&nK82RgUBcb9s0N", "null", "null",
                "null",
                "null", "null", "null", 100000,
                true, "null", "null"
            };
            const User admin = {
                1, "root", "6f1c4b752e621acea9a05eb451b104d23853250b93ff8d13", "g5GvcUsy@bg4Vz^S", "admin", "null",
                "null", "null",
                "null", "null", 0,
                true, "null", "null"
            };
        }

        void loadFromFile() override;

        void saveToFile() override;

        std::optional<User> findUserByUsername(const std::string &username) override;

        void insertUser(const User &user) override;

        bool updateUser(const User &user) override;

        bool deleteUser(int userId) override;

        std::optional<User> findUserById(int id) override;
    };
}

#endif //USER_DATA_H
