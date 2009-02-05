noinst_LTLIBRARIES		=	libfindik_http.la

libfindik_http_la_SOURCES	= \
	data.cpp \
	request.cpp \
	request_parser.cpp \
	response.cpp \
	response_parser.cpp \
	domain_filter.cpp \
	tidy_html_parser.cpp

libfindik_http_la_LIBADD	=	@LTLIBOBJS@

INCLUDES 			= \
	-I@top_srcdir@/src/include/config \
	-I@top_srcdir@/src/include/filter \
	-I@top_srcdir@/src/include/io \
	-I@top_srcdir@/src/include/logging \
	-I@top_srcdir@/src/include/parser \
	-I@top_srcdir@/src/include/protocols/http \
	-I@top_srcdir@/src/include/service 

