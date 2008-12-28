#ifndef FINDIK_FILTER_CONTENT_RESPONSE_FILTER_HPP
#define FINDIK_FILTER_CONTENT_RESPONSE_FILTER_HPP

#include "abstract_response_filter.hpp"

namespace findik {
	namespace filter {

		class content_response_filter :
			public abstract_response_filter, public boost::enable_shared_from_this<content_response_filter>
		{
		public:
			~content_response_filter(void);
			bool filter();
			static abstract_response_filter *construct(persistency::dbmanager::pointer & manager, io::response & response);
			enum { ID = 100 } ;

		private:
			content_response_filter(persistency::dbmanager::pointer & manager, io::response & response);

		};
	}
}

#endif

