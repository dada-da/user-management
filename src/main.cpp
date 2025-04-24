#include <iostream>
#include <mysqlx/xdevapi.h>

#include "database-config/DatabaseConfig.h"

using namespace mysqlx;

int main() {
    DatabaseConfig config;

    config.getDatabaseConfig();

    std::cout << config.getConnectionString() << std::endl;

    try {
        const std::string connStr = config.getConnectionString();
        mysqlx::Session session(connStr);

        std::cout << "Connected to MySQL server using X Protocol" << std::endl;
    } catch (const mysqlx::Error &err) {
        std::cerr << "Error connecting to database: " << err.what() << std::endl;
    } catch (std::exception &ex) {
        std::cerr << "STD exception: " << ex.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception" << std::endl;
    }

    return 0;
}
