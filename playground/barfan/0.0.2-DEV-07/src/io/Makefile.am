noinst_LTLIBRARIES		=	libfindik_io.la

libfindik_io_la_SOURCES		= \
	connection.cpp \
	mime_types.cpp \
	reply.cpp \
	request.cpp \
	request_parser.cpp \
	response.cpp \
	response_parser.cpp \
	server.cpp

libfindik_io_la_LIBADD		=	@LTLIBOBJS@

INCLUDES 			= \
        -I@top_srcdir@/src/config \
        -I@top_srcdir@/src/filter \
        -I@top_srcdir@/src/logging \
        -I@top_srcdir@/src/parser \
        -I@top_srcdir@/src/persistency
