#ifndef FINDIK_MYSQLDBMANAGER_HPP
#define FINDIK_MYSQLDBMANAGER_HPP

#include "pooled_dbmanager.hpp"

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <boost/enable_shared_from_this.hpp>

namespace findik {
	
	class mysqldbmanager :
		public pooled_dbmanager<sql::Connection>,
		public boost::enable_shared_from_this<mysqldbmanager>
	{
		
	public:
		mysqldbmanager();
		~mysqldbmanager();

		void connectDb(std::string host, std::string db, 
			std::string username, std::string password);
		bool domainQuery(std::string hostname);
		bool urlQuery(std::string url);
		bool contentQuery(std::string content);
		bool domainRegexQuery(std::string hostname);
		bool urlRegexQuery(std::string url);
		bool contentRegexQuery(std::string content);

	protected:
		
		sql::Driver * driver;
		
		typedef dbconnection<sql::Connection> mysql_dbconnection;

		typedef boost::shared_ptr<mysql_dbconnection> mysql_dbconnection_ptr;

		mysql_dbconnection_ptr create_connection_object();

		typedef sql::Connection * connection_ptr;

	};	
}

#endif
