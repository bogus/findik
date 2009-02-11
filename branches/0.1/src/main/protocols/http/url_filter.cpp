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

#include "url_filter.hpp"

namespace findik
{
	namespace protocols
	{
		namespace http
		{
			// initialization of logger
			log4cxx::LoggerPtr url_filter::debug_logger(log4cxx::Logger::getLogger("findik.protocols.http.url_filter"));	
			int url_filter::filter_code = 404;
			// constructor definition of filter service registration inner class
			url_filter::initializer::initializer()
                        {
                                url_filter_ptr dfp(new url_filter());

                                FI_SERVICES->filter_srv().register_filter(filter_code,dfp);
                        }

                        url_filter::initializer url_filter::initializer::instance;

			boost::tuple<bool, findik::filter::filter_reason_ptr> url_filter::filter(findik::io::connection_ptr connection_) 
			{
				LOG4CXX_DEBUG(debug_logger, "URL filter entered"); // log for filter entrance
				
				// get request object from current data
				request_ptr req = boost::static_pointer_cast<request>(connection_->current_data());
				std::string url = req->request_uri();	
				// check whether hostname exists in domain blacklist
				if(!FI_SERVICES->db_srv().urlQuery(req->request_uri())){
					LOG4CXX_DEBUG(debug_logger, "URL filter failed for " + url);
					 return boost::make_tuple(false, findik::filter::filter_reason::create_reason(filter_code,"URL blocked : " + url, response::forbidden, true, findik::io::http));
				} 
				else {
					LOG4CXX_DEBUG(debug_logger, "URL filter passed for " + url);
				}
			
				return boost::make_tuple(true, findik::filter::filter_reason::create_reason(0));	
			}

                        bool url_filter::is_applicable(findik::io::connection_ptr connection_)
			{
				// set this filter to be used in request only
				return connection_->proto() == findik::io::http && connection_->current_data()->is_local();	
			}
		}
	}
}

