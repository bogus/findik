#SUBDIRS = filter io parser service

noinst_PROGRAMS			=	findik_test

findik_test_SOURCES		=	findik_test.cpp

findik_test_LDADD		= \
	../main/libfindik.la 

LIBS = \
	-lboost_thread \
	-lboost_system \
	-lpthread \
	-lz 

