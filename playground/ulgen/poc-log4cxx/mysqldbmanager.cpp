#include "mysqldbmanager.hpp"

#include <iostream>

namespace findik {
		
		mysqldbmanager::mysqldbmanager() {
		}

		mysqldbmanager::~mysqldbmanager() {
			if (con.get() != NULL && !con->isClosed())
				con->close();
		}

		void mysqldbmanager::connectDb(std::string host, std::string db, std::string username, std::string password) {
			this->host = host;
			this->username = username;
			this->password = password;
			this->db = db;

			try {
				this->driver = get_driver_instance();			
				std::auto_ptr< sql::Connection > con1(driver->connect(host, username, password));
				this->con = con1;
				this->con->setSchema(db);
			} catch (sql::SQLException &e) {
				LOG4CXX_ERROR(debug_logger, "SQL Error: " << e.getSQLState());
				LOG4CXX_ERROR(findik::log_initializer::user_logger,
					"Unable to connect MySQL on host: " << host << " with user: " << username);
			}
		}

		bool mysqldbmanager::contentQuery(std::string content) {
			return true;
		}

		bool mysqldbmanager::contentRegexQuery(std::string content) {
			return true;
		}

		bool mysqldbmanager::domainQuery(std::string hostname) {
			try {
				std::auto_ptr< sql::Statement > stmt(this->con->createStatement());
				std::auto_ptr< sql::ResultSet > res(stmt->executeQuery("SELECT domain from blacklist_domain where domain='"+hostname+"'"));
				
				if(res->rowsCount() > 0)
					return false;

			} catch (sql::SQLException &e) {
				LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
				return false;
			}
			return true;
		}

		bool mysqldbmanager::domainRegexQuery(std::string hostname) {
			return true;
		}

		bool mysqldbmanager::urlQuery(std::string url) {
			try {
				std::auto_ptr< sql::Statement > stmt(this->con->createStatement());
				std::auto_ptr< sql::ResultSet > res(stmt->executeQuery("SELECT url from blacklist_url where url='"+url+"'"));
				
				if(res->rowsCount() > 0)
					return false;

			} catch (sql::SQLException &e) {
				LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
				return false;
			}
			return true;
		}

		bool mysqldbmanager::urlRegexQuery(std::string url) {
			return true;
		}

		log4cxx::LoggerPtr mysqldbmanager::debug_logger(log4cxx::Logger::getLogger("findik.mysqldbmanager"));
}