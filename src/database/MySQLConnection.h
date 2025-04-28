#ifndef MYSQL_CONNECTION_H
#define MYSQL_CONNECTION_H

#include <mysqlx/xdevapi.h>
#include <memory>

class MySQLConnection {
private:
    MySQLConnection();

    ~MySQLConnection() = default;

    MySQLConnection(const MySQLConnection &) = delete;

    MySQLConnection &operator=(const MySQLConnection &) = delete;

    MySQLConnection(MySQLConnection &&) = delete;

    MySQLConnection &operator=(MySQLConnection &&) = delete;

    std::string connectionString;
    std::unique_ptr<mysqlx::Session> session;
    mutable std::mutex mutex;

    std::map<std::string, std::shared_ptr<mysqlx::SqlStatement> > preparedStatements;

    // Initialize connection details
    void setConnectionDetails(std::string_view host, uint16_t port,
                              std::string_view user, std::string_view password,
                              std::string_view schema);
};


#endif //MYSQL_CONNECTION_H
