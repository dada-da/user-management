#include <iostream>
#include <string_view>
#include <vector>
#include <map>
#include <memory>
#include <optional>
#include <functional>
#include <concepts>
#include <mysqlx/xdevapi.h>
#include <mutex>
#include "DBConnection.h"

DBConnection::DBConnection()
{
  // Default constructor
}

DBConnection &DBConnection::getInstance()
{
  static DBConnection instance;
  return instance;
}

bool DBConnection::connect(const std::string &connectionString)
{
  std::lock_guard<std::mutex> lock(mutex);

  if (session)
  {
    disconnect();
  }

  try
  {

    session = std::make_unique<mysqlx::Session>(connectionString);

    preparedStatements.clear();

    return true;
  }
  catch (const mysqlx::Error &err)
  {
    std::cerr << std::format("MySQL X DevAPI error: {}", err.what()) << std::endl;
    session.reset();
    return false;
  }
  catch (const std::exception &err)
  {
    std::cerr << std::format("Error connecting to MySQL: {}", err.what()) << std::endl;
    session.reset();
    return false;
  }
}

bool DBConnection::disconnect()
{
  std::lock_guard<std::mutex> lock(mutex);

  // Clear prepared statements
  preparedStatements.clear();

  if (session)
  {
    try
    {
      session->close();
      session.reset();
      return true;
    }
    catch (const std::exception &err)
    {
      std::cerr << std::format("Error disconnecting from MySQL: {}", err.what()) << std::endl;
      session.reset();
      return false;
    }
  }

  return true;
}

bool DBConnection::isConnected() const
{
  std::lock_guard<std::mutex> lock(mutex);

  if (!session)
  {
    return false;
  }

  try
  {
    session->sql("SELECT 1").execute();
    return true;
  }
  catch (...)
  {
    return false;
  }
}