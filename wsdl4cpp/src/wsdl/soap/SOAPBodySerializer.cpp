/*
 * %fv:SOAPBodySerializer.cpp-4 % 
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

