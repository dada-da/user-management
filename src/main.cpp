#include <iostream>
#include <mysqlx/xdevapi.h>

#include "database-config/DatabaseConfig.h"

using namespace mysqlx;

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

  try
  {
    const std::string connStr = config.getConnectionString();
    mysqlx::Session session(connStr);

    std::cout << "Connected to MySQL server using X Protocol" << std::endl;
  }
  catch (const mysqlx::Error &err)
  {
    std::cerr << "Error connecting to database: " << err.what() << std::endl;
  }
  catch (std::exception &ex)
  {
    std::cerr << "STD exception: " << ex.what() << std::endl;
  }
  catch (...)
  {
    std::cerr << "Unknown exception" << std::endl;
  }

  return 0;
}
