/*
 * %fv:SOAPFaultSerializer.cpp-3 % 
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

