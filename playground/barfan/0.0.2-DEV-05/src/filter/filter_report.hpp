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

#ifndef FINDIK_FILTER_FILTER_REPORT_HPP
#define FINDIK_FILTER_FILTER_REPORT_HPP

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

namespace findik {
	namespace filter {

		class filter_report :
			public boost::enable_shared_from_this<filter_report>
		{
		public:
			filter_report(void);
			~filter_report(void);

			enum reason_type
			{
				request_domain = 1,
				request_url = 2,
				request_content = 3,
				response_content = 100,
				response_content_type = 101
			} reason;

			void generate_report(reason_type reason, std::string data);

			std::string get_reply_result();

			typedef boost::shared_ptr<filter_report> pointer;

		private:
			std::string reply_result;

		};

		const std::string message_top =
		  "<html><head><title>FILTERED BY FINDIK</title></head><body><h1>THIS SITE IS FILTERED BY FINDIK</h1>";
		const std::string message_bottom =
		  "</body></html>";
		const std::string newline = "<br />";

	}
}

#endif

