#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#define EXAMPLE_HOST "localhost"
#define EXAMPLE_USER "root"
#define EXAMPLE_PASS "123123"
#define EXAMPLE_DB "deneme"

using namespace std;

int main(int argc, const char **argv)
{
	string url(argc >= 2 ? argv[1] : EXAMPLE_HOST);
	const string user(argc >= 3 ? argv[2] : EXAMPLE_USER);
	const string pass(argc >= 4 ? argv[3] : EXAMPLE_PASS);
	const string database(argc >= 5 ? argv[4] : EXAMPLE_DB);

	cout << endl;
	cout << "Connector/C++ standalone program example..." << endl;
	cout << endl;

	try {
		sql::Driver * driver = get_driver_instance();
		/* Using the Driver to create a connection */
		std::auto_ptr< sql::Connection > con(driver->connect(url, user, pass));
		con->setSchema(database);

		std::auto_ptr< sql::Statement > stmt(con->createStatement());
		std::auto_ptr< sql::ResultSet > res(stmt->executeQuery("SELECT name AS _message from test"));
		cout << "\t... running 'SELECT name AS _message' from test" << endl;
		while (res->next()) {
			cout << "\t... MySQL replies: " << res->getString("_message") << endl;
			cout << "\t... say it again, MySQL" << endl;
		}

	} catch (sql::SQLException &e) {
		/*
		The MySQL Connector/C++ throws three different exceptions:

		- sql::MethodNotImplementedException (derived from sql::SQLException)
		- sql::InvalidArgumentException (derived from sql::SQLException)
		- sql::SQLException (derived from std::runtime_error)
		*/
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		/* Use what() (derived from std::runtime_error) to fetch the error message */
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;

		return EXIT_FAILURE;
	}

	cout << endl;
	cout << "... find more at http://www.mysql.com" << endl;
	cout << endl;

	char c;

	cin >> c;

	return EXIT_SUCCESS;
}