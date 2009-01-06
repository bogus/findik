#include "magic_number_parser.hpp"

namespace findik {
        namespace parser {

		magic_number_parser::magic_number_parser()
		{
			
		}
                magic_number_parser::~magic_number_parser()
		{
			mime_type.clear();	
		}
                std::string magic_number_parser::get_magic_mime_type(const char *magic_buf,int length)	
		{
			magic_t magic_mime = 0;
			magic_mime = magic_open( MAGIC_MIME );
			if( !magic_mime ){
				LOG4CXX_DEBUG(debug_logger, "magic_t could not opened");
				magic_close(magic_mime);
				return mime_type;
			}
			int rc = magic_load( magic_mime, 0 );
			if( rc == -1) {
				LOG4CXX_DEBUG(debug_logger, "magic_t could not loaded");
				magic_close(magic_mime);
				return mime_type;
			}
			if(magic_buffer == NULL){
				LOG4CXX_DEBUG(debug_logger, "content null");
				magic_close(magic_mime);
                                return mime_type;
			}

			if(length > 0)
			{
				mime_type = magic_buffer( magic_mime, magic_buf, length );
				magic_close(magic_mime);
				return mime_type;
			}
			else
			{
				LOG4CXX_DEBUG(debug_logger, "no content");
				magic_close(magic_mime);
				return mime_type;
			}

		}

		log4cxx::LoggerPtr magic_number_parser::debug_logger(log4cxx::Logger::getLogger("findik.parser.magic_mime_type"));
	}
}
