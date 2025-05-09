#ifndef DATABASE_CONFIG_H
#define DATABASE_CONFIG_H

#include <string>

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

  static bool init(const std::string& filePath);

  [[nodiscard]] std::string getConnectionString() const;

  [[nodiscard]] std::string getDatabaseName() const;
};

#endif // DATABASE_CONFIG_H
