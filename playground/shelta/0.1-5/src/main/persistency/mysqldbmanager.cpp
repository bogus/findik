/*
  Copyright (C) 2008 H. Kerem Cevahir (shelta) <findikmail@gmail.com>

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

#include "mysqldbmanager.hpp"
#include "service_container.hpp"

#include <boost/scoped_ptr.hpp>
#include <cppconn/prepared_statement.h>

namespace findik 
{
	namespace persistency 
	{
		log4cxx::LoggerPtr mysqldbmanager::debug_logger(log4cxx::Logger::getLogger("findik.persistency.mysqldbmanager"));

		mysqldbmanager::mysqldbmanager() :
			is_connected(false)
		{}

		void mysqldbmanager::connect()
		{
			if (is_connected)
				return;
			is_connected = false;

			driver = get_driver_instance();

			host = FI_CONFIG.db_mysql_host();
			username = FI_CONFIG.db_mysql_username();
			password = FI_CONFIG.db_mysql_password();
			db = FI_CONFIG.db_mysql_database();
			pool_size_ = FI_CONFIG.db_pool_size();

			prepare_pool();
		}

		mysqldbmanager::~mysqldbmanager() 
		{
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

				dbconnection__->set_object(pcre_query,
					myconn_->prepareStatement("SELECT content,catid from blacklist_content"));
				
				return dbconnection__;
			}
			catch (sql::SQLException &e)
			{
				LOG4CXX_ERROR(debug_logger, "SQL Error: " << e.getSQLState());
				LOG4CXX_ERROR(logging::log_initializer::user_logger,
					"Unable to connect MySQL on host: " << host << " with user: " << username);
			}
		}

		bool mysqldbmanager::domainQuery(std::string hostname) 
		{
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

		bool mysqldbmanager::pcreQuery(std::map<int,std::string> &pcre_map) 
		{

			mysql_dbconnection_ptr dbconnection_(get_dbconnection());
                        sql::PreparedStatement * ps_ = (sql::PreparedStatement *) dbconnection_->get_object(pcre_query);

                        try {
                                boost::scoped_ptr< sql::ResultSet > res(ps_->executeQuery());

                                dbconnection_->unlock();

				while (res->next())
                                {
                                          pcre_map.insert(std::pair<int,std::string>(res->getInt("catid"),res->getString("content")));
                                }

                        } catch (sql::SQLException &e) {
                                LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
                                return false;
                        }
	
                        return true;
                }
	}
}
