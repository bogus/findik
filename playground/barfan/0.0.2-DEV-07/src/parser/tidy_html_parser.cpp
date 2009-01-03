/*
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "tidy_html_parser.hpp"

namespace findik {
	namespace parser {

		tidy_html_parser::tidy_html_parser(void)
		{
		}

		tidy_html_parser::~tidy_html_parser(void)
		{
			this->parsed_content.clear();
			tdoc.Release();
			pcre_text_analyzed_content.clear();	
		}

		void tidy_html_parser::clear()
		{
			this->parsed_content.clear();
			tdoc.Release();
			pcre_text_analyzed_content.clear();	
		}

		std::string &tidy_html_parser::get_content()
		{
			return this->parsed_content;
		}

		void tidy_html_parser::create_doc(const char* html_content)
		{
			int rc = -1;
			Bool ok;
		 	Tidy::BufferSink errbuf;	

			tdoc.Create();
			ok = tdoc.OptSetBool(TidyXhtmlOut, no);
			ok = tdoc.OptSetBool(TidyHtmlOut, yes);
			if( ok )
				rc = tdoc.SetErrorSink(errbuf);
			if ( rc >= 0 ) 
				rc = tdoc.ParseString(html_content);
			if ( rc >= 0 )
				rc = tdoc.CleanAndRepair();

			errbuf.Free();

		}

		void tidy_html_parser::parse_html()
		{
			this->dumpDoc();
		}

		std::map<std::string,int> & tidy_html_parser::get_pcre_text_analyze() 
		{
			pcrecpp::StringPiece *input = new pcrecpp::StringPiece(parsed_content);
			std::string match;

			for( int i = 0; i < parser::get_re_vector().size(); i++ ) {
				while(parser::get_re_vector()[i]->get_re()->FindAndConsume(input,&match)) {
					std::transform(match.begin(), match.end(), match.begin(), tolower);
					std::map<std::string, int>::const_iterator iter = pcre_text_analyzed_content.find(match);
					if(iter != pcre_text_analyzed_content.end())
						pcre_text_analyzed_content[match]++;
					else
						pcre_text_analyzed_content.insert(std::pair<std::string, int>(match, 1));
				}	
			}

			input->clear();
			match.clear();
			delete input;
			return pcre_text_analyzed_content;
		}

		void tidy_html_parser::dumpDoc()
		{
			dumpNode( tdoc.GetRoot() );
		}
	

		void tidy_html_parser::dumpNode(Tidy::Node *tnod)
		{
			Tidy::Node *child;
			Tidy::Buffer buffer;

			for ( child = tnod->Child(); child; child = child->Next() )
			{
				char * name = NULL;
				switch ( child->Type() )
				{
					/*
					case TidyNode_Root:	  name = "Root";		    break;
					case TidyNode_DocType:	  name = "DOCTYPE";		    break;
					case TidyNode_Comment:	  name = "Comment";		    break;
					case TidyNode_ProcIns:	  name = "Processing Instruction";  break;
					*/
					case TidyNode_Text:
						tdoc.GetNodeText(child, buffer);
						parsed_content.append((char *)buffer.Data());
						break;
					/*
					case TidyNode_CDATA:	  name = "CDATA";		    break;
					case TidyNode_Section:	  name = "XML Section";		    break;
					case TidyNode_Asp:	  name = "ASP";			    break;
					case TidyNode_Jste:	  name = "JSTE";		    break;
					case TidyNode_Php:	  name = "PHP";			    break;
					case TidyNode_XmlDecl:	  name = "XML Declaration";	    break;
					case TidyNode_Start:
					case TidyNode_End:
					case TidyNode_StartEnd:
					default:
					  name = tidyNodeGetName( child );
					  break;
					*/
					default:
						break;
				}
				
				dumpNode( child );
			  }
			  buffer.Free();
		}

	}
}

