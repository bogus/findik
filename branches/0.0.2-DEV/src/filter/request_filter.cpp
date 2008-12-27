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
			request_filter_factory_iter it = request_filter_factory_map().begin();
			bool isOk = true;
			
			while((it != request_filter_factory_map().end()) && (isOk == true))
			{
				abstract_request_filter * req_filter = (*it).second(manager_,request_) ;
				isOk = req_filter->filter();
				reply_string = req_filter->get_reply();
				delete req_filter ;
				it++;
			}
			
			return isOk;
			
		}

		std::string request_filter::get_reply_string()
		{
			return reply_string;
		}
	}
}

