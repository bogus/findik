#ifndef FINDIK_FILTER_REQUEST_FILTER_FACTORY_IMPL_HPP
#define FINDIK_FILTER_REQUEST_FILTER_FACTORY_IMPL_HPP

#include "domain_request_filter.hpp"
#include "url_request_filter.hpp"
#include <map>

namespace findik {
	namespace filter {

		typedef abstract_request_filter * (*ClassFactoryReqFn)( persistency::dbmanager::pointer & manager, io::request & request );

		class request_filter_factory_impl : public std::map<int,ClassFactoryReqFn>
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

