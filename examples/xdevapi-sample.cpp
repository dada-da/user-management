#include <iostream>
#include <mysqlx/xdevapi.h>

/**
 * X DevAPI test for MySQL 9.3 with Connector C++ 9.2
 * 
 * This sample demonstrates establishing a connection to MySQL 9.3
 * using X DevAPI from Connector C++ 9.2.
 */
int main() {
    try {
        std::cout << "Connecting to MySQL 9.3 using X DevAPI..." << std::endl;
        
        // Connection parameters
        const char* host = std::getenv("MYSQL_HOST") ? std::getenv("MYSQL_HOST") : "mysql";
        int port = std::getenv("MYSQL_PORT") ? std::stoi(std::getenv("MYSQL_PORT")) : 33060;
        const char* user = std::getenv("MYSQL_USER") ? std::getenv("MYSQL_USER") : "payment_user";
        const char* pwd = std::getenv("MYSQL_PASSWORD") ? std::getenv("MYSQL_PASSWORD") : "payment_password";
        const char* db = std::getenv("MYSQL_DATABASE") ? std::getenv("MYSQL_DATABASE") : "payment_system";
        
        // Create connection session with X DevAPI
        mysqlx::Session session(
            mysqlx::SessionOption::HOST, host,
            mysqlx::SessionOption::PORT, port,
            mysqlx::SessionOption::USER, user,
            mysqlx::SessionOption::PWD, pwd,
            mysqlx::SessionOption::DB, db
        );
        
        std::cout << "Connected to MySQL server using X DevAPI!" << std::endl;
        std::cout << "MySQL version: " << session.sql("SELECT VERSION()").execute().fetchOne()[0].get<std::string>() << std::endl;
        
        // Get a schema object
        mysqlx::Schema schema = session.getSchema(db);
        
        // Create a new collection (if not exists)
        mysqlx::Collection coll = schema.createCollection("test_collection", true);
        std::cout << "Collection 'test_collection' is ready" << std::endl;
        
        // Add a document
        coll.remove("true").execute();
        coll.add(R"({"name": "John", "age": 30, "balance": 1000.50})").execute();
        std::cout << "Added a document to the collection" << std::endl;
        
        // Find the document
        mysqlx::DocResult docs = coll.find("name = 'John'").execute();
        
        // Print the results
        for (auto doc : docs) {
            std::cout << "Found document: " 
                      << "name=" << doc["name"] 
                      << ", age=" << doc["age"] 
                      << ", balance=" << doc["balance"] << std::endl;
        }
        
        // Close the session
        session.close();
        std::cout << "Connection closed successfully" << std::endl;
        
    } catch (const mysqlx::Error& err) {
        std::cerr << "MySQL X DevAPI error: " << err.what() << std::endl;
        return 1;
    } catch (const std::exception& ex) {
        std::cerr << "Standard exception: " << ex.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown exception!" << std::endl;
        return 1;
    }
    
    return 0;
}