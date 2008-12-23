#include "abstract_request_filter.hpp"

namespace findik {
	namespace filter {
		abstract_request_filter::~abstract_request_filter(void)
		{	
		}

		abstract_request_filter::abstract_request_filter(persistency::dbmanager::pointer & manager, io::request & request):
			manager_(manager), request_(request)
		{
			filter_report_ = filter_report::pointer(new filter_report());
		}
	
		std::string abstract_request_filter::get_reply()
		{
			return filter_report_->get_reply_result();
		}
		/*
		bool request_filter::request_content_filter()
		{
			return true;
		}

		bool request_filter::request_url_filter()
		{
			
		}
		*/
	}
}

