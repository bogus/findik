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

#ifndef FINDIK_FILTER_REQUEST_FILTER_HPP
#define FINDIK_FILTER_REQUEST_FILTER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "request.hpp"
#include "mysqldbmanager.hpp"
#include "request_filter_factory_impl.hpp"

namespace findik {
	namespace filter {

		class request_filter:
			public boost::enable_shared_from_this<request_filter>
		{
		public:
			request_filter(persistency::dbmanager::pointer & manager, io::request & request);
			~request_filter(void);

			typedef boost::shared_ptr<request_filter> pointer;

			bool request_chain_filter();
			std::string get_reply_string();

		protected:
			io::request & request_ ;
			persistency::dbmanager::pointer manager_ ;
			std::string reply_string;

		};
	}
}

#endif

