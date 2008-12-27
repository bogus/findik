#ifndef FINDIK_FILTER_RESPONSE_FILTER_HPP
#define FINDIK_FILTER_RESPONSE_FILTER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "response.hpp" // must be included before mysql libraries
#include "mysqldbmanager.hpp"
#include "response_filter_factory_impl.hpp"

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
			std::string get_reply_string();

		private:
			io::response & response_;
			persistency::dbmanager::pointer manager_;
			std::string reply_string;
		};
	}
}

#endif
