#include "pcre_parser.hpp"

namespace findik {
	namespace parser {
		
		pcre_parser::pcre_parser()
                {
                }
		pcre_parser::~pcre_parser()
		{
		}
		pcre_parser::pcre_parser(int category_id_, std::string pattern_) 
		{
			pcrecpp::RE_Options options;
			options.set_caseless(true);
			options.set_extra(true);
                        options.set_extended(true);
			this->category_id_ = category_id_;
			this->re_ = new pcrecpp::RE(pattern_, options);
		}
		pcre_parser::pcre_parser(pcre_parser const &pcre_parser_)
		{
			
		}
		pcrecpp::RE * pcre_parser::get_re()
		{
			return this->re_;
		}
		void pcre_parser::set_re(pcrecpp::RE * re_)
		{
			this->re_ = re_;
		}	
		int pcre_parser::get_category_id()
		{
			return category_id_;
		}
		void pcre_parser::set_category_id(int category_id_)
		{
			this->category_id_ = category_id_;
		}
		
		void generate_pcre_vector()
		{
			std::cout << "++++++++++++++++++++++++++++++++++" << std::endl;
			std::string re_str = "(adultsight|adultsite|adultsonly|adultweb|blowjob|bondage|centerfold|cumshot|cyberlust|cybercore|hardcore|incest|masturbat|obscene|pedophil|pedofil|playmate|pornstar|sexdream|softcore|striptease)";
			int cat_id = 1;
			re_vector.push_back(pcre_parser(cat_id,re_str));
			std::cout << "VECTOR SIZE : " << re_vector.size() << std::endl;		
		}

		std::vector<pcre_parser> & get_re_vector()
		{
			return re_vector;
		}
	}
}
