noinst_LTLIBRARIES		=	libfindik_service.la

libfindik_service_la_SOURCES	= \
	filter_service.cpp \
	parser_service.cpp \
	service_chain_element.cpp \
	service_container.cpp \
	session_service.cpp

libfindik_service_la_LIBADD	=	@LTLIBOBJS@

INCLUDES 			= \
        -I@top_srcdir@/src/config \
        -I@top_srcdir@/src/io \
        -I@top_srcdir@/src/filter \
        -I@top_srcdir@/src/parser

