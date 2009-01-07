#ifndef FINDIK_IMPORTER_PERSISTENCE_MYSQLDBMANAGER_HPP
#define FINDIK_IMPORTER_PERSISTENCE_MYSQLDBMANAGER_HPP

#include "dbmanager.hpp"
#include "configuration.hpp"
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <iostream>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace findik {
	namespace importer {
		namespace persistence {

			class mysqldbmanager :
				public dbmanager, public boost::enable_shared_from_this<mysqldbmanager>
			{
			public:
				mysqldbmanager(void);
				~mysqldbmanager(void);

				void connectDb();
				int newCategory(std::string category_name);
				int newDomain(std::string domain_name,int category_id);
				int newUrl(std::string url_name,int category_id);
				int newContent(std::string content_name,int category_id);

				typedef boost::shared_ptr<mysqldbmanager> pointer;

			private:
				std::auto_ptr< sql::Connection > con;
				sql::Driver * driver;
			};

		}
	}
}

#endif
