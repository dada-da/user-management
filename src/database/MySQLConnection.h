#ifndef MYSQL_CONNECTION_H
#define MYSQL_CONNECTION_H

#include <mysqlx/xdevapi.h>
#include <string>
#include <vector>
#include <map>
#include <memory>

class MySQLConnection {
private:
    MySQLConnection();
    ~MySQLConnection() = default;

    std::string host;
    std::string user;
    std::string password;
    std::string database;
    std::string port;

    std::unique_ptr<mysqlx::Session> session;
};



#endif //MYSQL_CONNECTION_H
