#include <iostream>
#include <mysqlx/xdevapi.h>

using namespace std;
using namespace mysqlx;

int main() {
    try {
        Session sess("mysqlx://user:password@localhost:33060/database");

        // Get a schema
        Schema db = sess.getSchema("database");

        // Execute a query
        RowResult res = sess.sql("SELECT * FROM users LIMIT 5").execute();

        // Print results
        for (Row row : res.fetchAll()) {
            cout << "ID: " << row[0] << ", Name: " << row[1] << endl;
        }
    }
    catch (const Error &err) {
        cout << "Error: " << err.what() << endl;
        return 1;
    }

    return 0;
}
