#include "url_request_filter.hpp"

namespace findik {
	namespace filter {
		
		url_request_filter::url_request_filter(findik::persistency::dbmanager::pointer & manager, findik::io::request & request)
			: findik::filter::abstract_request_filter(manager, request)
		{
		}

		url_request_filter::~url_request_filter(void)
		{
		}

		bool url_request_filter::filter()
		{
			bool isOk = manager_->urlQuery(request_.get_uri());
			if(!isOk) {
				filter_report_->generate_report(filter_report::reason_type::request_url,request_.get_uri());
			}
			return isOk;
		}

		findik::filter::abstract_request_filter *url_request_filter::construct(persistency::dbmanager::pointer & manager, io::request & request)
		{
			return new url_request_filter(manager,request);
		}
		
	}
}