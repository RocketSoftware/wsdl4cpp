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
#include "wsdl/ext/UnknownExtensibilityElement.hpp"
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/soap/SOAPFault.hpp"
#include "wsdl/soap/SOAPFaultSerializer.hpp"
#include "wsdl/soap/SOAPSerializerUtils.hpp"
#include "wsdl/util/DOMUtils.hpp"
#include "wsdl/util/StringUtils.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

SOAPFaultSerializer::SOAPFaultSerializer()
{
}

SOAPFaultSerializer::~SOAPFaultSerializer()
{
}

ExtensibilityElementPtr SOAPFaultSerializer::unmarshall(
        QNamePtr parentType, QNamePtr elementType, 
        DOMElement* el, 
        DefinitionsPtr def, 
        ExtensionRegistryPtr extReg) throw (WSDLException)
{
    //SOAPFaultPtr eePtr(extReg->createExtension(parentType, elementType));
    ExtensibilityElementPtr eePtr(extReg->createExtension(parentType, elementType));
    
    SOAPSerializerUtils::unmarshallBodyBasic(eePtr.downcastTo<SOAPBodyBasic>(), el);
                                                                  
    XMLChString name = DOMUtils::getAttribute(el, 
                                    Constants::ATTR_NAME);
    if ( name != null ) {
        ((SOAPFault*)eePtr.get())->setName(name);
    }

    return eePtr;
}


WSDL_NAMESPACE_END

