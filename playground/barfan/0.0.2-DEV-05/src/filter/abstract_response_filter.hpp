#ifndef FINDIK_FILTER_ABSTRACT_RESPONSE_FILTER_HPP
#define FINDIK_FILTER_ABSTRACT_RESPONSE_FILTER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "mysqldbmanager.hpp"
#include "response.hpp"
#include "filter_report.hpp"

namespace findik {
	namespace filter {

		class abstract_response_filter:
			public boost::enable_shared_from_this<abstract_response_filter>
		{
		public:
			~abstract_response_filter(void);
			virtual bool filter() = 0;

			typedef boost::shared_ptr<abstract_response_filter> pointer;

			std::string get_reply();

		protected:
			io::response & response_ ;
			persistency::dbmanager::pointer manager_ ;
			filter_report::pointer filter_report_;

			abstract_response_filter(persistency::dbmanager::pointer & manager, io::response & response);

		};
	}
}

#endif
