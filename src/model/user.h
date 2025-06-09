#ifndef USER_H
#define USER_H

#include "../utils/role/role.h"
#include <string>

namespace data {
    class User {
    protected:
        int id;
        std::string username;
        std::string passwordHash;
        std::string salt;
        std::string role;
        std::string otpId;
        std::string name;
        std::string phoneNumber;
        std::string email;
        std::string dob;
        bool active;
        std::string updatedAt;
        std::string createdAt;

        template<typename T>
        friend class List;

    public:
        User() = default;

        User(
            const int &id,
            const std::string &username,
            const std::string &password,
            const std::string &salt,
            const std::string &role,
            const std::string &otpId,
            const std::string &name,
            const std::string &phoneNumber,
            const std::string &email,
            const std::string &dob,
            const bool active,
            const std::string &updatedAt,
            const std::string &createdAt
        )
            : id(id), username(username), passwordHash(password), salt(salt), role(role), otpId(otpId),
              name(name), phoneNumber(phoneNumber), email(email), dob(dob), active(active),
              createdAt(createdAt), updatedAt(updatedAt) {
        }

        void setRole(const std::string &role) {
            this->role = role;
        }

        void setActive(const bool active) {
            this->active = active;
        }

        void setName(const std::string &name) {
            this->name = name;
        }

        void setEmail(const std::string &email) {
            this->email = email;
        }

        void setPassword(const std::string &password) {
            this->passwordHash = password;
        }

        void setId(const int id) {
            this->id = id;
        }

        void setUsername(const std::string &username) {
            this->username = username;
        }

        void setSalt(const std::string &salt) {
            this->salt = salt;
        }

        void setOtpId(const std::string &otpId) {
            this->otpId = otpId;
        }

        void setPhoneNumber(const std::string &phoneNumber) {
            this->phoneNumber = phoneNumber;
        }

        void setDob(const std::string &dob) {
            this->dob = dob;
        }

        void setUpdatedAt(const std::string &updatedAt) {
            this->updatedAt = updatedAt;
        }

        void setCreatedAt(const std::string &createdAt) {
            this->createdAt = createdAt;
        }

        void setUser(const User &user) {
            id = user.id;
            username = user.username;
            passwordHash = user.passwordHash;
            salt = user.salt;
            role = user.role;
            otpId = user.otpId;
            name = user.name;
            phoneNumber = user.phoneNumber;
            email = user.email;
            dob = user.dob;
            active = user.active;
            updatedAt = user.updatedAt;
            createdAt = user.createdAt;
        }

        std::string getUsername() const {
            return username;
        }

        std::string getName() const {
            return name;
        }

        std::string getEmail() const {
            return email;
        }

        std::string getPassword() const {
            return passwordHash;
        }

        std::string getSalt() const {
            return salt;
        }

        std::string getRole() const {
            return role;
        }

        int getId() const {
            return id;
        }

        std::string getOtpId() const {
            return otpId;
        }

        std::string getPhoneNumber() const {
            return phoneNumber;
        }

        std::string getDob() const {
            return dob;
        }


        std::string getUpdatedAt() const {
            return updatedAt;
        }

        std::string getCreatedAt() const {
            return createdAt;
        }

        bool isAdmin() const {
            return this->role == UserRoles::ADMIN;
        }

        bool isActive() const {
            return active;
        }
    };
}

#endif // USER_H
