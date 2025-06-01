//
// Created by Da on 28/5/25.
//

#ifndef USER_DATA_H
#define USER_DATA_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "../utils/list/list.h"

namespace db_user {
    struct User {
        int id;
        std::string name;
        std::string username;
        std::string points;
        std::string phone_number;
        std::string otp_id;
        std::string role;
        std::string password_hash;
        std::string email;
        std::string dob;
        std::string created_at;
        std::string updated_at;
    };

    class UserData {
        List<User> users = List<User>();

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
                user.points = fields[3];
                user.phone_number = fields[4];
                user.otp_id = fields[5];
                user.role = (fields[6] == "null") ? "" : fields[6];
                user.password_hash = fields[7];
                user.email = fields[8];
                user.dob = fields[9];
                user.created_at = fields[10];
                user.updated_at = fields[11];
            }

            return user;
        }

    public:
        void readUsersFromFile(const std::string &filename) {
            std::ifstream file(filename);

            if (!file.is_open()) {
                throw std::runtime_error("Could not open file " + filename);
            }

            std::string line;
            bool isFirstLine = true;

            while (std::getline(file, line)) {
                if (isFirstLine) {
                    isFirstLine = false;
                    continue;
                }

                User user = parseLine(line);
                users.insert(user);
            }

            file.close();
            std::cout << "Successfully read " << users.getSize() << " users from CSV" << std::endl;
        };

        List<User> getData() {
            return users;
        };
    };
}

#endif //USER_DATA_H
