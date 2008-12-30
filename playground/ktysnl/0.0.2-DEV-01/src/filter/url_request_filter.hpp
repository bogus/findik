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

#ifndef FINDIK_FILTER_URL_REQUEST_FILTER_HPP
#define FINDIK_FILTER_URL_REQUEST_FILTER_HPP

#include "request_filter_factory_impl.hpp"

namespace findik {
	namespace filter {

/*!
 This class represents an implementation for abstract_request_filter

 @author Burak Oguz
*/
		class url_request_filter :
			public abstract_request_filter, public boost::enable_shared_from_this<url_request_filter>
		{
		public:
			~url_request_filter(void);
			/*!
                        Implementing function of  abstract_request_filter::filter(). Gets url name from request header and checks it from
                        database.

                        \return true if url does not exists in blacklist_url
                        */
			bool filter();

			/*!
                        This function will be registered to request_filter_factory_impl map to generate instances of this class.

                        \return an instance of url_request_filter
                        */
			static abstract_request_filter *construct(persistency::dbmanager::pointer & manager, io::request & request);
			/*!
                        Unique ID of this class to generate instances from map.
                        */
			enum { ID = 2 } ;

		private:
			/*!
                        Constructor for this class. Calls only super classes constructor.
                        \param manager database manager object to filter searching
                        \param request request object which filtering operation will use
                        */
			url_request_filter(persistency::dbmanager::pointer & manager, io::request & request);

		protected:
			static log4cxx::LoggerPtr debug_logger;
		};
	}
}


#endif

