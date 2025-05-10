#ifndef USER_H
#define USER_H

#include <string>

enum class Role {
    NONE,
    USER,
    ADMIN
};

class User {
    std::string username;
    std::string name;
    std::string email;
    std::string password;
    std::string role;
    bool active;

public:
    User(const std::string &username,
         const std::string &name,
         const std::string &email,
         const std::string &password,
         const std::string &role,
         bool active)
        : username(username), name(name), email(email),
          password(password), role(role), active(active) {
    }

    std::string getUsername() const { return username; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }
    std::string getPassword() const { return password; }
    std::string getRole() const { return role; }
    bool isActive() const { return active; }

    void setRole(const std::string &r) { role = r; }
    void setActive(bool a) { active = a; }
};

#endif // USER_H
