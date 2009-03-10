/*
  Copyright (C) 2008 H. Kerem Cevahir (shelta) <findikmail@gmail.com>

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

#include "filter_service.hpp"

#include <boost/tuple/tuple.hpp>

namespace findik
{
	namespace service
	{
		filter_service::filter_service()
		{}

		filter_service::~filter_service()
		{}

		void filter_service::register_filter(int code, findik::filter::abstract_filter_ptr filter_)
		{
			filter_list_.insert(std::pair<int, findik::filter::abstract_filter_ptr>(code, filter_));
		}

		boost::tuple<bool, findik::filter::filter_reason_ptr> 
			filter_service::filter(findik::io::connection_ptr connection_)
		{
			std::map<int,findik::filter::abstract_filter_ptr>::iterator it;
			std::string separator = " ";
			boost::tuple<bool, findik::filter::filter_reason_ptr> *remote_result;
			findik::filter::filter_reason_ptr frp;

			for ( it=filter_list_.begin();
				it != filter_list_.end(); it++)

				if ( it->second->is_applicable(connection_) )
				{
					boost::tuple<bool, findik::filter::filter_reason_ptr> result = 
						it->second->filter(connection_);
					
					if (!boost::get<0>(result)) {
						// Current log string : protocol::reason_code::[f|p]::src_ip::dst_dom dst_url reason
						std::string log_string =  boost::lexical_cast<std::string>(connection_->proto()) + separator;
						log_string += boost::lexical_cast<std::string>(boost::get<1>(result)->code()) + separator;
						log_string += "f" + separator;
						log_string += connection_->local_endpoint() + separator;
						log_string += boost::get<1>(result)->log_str();
			
						LOG4CXX_WARN(logging::log_initializer::filter_logger, log_string);			
						return result;
					} else {
						frp = boost::get<1>(result);
					}
				}

			//TODO: may be return score for greylisting
			std::string log_string =  boost::lexical_cast<std::string>(connection_->proto()) + separator;
			log_string += boost::lexical_cast<std::string>(frp->code()) + separator;
			log_string += "p" + separator;
			log_string += connection_->local_endpoint() + separator;
			log_string += frp->log_str();
			LOG4CXX_INFO(logging::log_initializer::filter_logger, log_string);
			return boost::make_tuple(true, frp);
		}
	}
}

