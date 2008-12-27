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

#ifndef FINDIK_FILTER_REQUEST_FILTER_FACTORY_IMPL_HPP
#define FINDIK_FILTER_REQUEST_FILTER_FACTORY_IMPL_HPP

#include "domain_request_filter.hpp"
#include "url_request_filter.hpp"
#include <map>

namespace findik {
	namespace filter {

		typedef abstract_request_filter * (*ClassFactoryFn)( persistency::dbmanager::pointer & manager, io::request & request );

		class request_filter_factory_impl : public std::map<int,ClassFactoryFn>
		{
		public:
			request_filter_factory_impl(void);
		};

		typedef request_filter_factory_impl::const_iterator request_filter_factory_iter;

		request_filter_factory_impl& request_filter_factory_map();

		static request_filter_factory_impl request_filter_factory_map_;

		void generate_request_filter_factory_map();

	}
}

#endif

