#include <iostream>

#include "database_config/database_config.h"
#include "database/db_connection.h"
#include "menu_system/menu_system.h"
#include "user/user_management.h"

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
        return 1;
    }

    if (!DBConnection::getInstance().init(config.getDatabaseName())) {
        cout << "Cannot init" << config.getDatabaseName() << endl;
        return 1;
    }

    UserManagement userMgmt;
    MenuSystem::run(&userMgmt);

    return 0;
}
