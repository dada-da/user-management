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
        int points;
        std::string phone_number;
        std::string otp_id;
        std::string role;
        std::string password_hash;
        std::string salt;
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
                user.points = (fields[3] == "null" || fields[3].empty()) ? 0 : std::stoi(fields[3]);;
                user.phone_number = fields[4];
                user.otp_id = fields[5];
                user.role = (fields[6] == "null") ? "" : fields[6];
                user.password_hash = fields[7];
                user.salt = fields[8];
                user.email = fields[9];
                user.dob = fields[10];
                user.created_at = fields[11];
                user.updated_at = fields[12];
            }

            return user;
        }

    protected:
        static const std::string filePath;

    public:
        static void initUser() {
            const User customer = {
                2, "customer", "customer", 10000, "null", "null", "null",
                "11970201ac5917728656733e555c2f94605dc31ebac8880", "g&nK82RgUBcb9s0N", "null", "null",
                "null", "null"
            };

            const User admin = {
                1, "root", "root", 0, "null", "null", "null", "6f1c4b752e621acea9a05eb451b104d23853250b93ff8d13",
                "g5GvcUsy@bg4Vz^S", "null", "null",
                "null", "null"
            };
        }

        void readUsersFromFile() {
            std::ifstream file(filePath);

            if (!file.is_open()) {
                throw std::runtime_error("Could not open file " + filePath);
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
        }

        void writeUsersToFile() {
            std::ofstream file(filePath);
            if (!file.is_open()) {
                throw std::runtime_error("Error opening file for writing");
            }

            for (int i = 0; i < users.getSize(); i++) {
                const std::optional userData = users.getDataAt(i);

                if (userData == std::nullopt || !userData.has_value()) continue;

                file << userData->id << ","
                        << userData->name << ","
                        << userData->username << ","
                        << userData->points << ","
                        << userData->phone_number << ","
                        << userData->otp_id << ","
                        << userData->role << ","
                        << userData->password_hash << ","
                        << userData->salt << ","
                        << userData->email << ","
                        << userData->dob << ","
                        << userData->created_at << ","
                        << userData->updated_at;

                if (i < users.getSize() - 1) {
                    file << "\n";
                }
            }
        }


        void insertUser(const User &user) {
            // TODO;
            users.insert(user);
        }

        User getData() {
            return *users.getDataAt(0);
        }
    };
}

#endif //USER_DATA_H
