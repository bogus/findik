/*
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

		class abstract_request_filter:
			public boost::enable_shared_from_this<abstract_request_filter>
		{
		public:
			~abstract_request_filter(void);
			virtual bool filter() = 0;

			typedef boost::shared_ptr<abstract_request_filter> pointer;

			std::string get_reply();

		protected:
			io::request & request_ ;
			persistency::dbmanager::pointer manager_ ;
			filter_report::pointer filter_report_;

			abstract_request_filter(persistency::dbmanager::pointer & manager, io::request & request);

		};
	}
}

#endif
