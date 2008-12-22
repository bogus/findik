#include "mysqldbmanager.hpp"

#include <boost/scoped_ptr.hpp>
#include <iostream>

#include <cppconn/prepared_statement.h>

namespace findik {
	namespace persistency {
		mysqldbmanager::mysqldbmanager()
		{
			driver = get_driver_instance();
			pool_size_ = 10; // must take value from conf
			connectDb();
		}

		mysqldbmanager::~mysqldbmanager() {
			for (size_t i = 0; i < pool_size_; ++i)
				if (!((dbconnection<sql::Connection>::pointer)pool_[i])->connection()->isClosed())
					((dbconnection<sql::Connection>::pointer)pool_[i])->connection()->close();
			this->host.clear();
			this->username.clear();
			this->password.clear();
			this->db.clear();
		}

		mysqldbmanager::mysql_dbconnection_ptr mysqldbmanager::create_connection_object()
		{
			try {
				sql::Connection * myconn_ = driver->connect(host, username, password);
				myconn_->setSchema(db);

				mysql_dbconnection_ptr dbconnection__(
					new mysql_dbconnection(myconn_));

				dbconnection__->set_object(domain_query, 
					myconn_->prepareStatement("SELECT domain from blacklist_domain where domain=?"));

				dbconnection__->set_object(url_query, 
					myconn_->prepareStatement("SELECT url from blacklist_url where url=?"));

				return dbconnection__;
			} 
			catch (sql::SQLException &e)
			{
				LOG4CXX_ERROR(debug_logger, "SQL Error: " << e.getSQLState());
				LOG4CXX_ERROR(findik::log_initializer::user_logger,
					"Unable to connect MySQL on host: " << host << " with user: " << username);
			}
		}

		void mysqldbmanager::connectDb() {
			
			config::configuration_.getConfigValue_String("findik.db.host",this->host);	
			config::configuration_.getConfigValue_String("findik.db.username",this->username);
			config::configuration_.getConfigValue_String("findik.db.password",this->password);
			config::configuration_.getConfigValue_String("findik.db.db",this->db);

			prepare_pool();
		}

		bool mysqldbmanager::contentQuery(std::string content) {
			return true;
		}

		bool mysqldbmanager::contentRegexQuery(std::string content) {
			return true;
		}

		bool mysqldbmanager::domainQuery(std::string hostname) {
			mysql_dbconnection_ptr dbconnection_(get_dbconnection());
			sql::PreparedStatement * ps_ = (sql::PreparedStatement *) dbconnection_->get_object(domain_query);

			try {
				ps_->setString(1,hostname);
				boost::scoped_ptr< sql::ResultSet > res(ps_->executeQuery());

				dbconnection_->unlock(); 
				
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
			mysql_dbconnection_ptr dbconnection_(get_dbconnection());
			sql::PreparedStatement * ps_ = (sql::PreparedStatement *) dbconnection_->get_object(url_query);

			try {
				ps_->setString(1,url);
				boost::scoped_ptr< sql::ResultSet > res(ps_->executeQuery());

				dbconnection_->unlock();
				
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
}
