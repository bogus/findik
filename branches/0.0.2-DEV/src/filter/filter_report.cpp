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

#include "filter_report.hpp"

namespace findik {
	namespace filter {

		filter_report::filter_report(void)
		{
		}

		filter_report::~filter_report(void)
		{
			reply_result.clear();
		}

		std::string filter_report::get_reply_result()
		{
			return reply_result;
		}

		void filter_report::generate_report(reason_type reason, std::string data)
		{
			reply_result += message_top;
			reply_result += newline;
			reply_result += "Reason : ";
			switch(reason) {
				case request_domain:
					reply_result += "Domain : ";
					reply_result += data;
					reply_result += " is banned by FINDIK, code : 1";
					break;
				case request_url:
					reply_result += "URL : ";
					reply_result += data;
					reply_result += " is banned by FINDIK, code : 2";
					break;
				case request_content:
					reply_result += "Content : ";
					reply_result += data;
					reply_result += " is banned by FINDIK, code : 3";
					break;
				case response_content:
					reply_result += "Content : ";
					reply_result += data;
					reply_result += " is banned by FINDIK, code : 100";
					break;
				case response_content_type:
					reply_result += "Content-Type : ";
					reply_result += data;
					reply_result += " is banned by FINDIK, code : 101";
					break;
			}
			reply_result += newline;
			reply_result += message_bottom;

		}
	}
}

