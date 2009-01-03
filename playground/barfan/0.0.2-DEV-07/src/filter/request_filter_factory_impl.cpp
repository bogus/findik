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

#include "request_filter_factory_impl.hpp"

namespace findik {
	namespace filter {

		request_filter_factory_impl::request_filter_factory_impl(void)
		{
		}

		request_filter_factory_impl & request_filter_factory_map()
		{
			return findik::filter::request_filter_factory_map_;
		}

		void generate_request_filter_factory_map()
		{
			// Change these lines to change
			// which classes are available
			//
			findik::filter::request_filter_factory_map_[domain_request_filter::ID] = domain_request_filter::construct;
			findik::filter::request_filter_factory_map_[url_request_filter::ID] = url_request_filter::construct;
			findik::filter::request_filter_factory_map_[domain_pcre_request_filter::ID] = domain_pcre_request_filter::construct;
			findik::filter::request_filter_factory_map_[url_pcre_request_filter::ID] = url_pcre_request_filter::construct;
		}
	}
}

