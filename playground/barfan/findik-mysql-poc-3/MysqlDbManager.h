#include "DbManager.h"

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>


class MysqlDbManager : public DbManager {
	
public:
	MysqlDbManager();
	void connectDb(std::string host, std::string db, 
		std::string username, std::string password);
	bool hostnameQuery(std::string hostname);
	bool contentQuery(std::string content);
	bool hostnameRegexQuery(std::string hostname);
	bool contentRegexQuery(std::string content);
};