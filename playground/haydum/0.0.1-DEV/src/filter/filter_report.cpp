#include "filter_report.hpp"

namespace findik {
	namespace filter {

		filter_report::filter_report(void)
		{
		}

		filter_report::~filter_report(void)
		{
			reply_result.clear();
		}

		std::string filter_report::get_reply_result()
		{
			return reply_result;
		}

		void filter_report::generate_report(reason_type reason, std::string data)
		{	
			reply_result += message_top;
			reply_result += newline;
			reply_result += "Reason : ";
			switch(reason) {
				case request_domain:
					reply_result += "Domain : "; 
					reply_result += data; 
					reply_result += " is banned by FINDIK, code : 1";
					break;
				case request_url:
					reply_result += "URL : ";
					reply_result += data;
					reply_result += " is banned by FINDIK, code : 2";
					break;
				case request_content:
					reply_result += "Content : "; 
					reply_result += data; 
					reply_result += " is banned by FINDIK, code : 3";
					break;
				case response_content:
					reply_result += "Content : "; 
					reply_result += data; 
					reply_result += " is banned by FINDIK, code : 100";
					break;
				case response_content_type:
					reply_result += "Content-Type : "; 
					reply_result += data; 
					reply_result += " is banned by FINDIK, code : 101";
					break;
			}
			reply_result += newline;
			reply_result += message_bottom;
	
		}
	}
}