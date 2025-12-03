/*
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
 */
#include <xercesc/util/XMLUniDefs.hpp>
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/Constants.hpp"
#include "wsdl/util/DOMUtils.hpp"
#include "wsdl/ext/UnknownExtensibilityElement.hpp"
#include "wsdl/soap/SOAPAddress.hpp"
#include "wsdl/soap/SOAPAddressSerializer.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

SOAPAddressSerializer::SOAPAddressSerializer()
{
}

SOAPAddressSerializer::~SOAPAddressSerializer()
{
}

ExtensibilityElementPtr SOAPAddressSerializer::unmarshall(
        QNamePtr parentType, QNamePtr elementType, 
        DOMElement* el, 
        DefinitionsPtr def, 
        ExtensionRegistryPtr extReg) throw (WSDLException)
{
    //SOAPAddressPtr eePtr(extReg->createExtension(parentType, elementType));
    ExtensibilityElementPtr eePtr(extReg->createExtension(parentType, elementType));
                                                                  
    XMLChString locationURI = DOMUtils::getAttribute(el, Constants::ATTR_LOCATION);
    if ( locationURI != null )
    {
        ((SOAPAddress*)eePtr.get())->setLocationURI(locationURI);
    }

    XMLChString requiredStr = DOMUtils::getAttributeNS(el,
                                                 Constants::NS_URI_WSDL,
                                                 Constants::ATTR_REQUIRED);
    if ( requiredStr != null ) 
    {
        eePtr->setRequired(XMLBOOL(requiredStr.c_str()));
    }
    
    //ExtensibilityElementPtr ret(theSoapAddress.get());

    return eePtr;
}


WSDL_NAMESPACE_END

