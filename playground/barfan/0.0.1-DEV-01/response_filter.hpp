#ifndef FINDIK_FILTER_RESPONSE_FILTER_HPP
#define FINDIK_FILTER_RESPONSE_FILTER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "tidy_html_parser.hpp"
#include "mysqldbmanager.hpp"
#include "response.hpp"
#include "filter_report.hpp"

namespace findik {
	namespace filter{

		class response_filter :
			public boost::enable_shared_from_this<response_filter>
		{
		public:
			response_filter(persistency::dbmanager::pointer & manager,io::response & response);
			~response_filter(void);

			typedef boost::shared_ptr<response_filter> pointer;

			bool response_chain_filter();

			std::string get_reply();

		private:
			io::response & response_;
			persistency::dbmanager::pointer manager_;
			filter_report::pointer filter_report_;
			parser::tidy_html_parser::pointer html_parser_;

			bool response_content_filter();
			bool response_content_type_filter();

		};
	}
}

#endif
