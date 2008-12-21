#include "request_filter_factory_impl.hpp"

namespace findik {
	namespace filter {

		request_filter_factory_impl & request_filter_factory_map()
		{
			static request_filter_factory_impl rfm;
			return rfm;
		}

		#define INCLUDE_UNIT(a) extern void init_##a();init_##a();

		request_filter_factory_impl::request_filter_factory_impl(void)
		{
			// Change these lines to change
			// which classes are available
			//
			INCLUDE_UNIT(url_request_filter)
			INCLUDE_UNIT(domain_request_filter)
		}	

		void request_filter_factory_impl::registerClass(int ID, ClassFactoryFn fn)
		{
			//(*this)[ID] = fn ;
			request_filter_factory_map()[ID] = fn;
		}
	}
}

