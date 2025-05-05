#include <iostream>
#include <map>
#include <memory>
#include <mysqlx/xdevapi.h>
#include <mutex>

#include "../database-constants/UserTable.h"
#include "../database-constants/UserQueries.h"
#include "../database-constants/WalletTable.h"
#include "../database-constants/WalletQueries.h"
#include "../database-constants/TransactionTable.h"
#include "../database-constants/TransactionQueries.h"
#include "DBConnection.h"

DBConnection::DBConnection() = default;

DBConnection &DBConnection::getInstance() {
    static DBConnection instance;
    return instance;
}

bool DBConnection::connect(const std::string &connectionString) {
    std::lock_guard lock(mutex);

    if (session) {
        disconnect();
    }

    try {
        session = std::make_unique<mysqlx::Session>(connectionString);

        preparedStatements.clear();

        return true;
    } catch (const mysqlx::Error &err) {
        std::cerr << std::format("MySQL X DevAPI error: {}", err.what()) << std::endl;
        session.reset();
        return false;
    }
    catch (const std::exception &err) {
        std::cerr << std::format("Error connecting to MySQL: {}", err.what()) << std::endl;
        session.reset();
        return false;
    }
}

bool DBConnection::disconnect() {
    std::lock_guard lock(mutex);

    preparedStatements.clear();

    if (session) {
        try {
            session->close();
            session.reset();
            return true;
        } catch (const std::exception &err) {
            std::cerr << std::format("Error disconnecting from MySQL: {}", err.what()) << std::endl;
            session.reset();
            return false;
        }
    }

    return true;
}

bool DBConnection::isConnected() const {
    std::lock_guard lock(mutex);

    if (!session) {
        return false;
    }

    try {
        session->sql("SELECT 1").execute();
        return true;
    } catch (...) {
        return false;
    }
}

bool DBConnection::init(const std::string &dbName) {
    std::lock_guard lock(mutex);

    this->dbName = dbName;

    if (!session) {
        return false;
    }
    try {
        bool dbExists = false;
        for (auto schemaList = session->getSchemas(); const auto &s: schemaList) {
            if (s.getName() == dbName) {
                dbExists = true;
                break;
            }
        }

        if (!dbExists) {
            session->createSchema(dbName);
        }

        session->sql("USE " + dbName).execute();

        try {
            if (!tableExists(user_table::TABLE_NAME)) {
                executeSQL(user_queries::CREATE_TABLE);
            }

            if (!tableExists(wallet_table::TABLE_NAME)) {
                executeSQL(wallet_queries::CREATE_TABLE);
            }

            if (!tableExists(transaction_table::TABLE_NAME)) {
                executeSQL(transaction_queries::CREATE_TABLE);
            }

            return true;
        } catch (const std::exception &e) {
            std::cerr << "Error creating tables: " << e.what() << std::endl;
            return false;
        }
    } catch (const mysqlx::Error &err) {
        std::cerr << "MySQL X DevAPI error: " << err.what() << std::endl;
        throw;
    }
}

bool DBConnection::tableExists(const std::string &tableName) const {
    try {
        mysqlx::Schema schema = session->getSchema(dbName);
        for (auto tables = schema.getTables(); const auto &table: tables) {
            if (table.getName() == tableName) {
                return true;
            }
        }
        return false;
    } catch (const mysqlx::Error &err) {
        std::cerr << "Error checking if table exists: " << err.what() << std::endl;
        return false;
    }
}

void DBConnection::executeSQL(const std::string &sqlQuery) const {
    std::lock_guard lock(mutex);

    try {
        session->sql(sqlQuery).execute();
    } catch (const mysqlx::Error &err) {
        std::cerr << "SQL execution error: " << err.what() << std::endl;
    }
}
