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
			boost::tuple<bool, findik::filter::filter_reason_ptr> *remote_result;
			findik::filter::filter_reason_ptr frp;
			std::string log_str;			

			for ( it=filter_list_.begin();
				it != filter_list_.end(); it++)

				if ( it->second->is_applicable(connection_) )
				{
					boost::tuple<bool, findik::filter::filter_reason_ptr> result = 
						it->second->filter(connection_);
					
					if (!boost::get<0>(result)) {
						LOG4CXX_WARN(logging::log_initializer::filter_logger, boost::get<1>(result)->log_str());			
						return result;
					} else if(connection_->current_data()->is_remote() && connection_->current_data()->has_content()) {
						log_str = boost::get<1>(result)->log_str();
					}
				}

			//TODO: may be return score for greylisting
			if(connection_->current_data()->is_remote() && connection_->current_data()->has_content()) {
				LOG4CXX_INFO(logging::log_initializer::filter_logger, log_str);
			}
			return boost::make_tuple(true, frp);
		}
	}
}

