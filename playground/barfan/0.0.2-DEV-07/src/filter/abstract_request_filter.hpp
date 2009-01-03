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

#ifndef FINDIK_FILTER_ABSTRACT_REQUEST_FILTER_HPP
#define FINDIK_FILTER_ABSTRACT_REQUEST_FILTER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "mysqldbmanager.hpp"
#include "request.hpp"
#include "filter_report.hpp"

namespace findik {
	namespace filter {

/*!
 This class represents an interface for other request_filter implementations

 @author Burak Oguz
*/
		class abstract_request_filter:
			public boost::enable_shared_from_this<abstract_request_filter>
		{
		public:
			~abstract_request_filter(void);
			
			/*!
			Virtual function for extending classes to implement. In request_filter class
			this filter method is called to implement filter chain over request_filter_factory_impl
	
			\return true if request passes from filtering operation.
			*/
			virtual bool filter() = 0;

			/*!
                         Boost shared pointer to the abstract_request_filter object.
                        */
			typedef boost::shared_ptr<abstract_request_filter> pointer;

			/*!
			Prepares string representation error page if filter fails to validate requested page.

			\return An HTML page which contains error message on the requested page
			*/			
			std::string get_reply();

		protected:
			/*!
			Request object to be used in extending classes for filtering operations
			*/
			io::request & request_ ;
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

			/*!
			Constructor for this object and all extending classes.
			\param manager database manager object to filter searching
			\param request request object which filtering operation will use	
			*/
			abstract_request_filter(persistency::dbmanager::pointer & manager, io::request & request);

		};
	}
}

#endif
