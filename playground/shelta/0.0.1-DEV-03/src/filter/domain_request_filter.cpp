#include "domain_request_filter.hpp"

namespace findik {
	namespace filter {
		
		domain_request_filter::domain_request_filter(findik::persistency::dbmanager::pointer & manager, findik::io::request & request)
			: findik::filter::abstract_request_filter(manager, request)
		{
		}

		domain_request_filter::~domain_request_filter(void)
		{
		}

		bool domain_request_filter::filter()
		{
			bool isOk = manager_->domainQuery(request_.host());
			if(!isOk) {
				LOG4CXX_WARN(log_initializer::filter_logger, request_.host() << " DOMAIN BLOCKED");
				filter_report_->generate_report(filter_report::request_domain,request_.host());
			}
			return isOk;
		}
		findik::filter::abstract_request_filter *domain_request_filter::construct(persistency::dbmanager::pointer & manager, io::request & request)
		{
			return new domain_request_filter(manager,request);
		}
		
	}
}
