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

#include "data.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

namespace findik
{
	namespace protocols
	{
		namespace http
		{
			data::data() :
				content_length_(0)
			{}

			void data::add_blank_header()
			{
				headers_.push_back(header());
			}

			header & data::last_header()
			{
				return headers_.back();
			}

			const std::vector<header> & data::get_headers()
			{
				return headers_;
			}

			unsigned int data::content_length()
			{
				if (content_length_ == 0)
					BOOST_FOREACH( header h, headers_ )
						if (h.name == "Content-Length")
							content_length_ =
							boost::lexical_cast< unsigned int >(h.value);

				return content_length_;
			}

		}
	}
}

