#ifndef FINDIK_FILTER_DOMAIN_REQUEST_FILTER_HPP
#define FINDIK_FILTER_DOMAIN_REQUEST_FILTER_HPP

#include "request_filter_factory_impl.hpp"

namespace findik {
	namespace filter {

		class domain_request_filter :
			public abstract_request_filter, public boost::enable_shared_from_this<domain_request_filter>
		{
		public:
			~domain_request_filter(void);
			bool filter();
			static abstract_request_filter *construct(persistency::dbmanager::pointer & manager, io::request & request);
			enum { ID = 1 } ;

		private:
			domain_request_filter(persistency::dbmanager::pointer & manager, io::request & request);

		};
	}
}

extern void init_domain_request_filter ();
void init_domain_request_filter ()
{
	static findik::filter::request_filter_factory_registrar<findik::filter::domain_request_filter> rffr;
}

#endif

