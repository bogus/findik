bin_PROGRAMS		= importer

	

importer_SOURCES	= \
			main.cpp\
			importer_tool.cpp\
			configuration.cpp\
			mysqldbmanager.cpp


LIBS = \
	-lboost_system \
	-lboost_thread \
	-lboost_program_options \
	-llog4cxx \
	-lconfig++ \
	-lmysqlpp\
	-lboost_filesystem

INCLUDES = \
	-I@top_srcdir@/ \ 
	-I/usr/include/mysql

