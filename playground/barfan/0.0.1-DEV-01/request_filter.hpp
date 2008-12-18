#ifndef FINDIK_FILTER_REQUEST_FILTER_HPP
#define FINDIK_FILTER_REQUEST_FILTER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "mysqldbmanager.hpp"
#include "request.hpp"
#include "filter_report.hpp"

namespace findik {
	namespace filter {

		class request_filter:
			public boost::enable_shared_from_this<request_filter>
		{
		public:
			~request_filter(void);
			request_filter(persistency::dbmanager::pointer & manager, io::request & request);

			typedef boost::shared_ptr<request_filter> pointer;

			bool request_chain_filter();

			std::string get_reply();

		private:
			io::request & request_ ;
			persistency::dbmanager::pointer manager_ ;
			filter_report::pointer filter_report_;

			bool request_domain_filter();
			bool request_url_filter();
			bool request_content_filter();

		};
	}
}

#endif
