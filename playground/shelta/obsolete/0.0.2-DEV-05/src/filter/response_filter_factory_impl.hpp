#ifndef FINDIK_FILTER_RESPONSE_FILTER_FACTORY_IMPL_HPP
#define FINDIK_FILTER_RESPONSE_FILTER_FACTORY_IMPL_HPP

#include "content_response_filter.hpp"
#include <map>

namespace findik {
	namespace filter {

		typedef abstract_response_filter * (*ClassFactoryRespFn)( persistency::dbmanager::pointer & manager, io::response & response );

		class response_filter_factory_impl : public std::map<int,ClassFactoryRespFn>
		{
		public:
			response_filter_factory_impl(void);
		};

		typedef response_filter_factory_impl::const_iterator response_filter_factory_iter;

		response_filter_factory_impl& response_filter_factory_map();

		static response_filter_factory_impl response_filter_factory_map_;

		void generate_response_filter_factory_map();

	}
}

#endif

