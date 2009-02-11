noinst_LTLIBRARIES		=	libfindik_util.la

libfindik_util_la_SOURCES	= \
	pcre_analyzer.cpp \
	pcre_parser.cpp \
	tidy_html_parser.cpp

libfindik_util_la_LIBADD	=	@LTLIBOBJS@

INCLUDES 			= \
	-I@top_srcdir@/src/include/config \
	-I@top_srcdir@/src/include/filter \
	-I@top_srcdir@/src/include/io \
	-I@top_srcdir@/src/include/logging \
	-I@top_srcdir@/src/include/parser \
	-I@top_srcdir@/src/include/persistency \
	-I@top_srcdir@/src/include/service \
	-I@top_srcdir@/src/include/util \
	-I/usr/include/mysql

