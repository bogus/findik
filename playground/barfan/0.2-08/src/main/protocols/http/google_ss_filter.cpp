/*
  Copyright (C) 2008 Burak OGUZ (barfan) <findikmail@gmail.com>

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

#include "google_ss_filter.hpp"

namespace findik
{
	namespace protocols
	{
		namespace http
		{
			// initialization of logger
			log4cxx::LoggerPtr google_ss_filter::debug_logger_(log4cxx::Logger::getLogger("findik.protocols.http.google_ss_filter"));	
	
			std::string google_ss_filter::filter_code_ = "content_domain";

			boost::tuple<bool, findik::filter::filter_reason_ptr> 
					google_ss_filter::filter(findik::io::connection_ptr connection_, unsigned int param) 
			{
				LOG4CXX_DEBUG(debug_logger_, "Google Safe Search filter entered"); // log for filter entrance
				
				// get request object from current data
                                request_ptr req = boost::static_pointer_cast<request>(connection_->current_data());
                                std::string url = req->request_uri();	
			
				// check whether it is "www.google.com" and contains "/search?"
				std::string::size_type posHost = url.find("www.google.com");
				std::string::size_type posSearch = url.find("/search?");
	
				if(posHost != std::string::npos && posSearch != std::string::npos){
					req->uri += "&safe=active";
				} 
				findik::filter::filter_reason_ptr frp_;
				return boost::make_tuple(true, frp_);	
			}

                        bool google_ss_filter::is_applicable(findik::io::connection_ptr connection_)
			{
				// set this filter to be used in request only
				return connection_->proto() == findik::io::http && connection_->current_data()->is_local();	
			}
		}
	}
}

