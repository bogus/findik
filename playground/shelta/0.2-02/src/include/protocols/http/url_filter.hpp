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

#ifndef FINDIK_PROTOCOLS_HTTP_URL_FILTER_HPP
#define FINDIK_PROTOCOLS_HTTP_URL_FILTER_HPP

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/logic/tribool.hpp>
#include <boost/tuple/tuple.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

#include "abstract_filter.hpp"
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
                        URL based request filter for HTTP protocol.
                        \extends boost::enable_shared_from_this<data> to use boost shared pointers.
                        \extends findik::filter::abstract_filter because this is a filter for FINDIK HTTP subsystem.
                        @author Burak OGUZ (barfan)
                        */
			class url_filter:
				public boost::enable_shared_from_this<url_filter>,
                                public findik::filter::abstract_filter
                        {
			
			public:
				boost::tuple<bool, findik::filter::filter_reason_ptr> filter(findik::io::connection_ptr connection_);	
				bool is_applicable(findik::io::connection_ptr connection_);

				class initializer
                                {
                                protected:
                                        /*!
                                        Default constructor.
                                        Construction of this object will register a url_filter instance to filter_service.
                                        */
                                        initializer();

                                        /*!
                                        Instance to create initializer once.
                                        */
                                        static initializer instance;
                                };

			
			protected:
				static log4cxx::LoggerPtr debug_logger_;			
				static int filter_code_;
			};

			typedef boost::shared_ptr<url_filter> url_filter_ptr;

		}
	}
}

#endif
