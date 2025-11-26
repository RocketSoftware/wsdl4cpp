/*
 * %fv: WsdlFramework.hpp-2 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
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
