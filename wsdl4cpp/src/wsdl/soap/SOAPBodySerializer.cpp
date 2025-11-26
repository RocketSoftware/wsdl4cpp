/*
 * %fv:SOAPBodySerializer.cpp-4 % 
 * 
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
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/soap/SOAPBody.hpp"
#include "wsdl/soap/SOAPBodySerializer.hpp"
#include "wsdl/soap/SOAPSerializerUtils.hpp"
#include "wsdl/util/DOMUtils.hpp"
#include "wsdl/util/StringUtils.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

SOAPBodySerializer::SOAPBodySerializer()
{
}

SOAPBodySerializer::~SOAPBodySerializer()
{
}

ExtensibilityElementPtr SOAPBodySerializer::unmarshall(
        QNamePtr parentType, QNamePtr elementType, 
        DOMElement* el, 
        DefinitionsPtr def, 
        ExtensionRegistryPtr extReg) throw (WSDLException)
{
    //SOAPBodyPtr eePtr(extReg->createExtension(parentType, elementType));
    ExtensibilityElementPtr eePtr(extReg->createExtension(parentType, elementType));
                                                                  
    SOAPSerializerUtils::unmarshallBodyBasic(eePtr.downcastTo<SOAPBodyBasic>(), el);
                                                                  
    XMLChString partsStr = DOMUtils::getAttribute(el, 
                                    SOAPConstants::ATTR_PARTS);
    if ( partsStr != null )
    {
        ((SOAPBody*)eePtr.get())->setParts(StringUtils::parseNMTokens(partsStr));
    }

    return eePtr;
}


WSDL_NAMESPACE_END

