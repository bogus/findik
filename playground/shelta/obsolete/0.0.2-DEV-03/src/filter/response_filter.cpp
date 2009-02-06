/*
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

#include "response_filter.hpp"

namespace findik {
	namespace filter {

		response_filter::response_filter(persistency::dbmanager::pointer & manager, io::response & response):
			manager_(manager), response_(response)
		{

		}

		response_filter::~response_filter(void)
		{
		}

		bool response_filter::response_chain_filter()
		{
			response_filter_factory_iter it = response_filter_factory_map().begin();
			bool isOk = true;

			while((it != response_filter_factory_map().end()) && (isOk == true))
			{
				abstract_response_filter * resp_filter = (*it).second(manager_,response_) ;
				isOk = resp_filter->filter();
				reply_string = resp_filter->get_reply();
				delete resp_filter ;
				it++;
			}

			return isOk;

		}

		std::string response_filter::get_reply_string()
		{
			return reply_string;
		}


	}
}

