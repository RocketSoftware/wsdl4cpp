/*
 * %fv:SOAPHeaderSerializer.cpp-3 % 
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
 */
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/Constants.hpp"
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/soap/SOAPHeader.hpp"
#include "wsdl/soap/SOAPHeaderSerializer.hpp"
#include "wsdl/soap/SOAPSerializerUtils.hpp"
#include "wsdl/util/DOMUtils.hpp"
#include "wsdl/util/StringUtils.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

SOAPHeaderSerializer::SOAPHeaderSerializer()
{
}

SOAPHeaderSerializer::~SOAPHeaderSerializer()
{
}

ExtensibilityElementPtr SOAPHeaderSerializer::unmarshall(
        QNamePtr parentType, QNamePtr elementType, 
        DOMElement* el, 
        DefinitionsPtr def, 
        ExtensionRegistryPtr extReg) throw (WSDLException)
{
	ExtensibilityElementPtr eePtr0(extReg->createExtension(parentType, elementType));
	
    SOAPHeaderPtr eePtr = eePtr0.downcastTo<SOAPHeader>();
                                                                  
    SOAPSerializerUtils::unmarshallHeaderBasic(eePtr, el, def);
                                                                  
    DOMElement* tempEl = DOMUtils::getFirstChildElement(el);

    while (tempEl)
    {
      if (DOMUtils::matches(SOAPConstants::Q_ELEM_SOAP_HEADER_FAULT, tempEl))
      {
        eePtr->addSOAPHeaderFault(
          parseSoapHeaderFault(SOAPConstants::Q_ELEM_SOAP_HEADER,
                               SOAPConstants::Q_ELEM_SOAP_HEADER_FAULT,
                               tempEl,
                               extReg,
                               def));
      }
      else
      {
        DOMUtils::throwWSDLException(tempEl);
      }

      tempEl = DOMUtils::getNextSiblingElement(tempEl);
    }

    return eePtr;
}

SOAPHeaderFaultPtr SOAPHeaderSerializer::parseSoapHeaderFault(
    QNamePtr parentType,
    QNamePtr elementType,
    DOMElement* el, 
    ExtensionRegistryPtr extReg, 
    DefinitionsPtr def)
    throw (WSDLException)
{
	ExtensibilityElementPtr eePtr0(extReg->createExtension(parentType, elementType));
    SOAPHeaderFaultPtr eePtr = eePtr0.downcastTo<SOAPHeaderFault>();

    SOAPSerializerUtils::unmarshallHeaderBasic(eePtr, el, def);

    return eePtr;
}

WSDL_NAMESPACE_END

