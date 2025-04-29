#ifndef MYSQL_CONNECTION_H
#define MYSQL_CONNECTION_H

#include <mysqlx/xdevapi.h>
#include <memory>

class DBConnection
{
private:
  DBConnection();

  ~DBConnection() = default;

  DBConnection(const DBConnection &) = delete;

  DBConnection &operator=(const DBConnection &) = delete;

  DBConnection(DBConnection &&) = delete;

  DBConnection &operator=(DBConnection &&) = delete;

  std::unique_ptr<mysqlx::Session> session;

  mutable std::mutex mutex;

  std::map<std::string, std::shared_ptr<mysqlx::SqlStatement>> preparedStatements;

public:
  static DBConnection &getInstance();

  bool connect(const std::string &connectionString);

  bool disconnect();

  [[nodiscard]] bool isConnected() const;
};

#endif // MYSQL_CONNECTION_H
