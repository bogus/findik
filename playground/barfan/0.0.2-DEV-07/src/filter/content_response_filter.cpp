#include "content_response_filter.hpp"

namespace findik {
	namespace filter {

		content_response_filter::content_response_filter(findik::persistency::dbmanager::pointer & manager, findik::io::response & response)
			: findik::filter::abstract_response_filter(manager, response)
		{
		}

		content_response_filter::~content_response_filter(void)
		{
			html_parser_->clear();			
			pcre_text_analyzed_content.clear();
		}

		bool content_response_filter::filter()
		{
			bool isOk = true;
			int magic_mime_length = response_.content().length();
			//char *magic_mime_buffer = new char[100];
			//magic_mime_length=response_.content().copy(magic_mime_buffer,100,0);
			 
			if( magic_mime_length > 0) {
				std::string mime_type = parser::magic_number_parser().get_magic_mime_type(response_.content().c_str(), magic_mime_length);
				if(mime_type.compare(0,9,"text/html") == 0) {
					LOG4CXX_DEBUG(debug_logger, "checking for html text content: " << response_.get_request().host());
					html_parser_ = parser::tidy_html_parser::pointer(new findik::parser::tidy_html_parser());
					html_parser_->create_doc(response_.content().c_str());
					html_parser_->parse_html();
					pcre_text_analyzed_content = html_parser_->get_pcre_text_analyze();
					isOk = pcre_text_analyzed_content.empty();
					if(!isOk) {
						std::map<std::string, int>::const_iterator iter = pcre_text_analyzed_content.begin();
						for( ; iter != pcre_text_analyzed_content.end() ; iter++ )
							LOG4CXX_WARN(logging::log_initializer::filter_logger, iter->first << " found " << iter->second << " times" << " CONTENT REGEX BLOCKED");
						filter_report_->generate_report(filter_report::response_content,this->generate_report_data());
					}
					html_parser_->clear();
					pcre_text_analyzed_content.clear();
				}
				mime_type.clear();
				}
			//delete magic_mime_buffer;
			return isOk;
		}
		findik::filter::abstract_response_filter *content_response_filter::construct(persistency::dbmanager::pointer & manager, io::response & response)
		{
			return new content_response_filter(manager,response);
		}

		std::string content_response_filter::generate_report_data()
		{
				std::ostringstream stm;
				stm << ID;
				std::string report_data;
				report_data = "Reason : ";
				report_data += "Content : ";
				std::map<std::string, int>::const_iterator iter = pcre_text_analyzed_content.begin();
				for( ; iter != pcre_text_analyzed_content.end() ; iter++ )
				{
					report_data += iter->first;
					report_data += " found ";
					std::ostringstream stm_occ;
					stm_occ << iter->second;
					report_data += stm_occ.str();
					report_data += " times, ";

				}
				report_data += " is banned by FINDIK, code : ";
				report_data += stm.str();
				return report_data;
		}		

			log4cxx::LoggerPtr content_response_filter::debug_logger(log4cxx::Logger::getLogger("findik.filter.content_response_filter"));
		}
	}
