#ifndef FINDIK_PARSER_MAGIC_NUMBER_PARSER_HPP
#define FINDIK_PARSER_MAGIC_NUMBER_PARSER_HPP

#include <stdio.h>
#include <iostream>
#include <string>
#include <magic.h>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "log_initializer.hpp"

namespace findik {
        namespace parser {

                class magic_number_parser : public boost::enable_shared_from_this<magic_number_parser>
                {
                public:
			magic_number_parser();
			~magic_number_parser();

			std::string get_magic_mime_type(const char *magic_buffer, int length);	

			typedef boost::shared_ptr<magic_number_parser> pointer;
			
                private:
			std::string mime_type;

		protected:
                        static log4cxx::LoggerPtr debug_logger;		
                };

        }
}


#endif

