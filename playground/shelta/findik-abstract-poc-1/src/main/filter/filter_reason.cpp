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
		filter_reason(unsigned int code) :
			code_(code)
		{}

		filter_reason(unsigned int code, const std::string & reason_str) :
			code_(code),
			reason_str_(reason_str)
		{}

		static filter_reason_ptr filter_reason::create_reason(unsigned int code)
		{
			filter_reason_ptr p(new filter_reason(code));
			return p;
		}

		static filter_reason_ptr filter_reason::create_reason(
				unsigned int code, const std::string & reason_str)
		{
			filter_reason_ptr p(new filter_reason(code, reason_str));
			return p;
		}

		filter_reason::~filter_reason()
		{}

		const std::string & reason_str()
		{
			return reason_str;
		}

		unsigned int code()
		{
			return code_;
		}
	}
}

