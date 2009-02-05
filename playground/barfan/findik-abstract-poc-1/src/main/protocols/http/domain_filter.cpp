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

#include "domain_filter.hpp"
#include "service_container.hpp"
#include "tidy_html_parser.hpp"
#include "response.hpp"

namespace findik
{
	namespace protocols
	{
		namespace http
		{
			// initialization of logger
			log4cxx::LoggerPtr domain_filter::debug_logger(log4cxx::Logger::getLogger("findik.protocols.http.domain_filter"));	
			
			// constructor definition of filter service registration inner class
			domain_filter::initializer::initializer()
                        {
                                domain_filter_ptr dfp(new domain_filter());

                                FI_SERVICES->filter_srv().register_filter(dfp);
                        }

                        domain_filter::initializer domain_filter::initializer::instance;

			boost::tuple<bool, findik::filter::filter_reason_ptr> domain_filter::filter(findik::io::connection_ptr connection_) 
			{
				LOG4CXX_DEBUG(debug_logger, "Domain name filter entered"); // log for filter entrance
				
				// get request object from current data
				request_ptr req = boost::static_pointer_cast<request>(connection_->current_data());
				std::string hostname;
				
				// get hostname from request header
				BOOST_FOREACH( header h, req->get_headers() ) {
					if (h.name == "Host")
						hostname = h.value;
				}
				
				// check whether hostname exists in domain blacklist
				if(hostname == "www.live.com"){
					LOG4CXX_DEBUG(debug_logger, "Domain name filter failed for domain " + hostname);
					return boost::make_tuple(false, findik::filter::filter_reason::create_reason(FC_BAD_LOCAL,"hede"));	
				} 
				else {
					LOG4CXX_DEBUG(debug_logger, "Domain name filter passed for domain " + hostname);
					return boost::make_tuple(true, findik::filter::filter_reason::create_reason(FC_BAD_LOCAL,"hede"));	
				}
				
				/*bool is_html = false;
				response_ptr resp = boost::static_pointer_cast<response>(connection_->current_data());
				if(resp->content_type() == "text/html") {
					tidy_html_parser *tdoc = new tidy_html_parser();
					tdoc->parse(connection_->current_data()->content());
				}
				return boost::make_tuple(true, findik::filter::filter_reason::create_reason(FC_BAD_LOCAL,"hede"));*/
			}

                        bool domain_filter::is_applicable(findik::io::connection_ptr connection_)
			{
				// set this filter to be used in request only
				return connection_->proto() == findik::io::http && connection_->current_data()->is_local();	
				//return connection_->proto() == findik::io::http && connection_->current_data()->is_remote();	
			}
		}
	}
}

