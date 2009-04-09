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

#ifndef FINDIK_PROTOCOLS_HTTP_FILTER_RESULT_GENERATOR_HPP
#define FINDIK_PROTOCOLS_HTTP_FILTER_RESULT_GENERATOR_HPP

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

#include "http_filter_logger.hpp"
#include "reply_service.hpp"
#include "request.hpp"
#include "response.hpp"
#include "service_container.hpp"

#include <string>

namespace findik
{
	namespace protocols
	{
		namespace http
		{
			
			/*!
                        Filter logger for HTTP protocol.
                        \extends boost::enable_shared_from_this<data> to use boost shared pointers.
                        \extends findik::filter::abstract_filter because this is a filter for FINDIK HTTP subsystem.
                        @author Burak OGUZ (barfan)
                        */
			class http_filter_result_generator :
				public boost::enable_shared_from_this<http_filter_result_generator>
                        {
			
			public:
				http_filter_result_generator(
					const std::string & filter_code, 
					bool filter_result, 
					unsigned int return_code, 
					bool is_close_connection, 
					const std::string & reply_str, 
					const std::string & filter_reason, 
					findik::io::connection_ptr connection_, 
					request_ptr request_, 
					response_ptr response_
				);

				http_filter_result_generator(
					const std::string & filter_code, 
					bool filter_result, 
					unsigned int return_code, 
					bool is_close_connection, 
					const std::string & reply_str, 
					const std::string & filter_reason, 
					findik::io::connection_ptr connection_, 
					request_ptr request_
				);

				const std::string & log_str();
				const std::string & reply_str();

			protected:
				const std::string generateGMTDate();

			private:
				findik::io::protocol proto_;
				std::string filter_code_;
				bool filter_result_;
				unsigned int return_code_;
				bool is_close_connection_;
				std::string reply_str_;
				std::string local_endpoint_;
				std::string domain_name_;
				std::string url_;
				unsigned int request_size_;
				unsigned int response_size_;
				std::string filter_reason_;
				std::string log_str_;

				std::string return_resp_;
			};

			typedef boost::shared_ptr<http_filter_result_generator> http_filter_result_generator_ptr;

		}
	}
}

#endif

