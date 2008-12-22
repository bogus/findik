#ifndef FINDIK_FILTER_URL_REQUEST_FILTER_HPP
#define FINDIK_FILTER_URL_REQUEST_FILTER_HPP

#include "request_filter_factory_impl.hpp"

namespace findik {
	namespace filter {

		class url_request_filter :
			public abstract_request_filter, public boost::enable_shared_from_this<url_request_filter>
		{
		public:
			~url_request_filter(void);
			bool filter();
			static abstract_request_filter *construct(persistency::dbmanager::pointer & manager, io::request & request);
			enum { ID = 2 } ;

		private:
			url_request_filter(persistency::dbmanager::pointer & manager, io::request & request);

		};
	}
}

extern void init_url_request_filter ();
void init_url_request_filter ()
{
	static findik::filter::request_filter_factory_registrar<findik::filter::url_request_filter> rffr;
}

#endif