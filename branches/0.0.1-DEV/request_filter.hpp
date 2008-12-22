#ifndef FINDIK_FILTER_REQUEST_FILTER_HPP
#define FINDIK_FILTER_REQUEST_FILTER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "request.hpp"
#include "mysqldbmanager.hpp"
#include "request_filter_factory_impl.hpp"

namespace findik {
	namespace filter {

		class request_filter:
			public boost::enable_shared_from_this<request_filter>
		{
		public:
			request_filter(persistency::dbmanager::pointer & manager, io::request & request);
			~request_filter(void);

			typedef boost::shared_ptr<request_filter> pointer;

			bool request_chain_filter();
			std::string get_reply_string();

		protected:
			io::request & request_ ;
			persistency::dbmanager::pointer manager_ ;
			std::string reply_string;

		};
	}
}

#endif
