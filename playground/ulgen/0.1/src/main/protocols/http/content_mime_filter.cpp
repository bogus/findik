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

#include "content_mime_filter.hpp"

namespace findik
{
	namespace protocols
	{
		namespace http
		{
			// initialization of logger
			log4cxx::LoggerPtr content_mime_filter::debug_logger(log4cxx::Logger::getLogger("findik.protocols.http.content_mime_filter"));	
			int  content_mime_filter::filter_code = 501;	
			// constructor definition of filter service registration inner class
			content_mime_filter::initializer::initializer()
                        {
                                content_mime_filter_ptr dfp(new content_mime_filter());

                                FI_SERVICES->filter_srv().register_filter(filter_code,dfp);
                        }

                        content_mime_filter::initializer content_mime_filter::initializer::instance;

			boost::tuple<bool, findik::filter::filter_reason_ptr> content_mime_filter::filter(findik::io::connection_ptr connection_) 
			{
				LOG4CXX_DEBUG(debug_logger, "Content mime-type filter entered"); // log for filter entrance
				response_ptr resp = boost::static_pointer_cast<response>(connection_->current_data());
				std::string content_type;
				if(!FI_SERVICES->db_srv().mimeTypeQuery(resp->magic_mime_type())) 
				{
					LOG4CXX_DEBUG(debug_logger, "Content mime-type filter failed" + resp->magic_mime_type());
					return boost::make_tuple(false, findik::filter::filter_reason::create_reason(filter_code,"Content blocked for mime-type : " + resp->magic_mime_type(), response::forbidden, false, findik::io::http));						
				}
				LOG4CXX_DEBUG(debug_logger, "Content mime-type filter passed");

				return boost::make_tuple(true, findik::filter::filter_reason::create_reason(0));

			}

			bool content_mime_filter::is_applicable(findik::io::connection_ptr connection_)
			{
				// set this filter to be used in request only
				return connection_->proto() == findik::io::http && connection_->current_data()->is_remote();	
			}
		}
	}
}

