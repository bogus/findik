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

#include "request_filter.hpp"

namespace findik {
	namespace filter {
		request_filter::~request_filter(void)
		{
		}

		request_filter::request_filter(persistency::dbmanager::pointer & manager, io::request & request):
			manager_(manager), request_(request)
		{
		}

		bool request_filter::request_chain_filter()
		{
			request_filter_factory_iter it = request_filter_factory_map().begin();
			bool isOk = true;

			while((it != request_filter_factory_map().end()) && (isOk == true))
			{
				abstract_request_filter * req_filter = (*it).second(manager_,request_) ;
				isOk = req_filter->filter();
				reply_string = req_filter->get_reply();
				delete req_filter ;
				it++;
			}

			return isOk;

		}

		std::string request_filter::get_reply_string()
		{
			return reply_string;
		}
	}
}

