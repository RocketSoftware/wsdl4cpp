/*
 * %fv:SOAPOperationSerializer.cpp-3 % 
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
#include <xercesc/util/XMLUniDefs.hpp>
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/Constants.hpp"
#include "wsdl/util/DOMUtils.hpp"
#include "wsdl/ext/UnknownExtensibilityElement.hpp"
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/soap/SOAPOperation.hpp"
#include "wsdl/soap/SOAPOperationSerializer.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

SOAPOperationSerializer::SOAPOperationSerializer()
{
}

SOAPOperationSerializer::~SOAPOperationSerializer()
{
}

ExtensibilityElementPtr SOAPOperationSerializer::unmarshall(
        QNamePtr parentType, QNamePtr elementType, 
        DOMElement* el, 
        DefinitionsPtr def, 
        ExtensionRegistryPtr extReg) throw (WSDLException)
{
    //SOAPOperationPtr eePtr(extReg->createExtension(parentType, elementType));
    ExtensibilityElementPtr eePtr(extReg->createExtension(parentType, elementType));
                                                                  
    XMLChString soapActionURI = DOMUtils::getAttribute(el, 
                                    SOAPConstants::ATTR_SOAP_ACTION);
    if ( soapActionURI != null )
    {
        ((SOAPOperation*)eePtr.get())->setSoapActionURI(soapActionURI);
    }

    XMLChString style = DOMUtils::getAttribute(el, 
                                    SOAPConstants::ATTR_STYLE);
    if ( style != null )
    {
        ((SOAPOperation*)eePtr.get())->setStyle(style);
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

