#include "mysqldbmanager.hpp"

namespace findik {
	namespace importer {
		namespace persistence {

			mysqldbmanager::mysqldbmanager(void)
			{
			}

			mysqldbmanager::~mysqldbmanager(void)
			{
				if (con.get() != NULL && !con->isClosed())
					con->close();
				this->host.clear();
				this->username.clear();
				this->password.clear();
				this->db.clear();
			}

			void mysqldbmanager::connectDb()
			{
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
			
			/**
			* First checks whether category name is inserted. If inserted returns category_id
			* Then inserts category and returns newly added category name
			*/
			int mysqldbmanager::newCategory(std::string category_name)
			{
				std::stringstream sql;
				bool ok;
				try {
					std::auto_ptr< sql::Statement > stmt(con->createStatement());
					sql.str("");
					sql << "Select * from category where catname = '";
					sql << category_name << "';";
					ok = stmt->execute(sql.str());
					if(ok) 
					{
						std::auto_ptr< sql::ResultSet > res(stmt->getResultSet());
						if(res->rowsCount() > 0) {
							res->next();
							return res->getInt("id");
						}
					}

					sql.str("");
					sql << "INSERT INTO category VALUES (NULL,'";
					sql << category_name << "');";
					stmt->execute(sql.str());
					sql.str("");
					sql << "Select * from category where catname = '";
					sql << category_name << "';";
					ok = stmt->execute(sql.str());
					if(ok) 
					{
						std::auto_ptr< sql::ResultSet > res(stmt->getResultSet());
						if(res->rowsCount() > 0) {
							res->next();
							return res->getInt("id");
						}
					}
				} catch (sql::SQLException &e) {
					std::cout << "SQL Error :" << e.getErrorCode() << std::endl;
				}
				return 0;
			}
			
			/**
			* First checks whether domain name is inserted. If inserted returns 0
			* Then inserts domain name and returns 0 if process true
			* returns 1 if exception occurs
			*/
			int mysqldbmanager::newDomain(std::string domain_name,int category_id)
			{
				std::stringstream sql;
				bool ok;
				try {
					std::auto_ptr< sql::Statement > stmt(con->createStatement());
					sql.str("");
					sql << "Select * from blacklist_domain where domain = '";
					sql << domain_name << "';";
					std::cout << sql.str() << std::endl;
					ok = stmt->execute(sql.str());
					if(ok) 
					{
						std::auto_ptr< sql::ResultSet > res(stmt->getResultSet());
						if(res->rowsCount() > 0) {
							return 0;
						}
					}

					sql.str("");
					sql << "INSERT INTO blacklist_domain VALUES (NULL,'";
					sql << domain_name << "','1','"<< category_id <<"');";
					std::cout << sql.str() << std::endl;
					stmt->execute(sql.str());

					sql.str("");
					sql << "Select * from blacklist_domain where domain = '";
					sql << domain_name << "';";
					std::cout << sql.str() << std::endl;
					ok = stmt->execute(sql.str());
					if(ok) 
					{
						std::auto_ptr< sql::ResultSet > res(stmt->getResultSet());
						if(res->rowsCount() > 0) {
							return 0;
						}
					}
				} catch (sql::SQLException &e) {
					std::cout << "SQL Error :" << e.getErrorCode() << std::endl;
				}
				return 1;
			}
			
			/**
			* First checks whether url name is inserted. If inserted returns 0
			* Then inserts url name and returns 0 if process true
			*/
			int mysqldbmanager::newUrl(std::string url_name,int category_id)
			{
				std::stringstream sql;
				bool ok;
				try {
					std::auto_ptr< sql::Statement > stmt(con->createStatement());
					sql.str("");
					sql << "Select * from blacklist_url where url = '";
					sql << url_name << "';";
					std::cout << sql.str() << std::endl;
					ok = stmt->execute(sql.str());
					if(ok) 
					{
						std::auto_ptr< sql::ResultSet > res(stmt->getResultSet());
						if(res->rowsCount() > 0) {
							return 0;
						}
					}

					sql.str("");
					sql << "INSERT INTO blacklist_url VALUES (NULL,'";
					sql << url_name << "','1','"<< category_id <<"');";
					std::cout << sql.str() << std::endl;
					stmt->execute(sql.str());

					sql.str("");
					sql << "Select * from blacklist_url where url = '";
					sql << url_name << "';";
					std::cout << sql.str() << std::endl;
					ok = stmt->execute(sql.str());
					if(ok) 
					{
						std::auto_ptr< sql::ResultSet > res(stmt->getResultSet());
						if(res->rowsCount() > 0) {
							return 0;
						}
					}
				} catch (sql::SQLException &e) {
					std::cout << "SQL Error :" << e.getErrorCode() << std::endl;
				}
				return 1;
			}

			int mysqldbmanager::newContent(std::string content_name,int category_id)
                        {
                                std::stringstream sql;
                                bool ok;
                                try {
                                        std::auto_ptr< sql::Statement > stmt(con->createStatement());
                                        sql.str("");
                                        sql << "Select * from blacklist_content where content = '";
                                        sql << content_name << "';";
                                        std::cout << sql.str() << std::endl;
                                        ok = stmt->execute(sql.str());
                                        if(ok) 
                                        {
                                                std::auto_ptr< sql::ResultSet > res(stmt->getResultSet());
                                                if(res->rowsCount() > 0) {
                                                        return 0;
                                                }
                                        }

                                        sql.str("");
                                        sql << "INSERT INTO blacklist_content VALUES (NULL,'";
                                        sql << content_name << "','1','"<< category_id <<"');";
                                        std::cout << sql.str() << std::endl;
                                        stmt->execute(sql.str());

                                        sql.str("");
                                        sql << "Select * from blacklist_content where content = '";
                                        sql << content_name << "';";
                                        std::cout << sql.str() << std::endl;
                                        ok = stmt->execute(sql.str());
                                        if(ok) 
                                        {
                                                std::auto_ptr< sql::ResultSet > res(stmt->getResultSet());
                                                if(res->rowsCount() > 0) {
                                                        return 0;
                                                }
                                        }
                                } catch (sql::SQLException &e) {
                                        std::cout << "SQL Error :" << e.getErrorCode() << std::endl;
                                }
                                return 1;
                        }
		}
	}
}
