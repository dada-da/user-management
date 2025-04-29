#include "DatabaseConfig.h"

#include <iostream>

namespace
{
  void setEnvironmentVariable(const std::string &name, const std::string &value)
  {
#ifdef _WIN32
    _putenv_s(name.c_str(), value.c_str());
#else
    setenv(name.c_str(), value.c_str(), 1);
#endif
  }
}

bool DatabaseConfig::init(const std::string &filePath)
{
  std::ifstream configFile(filePath);
  if (!configFile.is_open())
  {
    std::cerr << "Could not open config file: " << filePath << std::endl;
    return false;
  }

  std::cout << "Loading database configuration from " << filePath << std::endl;

  std::string line;
  bool success = true;

  while (std::getline(configFile, line))
  {
    if (line.empty() || line[0] == '#')
    {
      continue;
    }

    size_t equalsPos = line.find('=');
    if (equalsPos != std::string::npos)
    {
      std::string key = line.substr(0, equalsPos);
      std::string value = line.substr(equalsPos + 1);

      key.erase(0, key.find_first_not_of(" \t"));
      key.erase(key.find_last_not_of(" \t") + 1);
      value.erase(0, value.find_first_not_of(" \t"));
      value.erase(value.find_last_not_of(" \t") + 1);

      setEnvironmentVariable(key, value);
    }
  }

  const std::vector<std::string> requiredVars = {
      "DB_HOST", "DB_PORT", "DB_USER", "DB_PASSWORD", "DB_NAME"};

  for (const auto &var : requiredVars)
  {
    if (!std::getenv(var.c_str()))
    {
      std::cerr << "Required variable " << var << " not found in config file" << std::endl;
      success = false;
    }
  }

  return success;
}

void DatabaseConfig::getConfig()
{
  struct EnvVar
  {
    const char *name;
    std::string *target;
  };

  EnvVar vars[] = {
      {"DB_NAME", &this->dbName},
      {"DB_HOST", &this->host},
      {"DB_PORT", &this->port},
      {"DB_USER", &this->user},
      {"DB_PASSWORD", &this->password}};

  for (const auto &[name, target] : vars)
  {
    const char *value = std::getenv(name);

    if (value == nullptr)
    {
      std::cerr << name << " not set" << std::endl;
      return;
    }

    *target = std::string(value);
  }
}

std::string DatabaseConfig::getConnectionString() const
{
  std::stringstream connectionString;
  connectionString << "mysqlx://";

  connectionString << user << ":" << password << "@";

  connectionString << host << ":" << port;

  return connectionString.str();
}

std::string DatabaseConfig::getDatabaseName() const
{
  return this->dbName;
}
