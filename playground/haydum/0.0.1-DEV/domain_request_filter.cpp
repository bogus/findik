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
				std::cout << request_.host() << std::endl;
				filter_report_->generate_report(filter_report::reason_type::request_domain,request_.host());
			}
			return isOk;
		}
		findik::filter::abstract_request_filter *domain_request_filter::construct(persistency::dbmanager::pointer & manager, io::request & request)
		{
			return new domain_request_filter(manager,request);
		}
		
	}
}