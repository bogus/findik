/*
  Copyright (C) 2008 Burak OGUZ (barfan) <findikmail@gmail.com>

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
	namespace util {

		log4cxx::LoggerPtr tidy_html_parser::debug_logger(log4cxx::Logger::getLogger("findik.util.tidy_html_parser"));
		tidy_html_parser::tidy_html_parser()
		{
		}

		tidy_html_parser::~tidy_html_parser()
		{
			tdoc.Release();
		}

		void tidy_html_parser::parse(std::vector<char> content)
		{
			LOG4CXX_DEBUG(debug_logger, "HTML Parsing started");
			int rc = -1;
			Bool ok;
			// initiate error buffer
			Tidy::BufferSink errbuf;	

			// create a Tidy document
			tdoc.Create();

			// no xhtml output for performance reasons
			ok = tdoc.OptSetBool(TidyXhtmlOut, no);
			ok = tdoc.OptSetBool(TidyHtmlOut, yes);

			// set error buffer for Tidy Document
			if( ok )
				rc = tdoc.SetErrorSink(errbuf);
			// parse string for Tidy Document
			if ( rc >= 0 )  
				rc = tdoc.ParseString(&content[0]);
			// clean and repair the taken content and prepare for traverse
			if ( rc >= 0 )
				rc = tdoc.CleanAndRepair();

			errbuf.Free();

			// traverse Tidy Document and take text parts
			this->dumpDoc();
			LOG4CXX_DEBUG(debug_logger, "HTML Parsing ended");
		}

		std::string tidy_html_parser::get_clear_text()
		{
			return clear_text;
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
						clear_text.append((char *)buffer.Data());
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

		void tidy_html_parser::dumpDoc()
		{
			dumpNode(tdoc.GetRoot());
		}
	}
}
