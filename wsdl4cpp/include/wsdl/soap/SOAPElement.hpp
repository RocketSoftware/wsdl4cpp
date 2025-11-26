/*
 * %fv:SOAPElement.hpp-3 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
 */
#ifndef SOAPELEMENT_HPP_
#define SOAPELEMENT_HPP_
#include <list>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/QName.hpp"
#include "wsdl/ext/ExtensibilityElement.hpp"

WSDL_NAMESPACE_BEGIN

class WSDL_EXPORT SOAPElement : public ExtensibilityElement
{
public:
    static const XMLCh PREFIX[];
    static const XMLCh PREFIX_SEPARATOR[];
    
    SOAPElement(QNamePtr elementType, bool b = false)
        : ExtensibilityElement(elementType, b){}
    
    SOAPElement()
        : ExtensibilityElement(){}
    
    virtual ~SOAPElement(){};

	virtual XMLChString toString();
    
	
};

WSDL_NAMESPACE_END

#endif /*SOAPELEMENT_HPP_*/
