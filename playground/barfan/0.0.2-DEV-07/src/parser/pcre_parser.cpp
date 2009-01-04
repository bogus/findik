#include "pcre_parser.hpp"

namespace findik {
	namespace parser {
		
		pcre_parser::pcre_parser()
                {
                }
		pcre_parser::~pcre_parser()
		{
		}
		pcre_parser::pcre_parser(int category_id_, std::string & pattern_) 
		{
			options_ = new pcrecpp::RE_Options();
			options_->set_caseless(true);
			options_->set_extra(true);
                        options_->set_extended(true);
                        options_->set_multiline(true);
			this->category_id_ = category_id_;
			this->re_ = new pcrecpp::RE(pattern_, *options_);
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
			return this->category_id_;
		}
		void pcre_parser::set_category_id(int category_id_)
		{
			this->category_id_ = category_id_;
		}
		
		std::vector<pcre_parser *> & get_re_vector()
		{
			return re_vector;
		}
		
		void generate_pcre_parser()
		{
			std::map<int,std::string> pcre_map;
			findik::persistency::dbmanager::pointer dbmanager_(new findik::persistency::mysqldbmanager());
			dbmanager_->pcreQuery(pcre_map);
			for(std::map<int,std::string>::iterator iter = pcre_map.begin(); iter != pcre_map.end(); iter++)
			{
				get_re_vector().push_back(new pcre_parser(iter->first,iter->second));
			}
		}
	}
}
