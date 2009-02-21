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

#ifndef FINDIK_CONFIG_CONFIGURATION_OBJECT_HPP
#define FINDIK_CONFIG_CONFIGURATION_OBJECT_HPP

#include "configuration_initializer.hpp"

#include <string>

namespace findik 
{
	namespace config 
	{

		/*!
		An object encapsulates configuration parameters.
		@author H. Kerem Cevahir (shelta)
		*/
		class configuration_object
		{
		public:
			/*!
			Default constructor.
			*/
			configuration_object(configuration_initializer & config_);

			/*!
			Default destructor.
			*/
			~configuration_object();

			bool server_http_run_with_squid();

			const std::string & server_http_squid_host();

			unsigned int server_http_squid_port();

			unsigned int server_http_squid_keepalive_timeout();

			unsigned int server_local_receive_timeout();

			unsigned int server_remote_receive_timeout();

			unsigned int server_http_max_object_size();

			unsigned int connection_queue_size();

			const std::string & db_mysql_host();

			const std::string & db_mysql_database();

			const std::string & db_mysql_username();

			const std::string & db_mysql_password();

			unsigned int db_pool_size();

			unsigned int io_number_of_threads();

			const std::string & reply_reply_file();

			bool use_clamd();

                        const std::string & clamd_host();

                        const std::string & clamd_port();

                        bool use_ad_kerbv5_negotiation_auth();

                        const std::string & ad_service_name();

                        const std::string & ad_keytab_file();

	
		protected:

			bool server_http_run_with_squid_;

			std::string server_http_squid_host_;

			unsigned int server_http_squid_port_;

			unsigned int server_http_squid_keepalive_timeout_;

			unsigned int server_local_receive_timeout_;

			unsigned int server_remote_receive_timeout_;

			unsigned int server_http_max_object_size_;

			unsigned int connection_queue_size_;

			std::string db_mysql_host_;

			std::string db_mysql_database_;

			std::string db_mysql_username_;

			std::string db_mysql_password_;

			unsigned int db_pool_size_;

			unsigned int io_number_of_threads_;
			
			std::string reply_reply_file_;

			bool use_clamd_;
			
			std::string clamd_host_;
			
			std::string clamd_port_;
			
			bool use_ad_kerbv5_negotiation_auth_;
		
                        std::string ad_service_name_;

                        std::string ad_keytab_file_;


		};
	}
}

#endif

