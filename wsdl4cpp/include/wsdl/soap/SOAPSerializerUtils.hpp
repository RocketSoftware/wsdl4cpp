/*
 * %fv:SOAPSerializerUtils.hpp-2 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
/*
 * From release 1.0.0, WSDL4CPP is under the Eclipse Public License - v 2.0 (EPL 2.0)
 */
#ifndef SOAPSERIALIZERUTILS_HPP_
#define SOAPSERIALIZERUTILS_HPP_
#include <xercesc/dom/DOMElement.hpp>

#include "wsdl/wsdlbas.hpp"
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/Definitions.hpp"
#include "wsdl/soap/SOAPBodyBasic.hpp"
#include "wsdl/soap/SOAPHeaderBasic.hpp"

WSDL_NAMESPACE_BEGIN

class WSDL_EXPORT SOAPSerializerUtils
{
public:
    static void unmarshallBodyBasic(SOAPBodyBasicPtr eePtr, 
        XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el);
    
    static void unmarshallHeaderBasic(SOAPHeaderBasicPtr eePtr, 
        XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el, DefinitionsPtr def);
    
};

WSDL_NAMESPACE_END

#endif /*SOAPSERIALIZERUTILS_HPP_*/
