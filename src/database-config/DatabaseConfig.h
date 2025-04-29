#ifndef DATABASECONFIG_H
#define DATABASECONFIG_H

#include <fstream>
#include <string>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <mysqlx/devapi/common.h>

struct ConnectionParams
{
  std::string host;
  std::string dbName;
  std::string user;
  std::string password;
  std::string port;
};

class DatabaseConfig : ConnectionParams
{

  std::string environment;

public:
  DatabaseConfig()
  {
    const char *env = std::getenv("APP_ENV");
    environment = (env != nullptr) ? std::string(env) : "development";
  };

  void getConfig();

  bool init(const std::string& filePath);

  [[nodiscard]] std::string getConnectionString() const;

  [[nodiscard]] std::string getDatabaseName() const;
};

#endif // DATABASECONFIG_H
