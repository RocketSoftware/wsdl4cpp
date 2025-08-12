INCLUDES = -I$(top_srcdir)/src/test -I$(top_srcdir)/include \
	-I$(XERCESC_HOME)/include $(all_includes)
METASOURCES = AUTO
noinst_PROGRAMS = wsdltest


if XCURL
wsdltest_LDADD = $(top_builddir)/src/wsdl/libwsdl4cpp.la \
	-L$(XERCESC_HOME)/lib -lxerces-c-3.2 -L$(CURL_HOME)/lib -l$(CURLLIBNAME) -L$(OPENSSL_HOME)/lib -lssl -lcrypto
else
wsdltest_LDADD = $(top_builddir)/src/wsdl/libwsdl4cpp.la \
	-L$(XERCESC_HOME)/lib -lxerces-c
endif




wsdltest_SOURCES = WsdlTest.cpp
