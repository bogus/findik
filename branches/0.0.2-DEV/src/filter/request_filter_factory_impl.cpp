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
		}
	}
}

