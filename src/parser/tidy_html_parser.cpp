#include "tidy_html_parser.hpp"

namespace findik {
	namespace parser {

		tidy_html_parser::tidy_html_parser(void)
		{
			parsed_content = new std::string();
		}

		tidy_html_parser::~tidy_html_parser(void)
		{
			
		}

		void tidy_html_parser::clear()
		{
			delete this->parsed_content;
			tidyRelease( this->tdoc );
		}

		std::string * tidy_html_parser::get_content()
		{
			return this->parsed_content;
		}

		void tidy_html_parser::create_doc(const char* html_content)
		{
			int rc = -1;
			Bool ok;
			TidyBuffer errbuf;

			tidyBufInit( &errbuf );

			this->tdoc = tidyCreate();
			ok = tidyOptSetBool( tdoc, TidyXhtmlOut, yes );

			if( ok )
				rc = tidySetErrorBuffer( tdoc, &errbuf);      // Capture diagnostics*/
			if ( rc >= 0 )
				rc = tidyParseString( tdoc, html_content );           // Parse the input
			if ( rc >= 0 )
				rc = tidyCleanAndRepair( tdoc );               // Tidy it up!

			tidyBufFree( &errbuf );
			
		}

		void tidy_html_parser::parse_html()
		{
			this->dumpDoc();
		}
		
		void tidy_html_parser::dumpDoc()
		{
			dumpNode( tidyGetRoot(this->tdoc) );
		}

		void tidy_html_parser::dumpNode(TidyNode tnod)
		{
			TidyNode child;
			TidyBuffer buffer;

			tidyBufInit(&buffer);

			for ( child = tidyGetChild(tnod); child; child = tidyGetNext(child) )
			{
				char * name = NULL;
				switch ( tidyNodeGetType(child) )
				{
					/*
					case TidyNode_Root:       name = "Root";                    break;
					case TidyNode_DocType:    name = "DOCTYPE";                 break;
					case TidyNode_Comment:    name = "Comment";                 break;
					case TidyNode_ProcIns:    name = "Processing Instruction";  break;
					*/
					case TidyNode_Text: 
					tidyNodeGetText(this->tdoc,child,&buffer);      
					parsed_content->append((char *)buffer.bp);                    
					break;
					/*
					case TidyNode_CDATA:      name = "CDATA";                   break;
					case TidyNode_Section:    name = "XML Section";             break;
					case TidyNode_Asp:        name = "ASP";                     break;
					case TidyNode_Jste:       name = "JSTE";                    break;
					case TidyNode_Php:        name = "PHP";                     break;
					case TidyNode_XmlDecl:    name = "XML Declaration";         break;
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
				//assert( name != NULL);
				dumpNode( child );
			  }
			  tidyBufFree(&buffer);
		}

	}
}

