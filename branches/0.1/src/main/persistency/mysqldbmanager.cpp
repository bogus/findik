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
#include <vector>

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
				((dbconnection<mysqlpp::Connection>::pointer)pool_[i])->connection()->disconnect();
		}

		mysqldbmanager::mysql_dbconnection_ptr mysqldbmanager::create_connection_object()
		{
			try {
				mysqlpp::Connection * myconn_ = new mysqlpp::Connection(db.c_str(), host.c_str(), username.c_str(), password.c_str());

				mysql_dbconnection_ptr dbconnection__(new mysql_dbconnection(myconn_));

				mysqlpp::Query * domain_q = new mysqlpp::Query(myconn_->query("SELECT domain from blacklist_domain where domain = %0q"));
			        domain_q->parse();
				mysqlpp::Query * url_q = new mysqlpp::Query(myconn_->query("SELECT url from blacklist_url where url = %0q"));
			        url_q->parse();
				mysqlpp::Query * pcre_q = new mysqlpp::Query(myconn_->query("SELECT content,catid from blacklist_content"));
			        pcre_q->parse();
				mysqlpp::Query * file_ext_q = new mysqlpp::Query(myconn_->query("SELECT file_ext from blacklist_mime where file_ext = %0q"));
			        file_ext_q->parse();
				mysqlpp::Query * mime_type_q = new mysqlpp::Query(myconn_->query("SELECT mime_type from blacklist_mime where mime_type = %0q"));
                                mime_type_q->parse();


				dbconnection__->set_object(domain_query, domain_q);

				dbconnection__->set_object(url_query, url_q);

				dbconnection__->set_object(pcre_query, pcre_q);
				
				dbconnection__->set_object(file_ext_query, file_ext_q);
				
				dbconnection__->set_object(mime_type_query, mime_type_q);
				
				
				return dbconnection__;
			}
			catch (const mysqlpp::Exception& e)
			{
				LOG4CXX_ERROR(debug_logger, "SQL Error: " );
				LOG4CXX_ERROR(logging::log_initializer::user_logger,
					"Unable to connect MySQL on host: " << host << " with user: " << username);
			}
		}

		bool mysqldbmanager::domainQuery(std::string hostname) 
		{
			mysql_dbconnection_ptr dbconnection_(get_dbconnection());

			try {
				mysqlpp::StoreQueryResult res = ((mysqlpp::Query *)dbconnection_->get_object(domain_query))->store(hostname);
				
				if(res.num_rows() > 0)
					return false;

				res.clear();
				dbconnection_->unlock();

			} catch (const mysqlpp::BadQuery& e) {
				LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
				return false;
			}
			catch (const mysqlpp::BadConversion& e) {
				LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
				return false;
			}
			catch (const mysqlpp::Exception& e) {
				LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
				return false;
			}

			return true;
		}

		bool mysqldbmanager::urlQuery(std::string url) 
		{
			mysql_dbconnection_ptr dbconnection_(get_dbconnection());
			
			try {
                                mysqlpp::StoreQueryResult res = ((mysqlpp::Query *)dbconnection_->get_object(url_query))->store(url);

                                if(res.num_rows() > 0)
                                        return false;
				
				res.clear();
                                dbconnection_->unlock();

                        } catch (const mysqlpp::BadQuery& e) {
                                LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
                                return false;
                        }
                        catch (const mysqlpp::BadConversion& e) {
                                LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
                                return false;
                        }
                        catch (const mysqlpp::Exception& e) {
                                LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
                                return false;
                        }

                        return true;
		}

		bool mysqldbmanager::pcreQuery(std::map<int,std::string> &pcre_map) 
		{

			mysql_dbconnection_ptr dbconnection_(get_dbconnection());

			try {
				mysqlpp::StoreQueryResult res1 = ((mysqlpp::Query *)dbconnection_->get_object(pcre_query))->store();
				for (int i = 0 ; i < res1.size() ; i++) {
 					pcre_map.insert(std::pair<int,std::string>(1,res1[i][0].c_str())); 
				}
				res1.clear();
				dbconnection_->unlock();

			}  catch (const mysqlpp::BadQuery& e) {
                                LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
                                return false;
                        }
                        catch (const mysqlpp::BadConversion& e) {
                                LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
                                return false;
                        }
                        catch (const mysqlpp::Exception& e) {
                                LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
                                return false;
                        }

			return true;
		}
		
		bool mysqldbmanager::fileExtQuery(std::string file_ext) 
		{
			mysql_dbconnection_ptr dbconnection_(get_dbconnection());
			
			try {
                                mysqlpp::StoreQueryResult res = ((mysqlpp::Query *)dbconnection_->get_object(file_ext_query))->store(file_ext);

                                if(res.num_rows() > 0)
                                        return false;

				res.clear();
                                dbconnection_->unlock();

                        } catch (const mysqlpp::BadQuery& e) {
                                LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
                                return false;
                        }
                        catch (const mysqlpp::BadConversion& e) {
                                LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
                                return false;
                        }
                        catch (const mysqlpp::Exception& e) {
                                LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
                                return false;
                        }

                        return true;
		}
		
		bool mysqldbmanager::mimeTypeQuery(std::string mime_type) 
		{
			mysql_dbconnection_ptr dbconnection_(get_dbconnection());
			
			try {
                                mysqlpp::StoreQueryResult res = ((mysqlpp::Query *)dbconnection_->get_object(mime_type_query))->store(mime_type);

                                if(res.num_rows() > 0)
                                        return false;

				res.clear();
                                dbconnection_->unlock();

                        } catch (const mysqlpp::BadQuery& e) {
                                LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
                                return false;
                        }
                        catch (const mysqlpp::BadConversion& e) {
                                LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
                                return false;
                        }
                        catch (const mysqlpp::Exception& e) {
                                LOG4CXX_ERROR(debug_logger, "ERROR" << e.what());
                                return false;
                        }

                        return true;
		}
	}
}
