/*
 * %fv:SOAPElement.hpp-3 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
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
