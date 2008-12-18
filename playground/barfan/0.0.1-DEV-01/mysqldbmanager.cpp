#include "mysqldbmanager.hpp"

#include <iostream>

namespace findik {
	namespace persistency {
		mysqldbmanager::mysqldbmanager() {
		}

		mysqldbmanager::~mysqldbmanager() {
			if (con.get() != NULL && !con->isClosed())
				con->close();
			this->host.clear();
			this->username.clear();
			this->password.clear();
			this->db.clear();
		}

		void mysqldbmanager::connectDb() {
			
			config::configuration_.getConfigValue_String("findik.db.host",this->host);	
			config::configuration_.getConfigValue_String("findik.db.username",this->username);
			config::configuration_.getConfigValue_String("findik.db.password",this->password);
			config::configuration_.getConfigValue_String("findik.db.db",this->db);

			try {
				this->driver = get_driver_instance();			
				std::auto_ptr< sql::Connection > con1(driver->connect(host, username, password));
				this->con = con1;
				this->con->setSchema(db);
			} catch (sql::SQLException &e) {
				std::cerr << "SQL Error: " << e.getSQLState() << std::endl;
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
				std::cout << "ERROR" << e.what() << std::endl;
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
				std::cout << "ERROR" << e.what() << std::endl;
				return false;
			}
			return true;
		}

		bool mysqldbmanager::urlRegexQuery(std::string url) {
			return true;
		}
	}
}