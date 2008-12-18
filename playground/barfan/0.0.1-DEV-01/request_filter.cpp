#include "request_filter.hpp"

namespace findik {
	namespace filter {
		request_filter::~request_filter(void)
		{
			
		}

		request_filter::request_filter(persistency::dbmanager::pointer & manager, io::request & request):
			manager_(manager), request_(request)
		{
			filter_report_ = filter_report::pointer(new filter_report());
		}

		bool request_filter::request_chain_filter() 
		{
			if(request_domain_filter() &&
				request_url_filter() &&
				request_content_filter())
				return true;
			
			return false;
		}

		std::string request_filter::get_reply()
		{
			return filter_report_->get_reply_result();
		}

		bool request_filter::request_content_filter()
		{
			return true;
		}

		bool request_filter::request_domain_filter()
		{
			bool isOk = manager_->domainQuery(request_.host());
			if(!isOk)
				filter_report_->generate_report(filter_report::reason_type::request_domain,request_.host());
			
			return isOk;
		}

		bool request_filter::request_url_filter()
		{
			bool isOk = manager_->urlQuery(request_.get_uri());
			if(!isOk)
				filter_report_->generate_report(filter_report::reason_type::request_url,request_.get_uri());
			
			return isOk;
		}
	}
}