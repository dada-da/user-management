#ifndef MYSQL_CONNECTION_H
#define MYSQL_CONNECTION_H

#include <mysqlx/xdevapi.h>
#include <memory>

class MySQLConnection {
private:
    MySQLConnection();
    ~MySQLConnection() = default;

    std::unique_ptr<mysqlx::Session> session;
};



#endif //MYSQL_CONNECTION_H
