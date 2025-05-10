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
    std::string password;
    std::string email;
    Role role;
    
public:
    User(const std::string& user, const std::string& pass, const std::string& mail, Role r)
        : username(user), password(pass), email(mail), role(r) {}
    
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    std::string getEmail() const { return email; }
    Role getRole() const { return role; }
    
    void setRole(Role r) { role = r; }
};

#endif // USER_H