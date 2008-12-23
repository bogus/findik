#ifndef FINDIK_FILTER_ABSTRACT_REQUEST_FILTER_HPP
#define FINDIK_FILTER_ABSTRACT_REQUEST_FILTER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "mysqldbmanager.hpp"
#include "request.hpp"
#include "filter_report.hpp"

namespace findik {
	namespace filter {

		class abstract_request_filter:
			public boost::enable_shared_from_this<abstract_request_filter>
		{
		public:
			~abstract_request_filter(void);
			virtual bool filter() = 0;

			typedef boost::shared_ptr<abstract_request_filter> pointer;

			std::string get_reply();

		protected:
			io::request & request_ ;
			persistency::dbmanager::pointer manager_ ;
			filter_report::pointer filter_report_;

			abstract_request_filter(persistency::dbmanager::pointer & manager, io::request & request);

		};
	}
}

#endif
