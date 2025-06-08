//
// Created by Da on 1/6/25.
//

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

#include "../utils/list/list.h"
#include "user_data.h"

namespace db_user {
    void UserData::loadFromFile() {
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

            data::User user = parseLine(line);
            users.insert(user);
        }

        file.close();
        std::cout << "Successfully read " << users.getSize() << " users from CSV" << std::endl;
    }


    void UserData::saveToFile() {
        std::ofstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("Error opening file for writing");
        }

        file <<
                "id,name,username,points,phone_number,otp_id,role,password_hash,salt,email,dob,created_at,updated_at,active\n";

        for (int i = 0; i < users.getSize(); i++) {
            const std::optional<data::User> userData = users.getDataAt(i);

            if (userData == std::nullopt || !userData.has_value()) continue;

            file << userData->getId() << ","
                    << userData->getName() << ","
                    << userData->getUsername() << ","
                    << userData->getPoints() << ","
                    << userData->getPhoneNumber() << ","
                    << userData->getOtpId() << ","
                    << userData->getRole() << ","
                    << userData->getPassword() << ","
                    << userData->getSalt() << ","
                    << (userData->isActive() ? "true" : "false") << ","
                    << userData->getEmail() << ","
                    << userData->getDob() << ","
                    << userData->getCreatedAt() << ","
                    << userData->getUpdatedAt() << ",";

            if (i < users.getSize() - 1) {
                file << "\n";
            }
        }
    }

    std::optional<data::User> UserData::findUserByUsername(const std::string &username) {
        return users.findByProperty(&data::User::getUsername, username);
    }

    void UserData::insertUser(const data::User &user) {
        //TO DO
    }

    bool UserData::updateUser(const data::User &user) {
        for (int i = 0; i < users.getSize(); i++) {
            const std::optional<data::User> currentUser = users.getDataAt(i);
            if (currentUser && currentUser->getId() == user.getId()) {
                data::User updatedUser = *currentUser;
                updatedUser.setName(user.getName());
                updatedUser.setEmail(user.getEmail());
                updatedUser.setPhoneNumber(user.getPhoneNumber());
                updatedUser.setDob(user.getDob());

                users.setDataAt(i, updatedUser);

                saveToFile();
                return true;
            }
        }
        return false;
    }

    bool UserData::deleteUser(int userId) {
        //TO DO
        return false;
    }

    std::optional<data::User> UserData::findUserById(int id) {
        //TO DO
        return std::nullopt;
    }

    const std::string UserData::filePath = "./database/users.csv";

    std::string UserData::getCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }
}
