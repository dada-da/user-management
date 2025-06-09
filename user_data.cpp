#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <vector>
#include <algorithm>

#include "../../utils/list.h"
#include "../../utils/date_time.h"
#include "user_data.h"

namespace db_user {
    const std::string UserData::filePath = "./database/users.csv";
    int UserData::lastId = 0;

    int UserData::getNewId() {
        return ++lastId;
    }

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

        const data::User lastUser = users.getDataAt(users.getSize() - 1).value();

        setLastId(lastUser.getId());

        file.close();
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

    void UserData::create(const data::User &user) {
        data::User newUser = user;

        newUser.setId(getNewId());

        const std::string currentTime = utils::DateTime::getCurrentTimestamp();
        newUser.setCreatedAt(currentTime);
        newUser.setUpdatedAt(currentTime);

        users.insert(newUser);

        saveToFile();
    }

    bool UserData::update(const data::User &user) {
        for (int i = 0; i < users.getSize(); i++) {
            const std::optional<data::User> currentUser = users.getDataAt(i);
            const std::string currentTime = utils::DateTime::getCurrentTimestamp();

            if (currentUser && currentUser->getId() == user.getId()) {
                data::User updatedUser = *currentUser;
                updatedUser.setName(user.getName());
                updatedUser.setEmail(user.getEmail());
                updatedUser.setPhoneNumber(user.getPhoneNumber());
                updatedUser.setDob(user.getDob());
                updatedUser.setPassword(user.getPassword());
                updatedUser.setSalt(user.getSalt());
                updatedUser.setUpdatedAt(currentTime);

                users.setDataAt(i, updatedUser);

                saveToFile();
                return true;
            }
        }
        return false;
    }

    bool UserData::deleteUser(std::string username) {
        //TO DO
        return false;
    }

    std::optional<data::User> UserData::findUserById(int id) {
        //TO DO
        return std::nullopt;
    }

    std::vector<data::User> UserData::search(const std::string &keyword) {
        std::vector<data::User> results;
        for (int i = 0; i < users.getSize(); ++i) {
            auto userOpt = users.getDataAt(i);
            if (userOpt.has_value()) {
                const auto &user = userOpt.value();
                // Tìm theo username hoặc email (không phân biệt hoa thường)
                std::string uname = user.getUsername();
                std::string email = user.getEmail();
                std::string key = keyword;
                std::transform(uname.begin(), uname.end(), uname.begin(), ::tolower);
                std::transform(email.begin(), email.end(), email.begin(), ::tolower);
                std::transform(key.begin(), key.end(), key.begin(), ::tolower);
                if (uname.find(key) != std::string::npos || email.find(key) != std::string::npos) {
                    results.push_back(user);
                }
            }
        }
        return results;
    }
}
