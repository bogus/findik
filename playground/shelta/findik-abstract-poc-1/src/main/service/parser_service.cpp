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

#include "parser_service.hpp"

#include "request_parser.hpp"
#include "response_parser.hpp"

namespace findik
{
	namespace service
	{
		parser_service::parser_service()
		{
			findik::protocols::http::request_parser_ptr rq(
					new findik::protocols::http::request_parser()
				);
			findik::protocols::http::response_parser_ptr rs(
					new findik::protocols::http::response_parser()
				);
			local_parser_map_[findik::io::http] = rq;
			remote_parser_map_[findik::io::http] = rs;
		}

		parser_service::~parser_service()
		{}

		boost::tuple<boost::tribool, char*> parser_service::parse(
				findik::io::connection_ptr connection_,
				char* begin, char* end
			)
		{
			if (connection_->current_data()->is_local())
				return local_parser_map_[connection_->proto()]->parse(
						connection_, begin, end
					);
			else
				return remote_parser_map_[connection_->proto()]->parse(
						connection_, begin, end
					);
		}

	}
}

