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

#include "service_container.hpp"

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("findik"));

namespace findik
{
	namespace service
	{
		service_container::service_container() :
			resolver_srv_(io_srv_)
		{}

		service_container_ptr service_container::instance_;

		service_container::~service_container() 
		{}

		void service_container::start()
		{
			db_srv_.connect();
		}

		boost::asio::io_service & service_container::io_srv()
		{
			return io_srv_;
		}

		boost::asio::ip::tcp::resolver & service_container::resolver_srv()
		{
			return resolver_srv_;
		}

		session_service & service_container::session_srv()
		{
			return session_srv_;
		}

		parser_service & service_container::parser_srv()
		{
			return parser_srv_;
		}

		filter_service & service_container::filter_srv()
		{
			return filter_srv_;
		}

		findik::config::configuration & service_container::config_srv()
		{
			return config_srv_;
		}

		reply_service & service_container::reply_srv()
		{
			return reply_srv_;
		}

		findik::persistency::mysqldbmanager & service_container::db_srv()
		{
			return db_srv_;
		}
	}
}

