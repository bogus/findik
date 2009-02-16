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

#include "configuration_object.hpp"

namespace findik 
{
	namespace config 
	{
		configuration_object::configuration_object(configuration_initializer & config_):
			server_http_run_with_squid_(true),
			server_http_squid_host_("localhost"),
			server_http_squid_port_(3128),
			server_http_squid_keepalive_timeout_(60),
			server_http_max_object_size_(1048576),
			server_local_receive_timeout_(15),
			server_remote_receive_timeout_(60),
			connection_queue_size_(8),
			db_mysql_host_("localhost"),
			db_mysql_database_("findik"),
			db_mysql_username_("findik"),
			db_mysql_password_(""),
			db_pool_size_(32),
			io_number_of_threads_(50),
			reply_reply_file_("/etc/findik/index.html"),
			ssl_local_private_key_("/etc/findik/ssl/private.pem"),
			ssl_local_certificate_("/etc/findik/ssl/public.pem"),
			ssl_local_dh_parameters_("/etc/findik/ssl/dh.pem"),
			ssl_remote_ca_("/etc/findik/ssl/ca.pem"),
			server_max_session_(32),
			server_max_connection_per_session_(4)
		{
			config_.getConfigValue_Bool("findik.server.http.run_with_squid", server_http_run_with_squid_);
			config_.getConfigValue_String("findik.server.http.squid_host", server_http_squid_host_);
			config_.getConfigValue_UInt("findik.server.http.squid_port", server_http_squid_port_);
			config_.getConfigValue_UInt("findik.server.http.squid_keepalive_timeout", server_http_squid_keepalive_timeout_);
			config_.getConfigValue_UInt("findik.server.local_receive_timeout", server_local_receive_timeout_);
			config_.getConfigValue_UInt("findik.server.remote_receive_timeout", server_remote_receive_timeout_);
			config_.getConfigValue_UInt("findik.connection.queue_size", connection_queue_size_);
			config_.getConfigValue_String("findik.db.mysql.host", db_mysql_host_);
			config_.getConfigValue_String("findik.db.mysql.database", db_mysql_database_);
			config_.getConfigValue_String("findik.db.mysql.username", db_mysql_username_);
			config_.getConfigValue_String("findik.db.mysql.password", db_mysql_password_);
			config_.getConfigValue_UInt("findik.db.pool_size", db_pool_size_);
			config_.getConfigValue_UInt("findik.io.number_of_threads", io_number_of_threads_);
			config_.getConfigValue_String("findik.reply.reply_file", reply_reply_file_);
			config_.getConfigValue_String("findik.ssl.local.private_key", ssl_local_private_key_);
			config_.getConfigValue_String("findik.ssl.local.certificate", ssl_local_certificate_);
			config_.getConfigValue_String("findik.ssl.local.dh_parameters", ssl_local_dh_parameters_);
			config_.getConfigValue_String("findik.ssl.remote.ca", ssl_remote_ca_);
			config_.getConfigValue_UInt("findik.server.max_session", server_max_session_);
			config_.getConfigValue_UInt("findik.server.max_connection_per_session", server_max_connection_per_session_);
		}

		configuration_object::~configuration_object()
		{
		}

		bool configuration_object::server_http_run_with_squid()
		{
			return server_http_run_with_squid_;
		}

		const std::string & configuration_object::server_http_squid_host()
		{
			return server_http_squid_host_;
		}

		unsigned int configuration_object::server_http_squid_port()
		{
			return server_http_squid_port_;
		}

		unsigned int configuration_object::server_http_squid_keepalive_timeout()
		{
			return server_http_squid_keepalive_timeout_;
		}

		unsigned int configuration_object::server_local_receive_timeout()
		{
			return server_local_receive_timeout_;
		}

		unsigned int configuration_object::server_remote_receive_timeout()
		{
			return server_remote_receive_timeout_;
		}

		unsigned int configuration_object::server_http_max_object_size()
		{
			return server_http_max_object_size_;
		}

		unsigned int configuration_object::connection_queue_size()
		{
			return connection_queue_size_;
		}

		const std::string & configuration_object::db_mysql_host()
		{
			return db_mysql_host_;
		}

		const std::string & configuration_object::db_mysql_database()
		{
			return db_mysql_database_;
		}

		const std::string & configuration_object::db_mysql_username()
		{
			return db_mysql_username_;
		}

		const std::string & configuration_object::db_mysql_password()
		{
			return db_mysql_password_;
		}

		unsigned int configuration_object::db_pool_size()
		{
			return db_pool_size_;
		}

		unsigned int configuration_object::io_number_of_threads()
		{
			return io_number_of_threads_;
		}

		const std::string & configuration_object::reply_reply_file()
		{
			return reply_reply_file_;
		}

		const std::string & configuration_object::ssl_local_private_key()
		{
			return ssl_local_private_key_;
		}

		const std::string & configuration_object::ssl_local_certificate()
		{
			return ssl_local_certificate_;
		}

		const std::string & configuration_object::ssl_local_dh_parameters()
		{
			return ssl_local_dh_parameters_;
		}

		const std::string & configuration_object::ssl_remote_ca()
		{
			return ssl_remote_ca_;
		}

		unsigned int configuration_object::server_max_session()
		{
			return server_max_session_;
		}

		unsigned int configuration_object::server_max_connection_per_session()
		{
			return server_max_connection_per_session_;
		}
	}
}

