#include <iostream>

#include "database-config/DatabaseConfig.h"
#include "database/DBConnection.h"

int main()
{
  const std::string &configPath = "config/database.conf";
  DatabaseConfig config;

  if (!config.init(configPath))
  {
    std::cerr << "Cannot load config!" << std::endl;

    return 1;
  }

  config.getConfig();

  const std::string connStr = config.getConnectionString();

  if (DBConnection::getInstance().connect(connStr))
  {
    std::cout << "Connected" << std::endl;
  }

  return 0;
}
