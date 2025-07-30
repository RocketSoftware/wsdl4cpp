/*
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
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
