#ifndef USER_H
#define USER_H

#include <string>
#include "../role/role.h"

namespace db_user {
    class IUserDatabase;
    class UserData;
}

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
    int points;
    bool active;
    std::string updatedAt;
    std::string createdAt;

    friend class db_user::IUserDatabase;
    friend class db_user::UserData;
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
        const int points,
        const bool active,
        const std::string &updatedAt,
        const std::string &createdAt
    )
        : id(id), username(username), passwordHash(password), salt(salt), role(role), otpId(otpId),
          name(name), phoneNumber(phoneNumber), email(email), dob(dob), points(points), active(active),
          createdAt(createdAt), updatedAt(updatedAt) {
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

    bool isActive() const {
        return active;
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

    bool isAdmin() const {
        return this->role == UserRoles::ADMIN;
    }
};

#endif // USER_H
