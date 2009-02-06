/*
  Copyright (C) 2008 Burak Oguz (barfan) <findikmail@gmail.com>

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

#ifndef FINDIK_FILTER_REQUEST_FILTER_HPP
#define FINDIK_FILTER_REQUEST_FILTER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "request.hpp"
#include "mysqldbmanager.hpp"
#include "request_filter_factory_impl.hpp"

namespace findik {
	namespace filter {

/*!
 This class represents driver for request_filter_factory_impl to be used in connection class.

 @author Burak Oguz
*/
		class request_filter:
			public boost::enable_shared_from_this<request_filter>
		{
		public:
			/*!
                        Constructor for this class. 

                        \param manager database manager object to pass to abstract_request_filter implementing classes
                        \param request request object to pass to abstract_request_filter implementing classes
                        */
			request_filter(persistency::dbmanager::pointer & manager, io::request & request);
			~request_filter(void);

			/*!
                         Boost shared pointer to the request_filter object.
                        */
			typedef boost::shared_ptr<request_filter> pointer;
			
			/*!
			Generates objects from all abstract_request_filter implementing classes over map using 
			construct function pointer and calls their filter() methods one by one. 

			\return true if request passes from all filters. false if request fails even from one filter. 
			*/
			bool request_chain_filter();

			/*!
                        Gets string representation error page from the failed filter.

                        \return An HTML page which contains error message on the requested page
                        */
			std::string get_reply_string();

		protected:
			/*!
			Request object to be passed to abstract_request_filter implementing classes
			*/
			io::request & request_ ;
			/*!
			Database manager object to pass to abstract_request_filter implementing classes
			*/
			persistency::dbmanager::pointer manager_ ;
			/*!
                        Error page HTML
			*/
			std::string reply_string;

		};
	}
}

#endif

