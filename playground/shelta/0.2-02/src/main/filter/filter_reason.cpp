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

#include "filter_reason.hpp"

namespace findik
{
	namespace filter
	{
		filter_reason::filter_reason(unsigned int code) :
			code_(code),
                        reason_str_(" "),
                        return_code_(0),
                        close_connection_(false),
                        protocol_(0),
                        log_str_(" ")
		{}

		filter_reason::filter_reason(unsigned int code, const std::string & reason_str, unsigned int return_code, bool close_connection, unsigned int protocol, const std::string & log_str) :
			code_(code),
			reason_str_(reason_str),
			return_code_(return_code),
			close_connection_(close_connection_),
			protocol_(protocol),
			log_str_(log_str)
		{}

		filter_reason::~filter_reason()
		{}

		const std::string & filter_reason::reason_str()
		{
			return reason_str_;
		}

		unsigned int filter_reason::code()
		{
			return code_;
		}

		unsigned int filter_reason::return_code()
                {
                        return return_code_;
                }

		bool filter_reason::close_connection()
                {
                        return close_connection_;
                }

		unsigned int filter_reason::protocol()
                {
                        return protocol_;
                }

                const std::string & filter_reason::log_str()
		{
			return log_str_;
		}
	}
}

