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

#include "filter_service.hpp"

#include <boost/tuple/tuple.hpp>

namespace findik
{
	namespace service
	{
		filter_service::filter_service()
		{}

		filter_service::~filter_service()
		{}

		void filter_service::register_filter(findik::filter::abstract_filter_ptr filter_)
		{
			filter_list_.push_back(filter_);
		}

		boost::tuple<bool, findik::filter::filter_reason_ptr> 
			filter_service::filter(findik::io::connection_ptr connection_)
		{
			std::list<findik::filter::abstract_filter_ptr>::iterator it;

			for ( it=filter_list_.begin();
				it != filter_list_.end(); it++ )

				if ( (*it)->is_applicable(connection_) )
				{
					boost::tuple<bool, findik::filter::filter_reason_ptr> result = 
						(*it)->filter(connection_);
					
					if (!boost::get<0>(result))
						return result;
				}

			//TODO: may be return score for greylisting
			findik::filter::filter_reason_ptr frp;
			return boost::make_tuple(true, frp);
		}
	}
}

