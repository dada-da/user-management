#ifndef MYSQL_CONNECTION_H
#define MYSQL_CONNECTION_H

#include <mysqlx/xdevapi.h>
#include <memory>

class DBConnection {
    DBConnection();

    ~DBConnection() = default;

    DBConnection(const DBConnection &) = delete;

    DBConnection &operator=(const DBConnection &) = delete;

    DBConnection(DBConnection &&) = delete;

    DBConnection &operator=(DBConnection &&) = delete;

    std::unique_ptr<mysqlx::Session> session;

    std::string dbName;

    mutable std::mutex mutex;

    std::map<std::string, std::shared_ptr<mysqlx::SqlStatement> > preparedStatements;

    bool tableExists(const std::string &tableName) const;

    void executeSQL(const std::string &sqlQuery) const;

public:
    static DBConnection &getInstance();

    bool connect(const std::string &connectionString);

    bool disconnect();

    [[nodiscard]] bool isConnected() const;

    [[nodiscard]] bool init(const std::string &dbName);
};

#endif // MYSQL_CONNECTION_H
