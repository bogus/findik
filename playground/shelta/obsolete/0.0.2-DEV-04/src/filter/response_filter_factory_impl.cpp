#include "response_filter_factory_impl.hpp"

namespace findik {
	namespace filter {

		response_filter_factory_impl::response_filter_factory_impl(void)
		{
		}

		response_filter_factory_impl & response_filter_factory_map()
		{
			return findik::filter::response_filter_factory_map_;
		}

		void generate_response_filter_factory_map()
		{
			// Change these lines to change
			// which classes are available
			//
			findik::filter::response_filter_factory_map_[content_response_filter::ID] = content_response_filter::construct;
		}
	}
}

