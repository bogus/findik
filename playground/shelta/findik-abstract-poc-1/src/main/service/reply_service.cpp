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

#include "reply_service.hpp"

namespace findik
{
	namespace service
	{
		reply_service::reply_service()
		{
			stock_replies_[findik::io::http][FC_BAD_LOCAL] = "Bad request!";
			stock_replies_[findik::io::http][FC_BAD_REMOTE] = "Bad response!";
		}
		
		reply_service::~reply_service()
		{}

		void reply_service::reply(boost::asio::streambuf & sbuf,
			findik::io::protocol proto, unsigned int code)
		{
			std::ostream os(&sbuf);
			os << stock_replies_[proto][code];
		}

		void reply_service::reply(boost::asio::streambuf & sbuf,
				findik::io::protocol proto, findik::filter::filter_reason_ptr reason)
		{
			// TODO: reply generator chain .
			std::ostream os(&sbuf);
			os << stock_replies_[proto][reason->code()];
		}
	}
}

