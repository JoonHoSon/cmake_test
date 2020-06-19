#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include <iostream>

#include "mysql_connection.h"

using namespace std;
using namespace sql;

int main() {
    cout << "cmake test" << endl;

    try {
        Driver* driver;
        Connection* connection;
        Statement* statement;
        ResultSet* result;

        driver = get_driver_instance();
        connection = driver->connect("tcp://127.0.0.1:32758", "bokja", "1111");

        connection->setSchema("bokja");

        statement = connection->createStatement();
        result = statement->executeQuery("select count(*) as cnt from bj_member");

        int totalCount = 0;

        while (result->next()) {
            totalCount = result->getInt("cnt");
        }

        delete result;
        delete statement;
        delete connection;

        cout << "총 회원수 : " << totalCount << endl;
    } catch (SQLException& e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    return 0;
}