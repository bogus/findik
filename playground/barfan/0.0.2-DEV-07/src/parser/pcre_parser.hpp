#ifndef FINDIK_PARSER_PCRE_PARSER_HPP
#define FINDIK_PARSER_PCRE_PARSER_HPP

#include <pcrecpp.h>
#include <iostream>
#include <vector>

namespace findik {
	namespace parser {
	
		class pcre_parser
		{
		public:
			pcre_parser();
			~pcre_parser();
			pcre_parser(int category_id_, std::string & pattern_);
			pcre_parser(pcre_parser const &pcre_parser_);
			pcrecpp::RE * get_re();
			void set_re(pcrecpp::RE *re_);
			int get_category_id();
			void set_category_id(int category_id_);
			
		private:
			pcrecpp::RE * re_;
			int category_id_;
			pcrecpp::RE_Options *options_;
		};
		
		static std::vector<pcre_parser *> re_vector;
		
		std::vector<pcre_parser *> & get_re_vector();

		void generate_pcre_vector();	
	}	
}


#endif
