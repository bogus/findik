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

#include "abstract_request_filter.hpp"

namespace findik {
	namespace filter {
		abstract_request_filter::~abstract_request_filter(void)
		{
		}

		abstract_request_filter::abstract_request_filter(persistency::dbmanager::pointer & manager, io::request & request):
			manager_(manager), request_(request)
		{
			filter_report_ = filter_report::pointer(new filter_report());
		}

		std::string abstract_request_filter::get_reply()
		{
			return filter_report_->get_reply_result();
		}
		/*
		bool request_filter::request_content_filter()
		{
			return true;
		}

		bool request_filter::request_url_filter()
		{

		}
		*/
	}
}

