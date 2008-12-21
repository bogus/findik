#include "mysqldbmanager.hpp"

#include <boost/scoped_ptr.hpp>
#include <iostream>

#include <cppconn/prepared_statement.h>

namespace findik {
		
		mysqldbmanager::mysqldbmanager()
		{
			driver = get_driver_instance();
			pool_size_ = 10; // must take value from conf
			connectDb("localhost","findik","root",""); //must take from conf
		}

		mysqldbmanager::~mysqldbmanager() {
			for (size_t i = 0; i < pool_size_; ++i)
				if (!((dbconnection<sql::Connection>::pointer)pool_[i])->connection()->isClosed())
					((dbconnection<sql::Connection>::pointer)pool_[i])->connection()->close();
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
				std::cerr << "SQL Error: " << e.getSQLState() << std::endl;
			}
		}

		void mysqldbmanager::connectDb(std::string host, std::string db, std::string username, std::string password) {
			this->host = host;
			this->username = username;
			this->password = password;
			this->db = db;

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
				std::cout << "ERROR" << e.what() << std::endl;
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
				std::cout << "ERROR" << e.what() << std::endl;
				return false;
			}
			return true;
		}

		bool mysqldbmanager::urlRegexQuery(std::string url) {
			return true;
		}
}