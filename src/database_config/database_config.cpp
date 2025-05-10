#include <iostream>
#include <fstream>
#include <string>
#include <mysqlx/devapi/common.h>

#include "database_config.h"

using namespace std;

namespace
{
  void setEnvironmentVariable(const string &name, const string &value)
  {
#ifdef _WIN32
    _putenv_s(name.c_str(), value.c_str());
#else
    setenv(name.c_str(), value.c_str(), 1);
#endif
  }
}

bool DatabaseConfig::init(const string &filePath)
{
  ifstream configFile(filePath);
  if (!configFile.is_open())
  {
    cerr << "Could not open config file: " << filePath << endl;
    return false;
  }

  string line;
  bool success = true;

  while (getline(configFile, line))
  {
    if (line.empty() || line[0] == '#')
    {
      continue;
    }

    size_t equalsPos = line.find('=');
    if (equalsPos != string::npos)
    {
      string key = line.substr(0, equalsPos);
      string value = line.substr(equalsPos + 1);

      key.erase(0, key.find_first_not_of(" \t"));
      key.erase(key.find_last_not_of(" \t") + 1);
      value.erase(0, value.find_first_not_of(" \t"));
      value.erase(value.find_last_not_of(" \t") + 1);

      setEnvironmentVariable(key, value);
    }
  }

  const vector<string> requiredVars = {
      "DB_HOST", "DB_PORT", "DB_USER", "DB_PASSWORD", "DB_NAME"};

  for (const auto &var : requiredVars)
  {
    if (!getenv(var.c_str()))
    {
      cerr << "Required variable " << var << " not found in config file" << endl;
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
    string *target;
  };

  EnvVar vars[] = {
      {"DB_NAME", &this->dbName},
      {"DB_HOST", &this->host},
      {"DB_PORT", &this->port},
      {"DB_USER", &this->user},
      {"DB_PASSWORD", &this->password}};

  for (const auto &[name, target] : vars)
  {
    const char *value = getenv(name);

    if (value == nullptr)
    {
      cerr << name << " not set" << endl;
      return;
    }

    *target = string(value);
  }
}

string DatabaseConfig::getConnectionString() const
{
  stringstream connectionString;
  connectionString << "mysqlx://";

  connectionString << user << ":" << password << "@";

  connectionString << host << ":" << port;

  return connectionString.str();
}

string DatabaseConfig::getDatabaseName() const
{
  return this->dbName;
}
