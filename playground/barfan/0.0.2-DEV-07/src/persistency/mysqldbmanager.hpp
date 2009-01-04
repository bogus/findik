/*
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef FINDIK_MYSQLDBMANAGER_HPP
#define FINDIK_MYSQLDBMANAGER_HPP

#include "pooled_dbmanager.hpp"
#include "configuration.hpp"
#include "log_initializer.hpp"
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <boost/enable_shared_from_this.hpp>

namespace findik {
	namespace persistency {
		class mysqldbmanager :
			public pooled_dbmanager<sql::Connection>,
			public boost::enable_shared_from_this<mysqldbmanager>
		{

		public:
			mysqldbmanager();
			~mysqldbmanager();

			void connectDb();
			bool domainQuery(std::string hostname);
			bool urlQuery(std::string url);
			bool pcreQuery(std::map<int,std::string> &pcre_map);

		protected:

			sql::Driver * driver;

			typedef dbconnection<sql::Connection> mysql_dbconnection;

			typedef boost::shared_ptr<mysql_dbconnection> mysql_dbconnection_ptr;

			mysql_dbconnection_ptr create_connection_object();

			typedef sql::Connection * connection_ptr;

			enum prepared_statement_types {
				domain_query = 100,
				url_query = 101
			};

			static log4cxx::LoggerPtr debug_logger;
		};
	}
}

#endif
