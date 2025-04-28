#ifndef DATABASECONFIG_H
#define DATABASECONFIG_H

#include <fstream>
#include <mysqlx/devapi/common.h>

class DatabaseConfig {
    std::string environment;
    std::string host;
    std::string dbName;
    std::string user;
    std::string password;
    std::string port;

public:
    DatabaseConfig() {
        const char *env = std::getenv("APP_ENV");
        environment = (env != nullptr) ? std::string(env) : "development";
    };

    void getDatabaseConfig();

    [[nodiscard]] std::string getConnectionString() const;

        [[nodiscard]] std::string getDatabaseName() const;
};


#endif //DATABASECONFIG_H
