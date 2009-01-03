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

#ifndef FINDIK_FILTER_ABSTRACT_RESPONSE_FILTER_HPP
#define FINDIK_FILTER_ABSTRACT_RESPONSE_FILTER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "mysqldbmanager.hpp"
#include "response.hpp"
#include "filter_report.hpp"

namespace findik {
	namespace filter {
/*!
 This class represents an interface for other response_filter implementations

 @author Burak Oguz
*/
		class abstract_response_filter:
			public boost::enable_shared_from_this<abstract_response_filter>
		{
		public:
			~abstract_response_filter(void);
			/*!
                        Virtual function for extending classes to implement. In response_filter class
                        this filter method is called to implement filter chain over response_filter_factory_impl

                        \return true if request passes from filtering operation.
                        */
			virtual bool filter() = 0;

			/*!
                         Boost shared pointer to the abstract_response_filter object.
                        */
			typedef boost::shared_ptr<abstract_response_filter> pointer;
			
			/*!
                        Prepares string representation error page if filter fails to validate response.

                        \return An HTML page which contains error message caused by the response
                        */
			std::string get_reply();

		protected:
			/*!
                        Response object to be used in extending classes for filtering operations
                        */
			io::response & response_ ;
			/*!
                        Persistency object to be used in extending classes for filtering operations
                        */
			persistency::dbmanager::pointer manager_ ;
			/*!
                        Filter report object to be used in extending classes to save failure notice in request filtering
                        */
			filter_report::pointer filter_report_;

			/*!
                        Virtual function for extending classes to implement. Generates report data to be
                        shown to user if filter fails

                        \return report reason string
                        */
                        virtual std::string generate_report_data() = 0;

			abstract_response_filter(persistency::dbmanager::pointer & manager, io::response & response);

		};
	}
}

#endif
