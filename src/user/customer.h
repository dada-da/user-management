//
// Created by Da on 21/5/25.
//

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "user.h"

#include "../role/role.h"

class Customer final : public User {
    double points;

public:
    Customer(const std::string &username,
             const std::string &name,
             const std::string &email,
             const std::string &password,
             const double &points,
             const bool active): User(username, name, email,
                                      password, UserRoles::CUSTOMER, active), points(points) {
    }

    [[nodiscard]] double getPoints() const {
        return points;
    }

    void setPoints(const double &points) {
        this->points = points;
    }
};

#endif //CUSTOMER_H
