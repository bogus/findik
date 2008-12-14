#include "response_filter.hpp"

namespace findik {

	response_filter::response_filter(dbmanager *manager_,io::response *response_)
	{
	}

	response_filter::~response_filter(void)
	{
	}

	bool response_filter::response_chain_filter()
	{
		if(response_content_type_filter() &&
			response_content_filter())
			return true;

		return false;
	}

	bool response_filter::response_content_filter()
	{
		return true;
	}

	bool response_filter::response_content_type_filter()
	{
		return true;
	}

}
