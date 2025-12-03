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
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/soap/SOAPBinding.hpp"
#include "wsdl/soap/SOAPBindingSerializer.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

SOAPBindingSerializer::SOAPBindingSerializer()
{
}

SOAPBindingSerializer::~SOAPBindingSerializer()
{
}

ExtensibilityElementPtr SOAPBindingSerializer::unmarshall(
        QNamePtr parentType, QNamePtr elementType, 
        DOMElement* el, 
        DefinitionsPtr def, 
        ExtensionRegistryPtr extReg) throw (WSDLException)
{
    //SOAPBindingPtr eePtr(extReg->createExtension(parentType, elementType));
    ExtensibilityElementPtr eePtr(extReg->createExtension(parentType, elementType));
                                                                  
    XMLChString transportURI = DOMUtils::getAttribute(el, 
                                    SOAPConstants::ATTR_TRANSPORT);
    if (transportURI != null) 
    {
        ((SOAPBinding*)eePtr.get())->setTransportURI(transportURI);
    }

    XMLChString style = DOMUtils::getAttribute(el, 
                                    SOAPConstants::ATTR_STYLE);
    if (style != null) 
    {
        ((SOAPBinding*)eePtr.get())->setStyle(style);
    }

    XMLChString requiredStr = DOMUtils::getAttributeNS(el,
                                                 Constants::NS_URI_WSDL,
                                                 Constants::ATTR_REQUIRED);
    if (requiredStr != null) 
    {
        eePtr->setRequired(XMLBOOL(requiredStr.c_str()));
    }
    
    //ExtensibilityElementPtr ret(theSoapAddress.get());

    return eePtr;
}


WSDL_NAMESPACE_END

