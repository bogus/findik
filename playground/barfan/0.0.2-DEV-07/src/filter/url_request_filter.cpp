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

#include "url_request_filter.hpp"

namespace findik {
	namespace filter {

		url_request_filter::url_request_filter(findik::persistency::dbmanager::pointer & manager, findik::io::request & request)
			: findik::filter::abstract_request_filter(manager, request)
		{
		}

		url_request_filter::~url_request_filter(void)
		{
		}

		bool url_request_filter::filter()
		{
			LOG4CXX_DEBUG(debug_logger, "checking for uri: " << request_.get_full_uri());
			bool isOk = manager_->urlQuery(request_.get_full_uri());
			if(!isOk) {
				LOG4CXX_WARN(logging::log_initializer::filter_logger, request_.get_full_uri() << " URL BLOCKED");
				filter_report_->generate_report(filter_report::request_url,this->generate_report_data());
			}
			return isOk;
		}

		findik::filter::abstract_request_filter *url_request_filter::construct(persistency::dbmanager::pointer & manager, io::request & request)
		{
			return new url_request_filter(manager,request);
		}

		std::string url_request_filter::generate_report_data()
                {
                        std::string report_data;
                        std::ostringstream stm;
                        stm << ID;
			report_data = "Reason : ";
			report_data += "URL : ";
			report_data += request_.get_full_uri();
			report_data += " is banned by FINDIK, code : ";
			report_data += stm.str();
                        return report_data;
                }

		log4cxx::LoggerPtr url_request_filter::debug_logger(log4cxx::Logger::getLogger("findik.filter.url_request_filter"));
	}
}

