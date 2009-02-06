#ifndef FINDIK_FILTER_REQUEST_FILTER_FACTORY_IMPL_HPP
#define FINDIK_FILTER_REQUEST_FILTER_FACTORY_IMPL_HPP

#include "abstract_request_filter.hpp"
#include <map>

namespace findik {
	namespace filter {
		typedef abstract_request_filter * (*ClassFactoryFn)( persistency::dbmanager::pointer & manager, io::request & request );

		class request_filter_factory_impl : public std::map<int,ClassFactoryFn>
		{
		public:
			request_filter_factory_impl(void);

			void registerClass(int ID, ClassFactoryFn fn) ;
		};

		typedef request_filter_factory_impl::const_iterator request_filter_factory_iter;

		request_filter_factory_impl& request_filter_factory_map() ;

		template<class T> class request_filter_factory_registrar
		{
		public:
			request_filter_factory_registrar() {
				findik::filter::request_filter_factory_impl().registerClass(T::ID, T::construct);
			}
		};
	}
}

#endif

