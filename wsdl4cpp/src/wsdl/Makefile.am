INCLUDES = -I$(top_srcdir)/include -I$(XERCESC_HOME)/include -I$(CURL_HOME)/include $(all_includes)
METASOURCES = AUTO

lib_LTLIBRARIES = libwsdl4cpp.la
libwsdl4cpp_la_LDFLAGS= -avoid-version

libwsdl4cpp_la_LIBADD =  -L$(XERCESC_HOME)/lib -L$(CURL_HOME)/lib -L$(OPENSSL_HOME)/lib

libwsdl4cpp_la_SOURCES = Binding.cpp BindingFault.cpp BindingInput.cpp\
	BindingOperation.cpp BindingOutput.cpp Constants.cpp Definitions.cpp\
	WsdlFramework.cpp Fault.cpp Import.cpp Input.cpp\
	Message.cpp NamedElement.cpp Operation.cpp OperationType.cpp Output.cpp\
	Param.cpp Part.cpp Port.cpp PortType.cpp QName.cpp Service.cpp Types.cpp\
	WsdlErrorHandler.cpp WSDLException.cpp WsdlReader.cpp wsdlxerces.cpp \
	ext/AttributeExtensible.cpp ext/ElementExtensible.cpp\
        ext/ExtensibilityAttribute.cpp ext/ExtensibilityElement.cpp\
	ext/ExtensionRegistry.cpp ext/UnknownExtensibilityElement.cpp\
	ext/UnknownExtensionDeserializer.cpp\
	schema/SchemaConstants.cpp schema/Schema.cpp schema/SchemaDeserializer.cpp\
	schema/SchemaModel.cpp\
	soap/SOAPAddressSerializer.cpp soap/SOAPBindingSerializer.cpp\
	soap/SOAPBodySerializer.cpp soap/SOAPElement.cpp\
	soap/SOAPFaultSerializer.cpp soap/SOAPHeaderSerializer.cpp\
	soap/SOAPOperationSerializer.cpp soap/SOAPSerializerUtils.cpp\
	soap/SOAPConstants.cpp\
	util/DOMUtils.cpp \
	util/StringUtils.cpp util/XercesUtils.cpp\
	util/SOAPEncodingUtils.cpp

XCURL_SRC = ../xcurl/CurlInputSource.cpp ../xcurl/CurlInputSourceBuilder.cpp \
        ../xcurl/CurlInputStream.cpp
        
if XCURL

AM_CPPFLAGS=-DWSDL_USE_CURL

libwsdl4cpp_la_LIBADD +=  -lxerces-c-3.2 -l$(CURLLIBNAME)
	
libwsdl4cpp_la_SOURCES += $(XCURL_SRC)

else

	libwsdl4cpp_la_LIBADD +=  -lxerces-c

endif
