#include "request_filter.hpp"

namespace findik {
	namespace filter {
		request_filter::~request_filter(void)
		{
		}

		request_filter::request_filter(dbmanager::pointer & manager, io::request & request):
			manager_(manager), request_(request)
		{
		}

		bool request_filter::request_chain_filter() 
		{
			if(request_domain_filter() &&
				request_url_filter() &&
				request_content_filter())
				return true;
			
			return false;
		}

		bool request_filter::request_content_filter()
		{
			return true;
		}

		bool request_filter::request_domain_filter()
		{
			bool result = manager_->domainQuery(request_.host());
			if (!result)
			{
				LOG4CXX_WARN(log_initializer::filter_logger, request_.host() << " DOMAIN BLOCKED");
			}
			return result;
		}

		bool request_filter::request_url_filter()
		{
			return true;
		}
	}
}