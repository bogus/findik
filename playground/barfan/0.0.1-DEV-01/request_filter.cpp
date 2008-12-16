#include "request_filter.hpp"

namespace findik {
	namespace filter {
		request_filter::~request_filter(void)
		{
		}

		request_filter::request_filter(persistency::dbmanager::pointer & manager, io::request & request):
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
			return manager_->urlQuery(request_.get_uri());
		}

		bool request_filter::request_domain_filter()
		{
			return manager_->domainQuery(request_.host());
		}

		bool request_filter::request_url_filter()
		{
			return true;
		}
	}
}