#include "response_filter.hpp"

namespace findik {
	namespace filter {

		response_filter::response_filter(persistency::dbmanager::pointer & manager, io::response & response):
			manager_(manager), response_(response)
		{
			
		}

		response_filter::~response_filter(void)
		{
		}

		bool response_filter::response_chain_filter()
		{
			response_filter_factory_iter it = response_filter_factory_map().begin();
                        bool isOk = true;

                        while((it != response_filter_factory_map().end()) && (isOk == true))
                        {
                                abstract_response_filter * resp_filter = (*it).second(manager_,response_) ;
                                isOk = resp_filter->filter();
                                reply_string = resp_filter->get_reply();
                                delete resp_filter ;
                                it++;
                        }

                        return isOk;

		}

		std::string response_filter::get_reply_string()
                {
                        return reply_string;
                }


	}
}
