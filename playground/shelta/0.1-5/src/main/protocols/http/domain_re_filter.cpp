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

#include "domain_re_filter.hpp"

namespace findik
{
	namespace protocols
	{
		namespace http
		{
			// initialization of logger
			log4cxx::LoggerPtr domain_re_filter::debug_logger(log4cxx::Logger::getLogger("findik.protocols.http.domain_re_filter"));	
			int domain_re_filter::filter_code = 402;
			// constructor definition of filter service registration inner class
			domain_re_filter::initializer::initializer()
                        {
                                domain_re_filter_ptr dfp(new domain_re_filter());

                                FI_SERVICES->filter_srv().register_filter(dfp);
                        }

                        domain_re_filter::initializer domain_re_filter::initializer::instance;

			boost::tuple<bool, findik::filter::filter_reason_ptr> domain_re_filter::filter(findik::io::connection_ptr connection_) 
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
				if(FI_SERVICES->util_srv().pcre().matches_predefined(hostname).size() > 0){
					LOG4CXX_DEBUG(debug_logger, "Domain name regular expression filter failed for domain " + hostname);
					return boost::make_tuple(false, findik::filter::filter_reason::create_reason(filter_code,"Domain blocked : " + hostname));
				} 
				else {
					LOG4CXX_DEBUG(debug_logger, "Domain name regular expression filter passed for domain " + hostname);
				}
				
				return boost::make_tuple(true, findik::filter::filter_reason::create_reason(0,""));	
			}

                        bool domain_re_filter::is_applicable(findik::io::connection_ptr connection_)
			{
				// set this filter to be used in request only
				return connection_->proto() == findik::io::http && connection_->current_data()->is_local();	
			}
		}
	}
}

