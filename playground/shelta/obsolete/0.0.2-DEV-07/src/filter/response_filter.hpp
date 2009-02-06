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

#ifndef FINDIK_FILTER_RESPONSE_FILTER_HPP
#define FINDIK_FILTER_RESPONSE_FILTER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "response.hpp" // must be included before mysql libraries
#include "mysqldbmanager.hpp"
#include "response_filter_factory_impl.hpp"

namespace findik {
	namespace filter{
/*!
 This class represents driver for response_filter_factory_impl to be used in connection class.

 @author Burak Oguz
*/
		class response_filter :
			public boost::enable_shared_from_this<response_filter>
		{
		public:
			/*!
                        Constructor for this class.

                        \param manager database manager object to pass to abstract_response_filter implementing classes
                        \param response response object to pass to abstract_response_filter implementing classes
                        */
			response_filter(persistency::dbmanager::pointer & manager,io::response & response);
			~response_filter(void);
			
			/*!
                         Boost shared pointer to the response_filter object.
                        */
			typedef boost::shared_ptr<response_filter> pointer;
			
			/*!
                        Generates objects from all abstract_response_filter implementing classes over map using
                        construct function pointer and calls their filter() methods one by one.

                        \return true if response passes from all filters. false if response fails even from one filter.
                        */
			bool response_chain_filter();

			/*!
                        Gets string representation error page from the failed filter.

                        \return An HTML page which contains error message caused by the response 
                        */
			std::string get_reply_string();

		private:
			/*!
                        Response object to be passed to abstract_response_filter implementing classes
                        */
			io::response & response_;
			/*!
                        Database manager object to pass to abstract_response_filter implementing classes
                        */
			persistency::dbmanager::pointer manager_;
			/*!
                        Error page HTML
                        */
			std::string reply_string;
		};
	}
}

#endif

