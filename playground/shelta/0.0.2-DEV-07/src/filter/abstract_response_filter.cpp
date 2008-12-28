#include "abstract_response_filter.hpp"

namespace findik {
	namespace filter {
		abstract_response_filter::~abstract_response_filter(void)
		{
		}

		abstract_response_filter::abstract_response_filter(persistency::dbmanager::pointer & manager, io::response & response):
			manager_(manager), response_(response)
		{
			filter_report_ = filter_report::pointer(new filter_report());
		}

		std::string abstract_response_filter::get_reply()
		{
			return filter_report_->get_reply_result();
		}
	}
}

