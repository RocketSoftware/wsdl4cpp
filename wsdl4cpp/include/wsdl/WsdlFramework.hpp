/*
 * %fv: WsdlFramework.hpp-2 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#ifndef WSDLFRAMEWORK_HPP_
#define WSDLFRAMEWORK_HPP_
#include "wsdl/wsdlbas.hpp"
#include <xercesc/util/XMLException.hpp>

WSDL_NAMESPACE_BEGIN

class WSDL_EXPORT WsdlFramework
{
public:
	WsdlFramework(const char* const locale = 0, bool recognizeNEL = false)
		throw(XERCES_CPP_NAMESPACE_QUALIFIER XMLException);
	virtual ~WsdlFramework();
};

DEFINE_PTR(WsdlFramework);

//const XMLCh *Constants::ATTR_NAME  = XMLCHPTR("name");

WSDL_NAMESPACE_END


#endif /*WSDLFRAMEWORK_HPP_*/
