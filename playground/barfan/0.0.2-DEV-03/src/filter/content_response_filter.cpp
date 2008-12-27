#include "content_response_filter.hpp"

namespace findik {
	namespace filter {
		
		content_response_filter::content_response_filter(findik::persistency::dbmanager::pointer & manager, findik::io::response & response)
			: findik::filter::abstract_response_filter(manager, response)
		{
		}

		content_response_filter::~content_response_filter(void)
		{
		}

		bool content_response_filter::filter()
		{
			bool isOk = true; 
			return isOk;
		}
		findik::filter::abstract_response_filter *content_response_filter::construct(persistency::dbmanager::pointer & manager, io::response & response)
		{
			return new content_response_filter(manager,response);
		}

		
	}
}
