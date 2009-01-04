noinst_LTLIBRARIES			=	libfindik_persistency.la

libfindik_persistency_la_SOURCES	= \
	dbconnection.cpp \
	mysqldbmanager.cpp \
	pooled_dbmanager.cpp

libfindik_persistency_la_LIBADD		=	@LTLIBOBJS@

INCLUDES = \
        -I@top_srcdir@/src/config \
        -I@top_srcdir@/src/parser \
        -I@top_srcdir@/src/logging
