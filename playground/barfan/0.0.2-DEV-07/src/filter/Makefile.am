noinst_LTLIBRARIES		=	libfindik_filter.la

libfindik_filter_la_SOURCES	= \
	abstract_request_filter.cpp \
	domain_request_filter.cpp \
	domain_pcre_request_filter.cpp \
	filter_report.cpp \
	request_filter.cpp \
	request_filter_factory_impl.cpp \
	response_filter.cpp \
	url_request_filter.cpp \
	url_pcre_request_filter.cpp \
	content_response_filter.cpp \
	abstract_response_filter.cpp \
	response_filter_factory_impl.cpp

libfindik_filter_la_LIBADD	=	@LTLIBOBJS@

INCLUDES			= \
	-I@top_srcdir@/src/config \
	-I@top_srcdir@/src/io \
	-I@top_srcdir@/src/logging \
	-I@top_srcdir@/src/parser \
	-I@top_srcdir@/src/persistency
