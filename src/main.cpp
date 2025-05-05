#include <iostream>

#include "database-config/DatabaseConfig.h"
#include "database/DBConnection.h"

using namespace std;

int main() {
    const string &configPath = "config/database.conf";
    DatabaseConfig config;

    if (!DatabaseConfig::init(configPath)) {
        cerr << "Cannot load config!" << endl;

        return 1;
    }

    config.getConfig();

    if (!DBConnection::getInstance().connect(config.getConnectionString())) {
        cout << "Cannot connect to My SQL" << endl;
    }

    DBConnection::getInstance().init(config.getDatabaseName());

    if (!DBConnection::getInstance().init(config.getDatabaseName())) {
        cout << "Cannot init" << config.getDatabaseName() << endl;
    }

    return 0;
}
