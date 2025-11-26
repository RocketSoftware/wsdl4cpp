/*
 * %fv:SOAPSerializerUtils.cpp-3 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
 * 
 * This file provides the implementation of some utility methods of
 * the subclass of SOAPElement.
 * 
 */
#include "wsdl/wsdlxerces.hpp"

#include <xercesc/util/XMLUniDefs.hpp>
#include "wsdl/Constants.hpp"
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/soap/SOAPSerializerUtils.hpp"
#include "wsdl/util/DOMUtils.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

void SOAPSerializerUtils::unmarshallBodyBasic(SOAPBodyBasicPtr eePtr, DOMElement* el)
{
    XMLChString use = DOMUtils::getAttribute(el, 
                                    SOAPConstants::ATTR_USE);
    if ( use != null ) {
        eePtr->setUse(use);
    }

    XMLChString encStyleStr = DOMUtils::getAttribute(el, 
                                    SOAPConstants::ATTR_ENCODING_STYLE);
    if ( encStyleStr != null ) {
        eePtr->setEncodingStyles(StringUtils::parseNMTokens(encStyleStr));
    }

    XMLChString namespaceURI = DOMUtils::getAttribute(el, 
                                    Constants::ATTR_NAMESPACE);
    if ( namespaceURI != null ) {
        eePtr->setNamespaceURI(namespaceURI);
    }

    XMLChString requiredStr = DOMUtils::getAttributeNS(el,
                                                 Constants::NS_URI_WSDL,
                                                 Constants::ATTR_REQUIRED);
    if ( requiredStr != null ) {
        eePtr->setRequired(XMLBOOL(requiredStr.c_str()));
    }
    
}

void SOAPSerializerUtils::unmarshallHeaderBasic(
    SOAPHeaderBasicPtr eePtr, DOMElement* el, DefinitionsPtr def)
{
    unmarshallBodyBasic(eePtr, el);

    QNamePtr msg =
      DOMUtils::getQualifiedAttributeValue(el,
                                          Constants::ATTR_MESSAGE,
                                          SOAPConstants::ELEM_HEADER,
                                          false,
                                          def);
    if ( msg )
    {
        eePtr->setMessage(msg);
    }
                                          
    XMLChString aPart = DOMUtils::getAttribute(el, 
                                    SOAPConstants::ATTR_PART);
    if ( aPart != null ) {
        eePtr->setPart(aPart);
    }

}

WSDL_NAMESPACE_END

