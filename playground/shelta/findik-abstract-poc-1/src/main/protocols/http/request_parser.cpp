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

#include "request_parser.hpp"

#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

namespace findik
{
	namespace protocols
	{
		namespace http
		{

			boost::tuple<boost::tribool, char*> request_parser::parse(
					findik::io::connection_ptr connection_,
					char* begin, char* end
				)
			{
				while (begin != end)
				{
					boost::tribool result = consume(connection_, *begin++);
					if (result || !result)
						return boost::make_tuple(result, begin);
				}

				boost::tribool result = boost::indeterminate;
				return boost::make_tuple(result, begin);
			}

			boost::tribool request_parser::consume(findik::io::connection_ptr connection_, char input)
			{
				return false;
			}

		}
	}
}

