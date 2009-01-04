noinst_LTLIBRARIES		=	libfindik_parser.la

libfindik_parser_la_SOURCES	= \
	tidy_html_parser.cpp \
	magic_number_parser.cpp \
	pcre_parser.cpp

libfindik_parser_la_LIBADD	=	@LTLIBOBJS@

INCLUDES = \
        -I@top_srcdir@/src/persistency \
        -I@top_srcdir@/src/config \
        -I@top_srcdir@/src/logging 
