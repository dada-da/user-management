#include "DatabaseConfig.h"

#include <iostream>

void DatabaseConfig::getDatabaseConfig() {
    struct EnvVar {
        const char *name;
        std::string *target;
    };

    EnvVar vars[] = {
        {"DB_NAME", &this->dbName},
        {"DB_HOST", &this->host},
        {"DB_PORT", &this->port},
        {"DB_USER", &this->user},
        {"DB_PASSWORD", &this->password}
    };

    for (const auto &[name, target]: vars) {
        const char *value = std::getenv(name);

        if (value == nullptr) {
            std::cerr << name << " not set" << std::endl;
            return;
        }

        *target = std::string(value);
    }
}

std::string DatabaseConfig::getConnectionString() const {
    std::stringstream connectionString;
    connectionString << "mysqlx://";

    connectionString << user << ":" << password << "@";

    connectionString << host << ":" << port;

    return connectionString.str();
}

std::string DatabaseConfig::getDatabaseName() const {
    return this->dbName;
}
