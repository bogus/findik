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

namespace findik
{
	namespace service
	{
		service_container::~service_container() :
			resolver_(io_service_)
		{}

		static service_container_ptr service_container::instance()
		{
			if (instance_.get() == 0)
				instance_.reset(new service_container());
			return instance_;
		}

		boost::asio::io_service & service_container::io_service()
		{
			return io_service_;
		}

		boost::asio::ip::tcp::resolver & service_container::resolver()
		{
			return resolver_;
		}

		session_service & service_container::session_service()
		{
			return session_service_;
		}

		parser_service & service_container::parser_service()
		{
			return parser_service_;
		}

		filter_service & service_container::filter_service()
		{
			return filter_service_;
		}

		findik::config::configuration & config()
		{
			return config_;
		}

		reply_service & reply_service()
		{
			return reply_service_;
		}
	}
}

