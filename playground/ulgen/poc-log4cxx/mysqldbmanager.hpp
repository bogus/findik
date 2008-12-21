#ifndef FINDIK_MYSQLDBMANAGER_HPP
#define FINDIK_MYSQLDBMANAGER_HPP

#include "dbmanager.hpp"
#include "log_initializer.hpp"
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <boost/enable_shared_from_this.hpp>

namespace findik {
	
		class mysqldbmanager : 
			public dbmanager,
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

		private:
			std::auto_ptr< sql::Connection > con;
			sql::Driver * driver;
			static log4cxx::LoggerPtr debug_logger;
		};	
}

#endif
