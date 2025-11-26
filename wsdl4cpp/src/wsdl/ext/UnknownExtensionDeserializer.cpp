/*
 * %fv:UnknownExtensionDeserializer.cpp-4 % 
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
#include <xercesc/util/XMLUniDefs.hpp>
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/Constants.hpp"
#include "wsdl/util/DOMUtils.hpp"
#include "wsdl/ext/UnknownExtensibilityElement.hpp"
#include "wsdl/ext/UnknownExtensionDeserializer.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

UnknownExtensionDeserializer::UnknownExtensionDeserializer()
{
}

UnknownExtensionDeserializer::~UnknownExtensionDeserializer()
{
}

ExtensibilityElementPtr UnknownExtensionDeserializer::unmarshall(
        QNamePtr parentType, QNamePtr elementType, 
        DOMElement* el, 
        DefinitionsPtr def, 
        ExtensionRegistryPtr extReg) throw (WSDLException)
{
    UnknownExtensibilityElementPtr unknownExt(new UnknownExtensibilityElement());
    
    XMLChString requiredStr = DOMUtils::getAttributeNS(el,
                             Constants::NS_URI_WSDL,
                             Constants::ATTR_REQUIRED);
    if (requiredStr != null)
    {
        unknownExt->setRequired(XMLBOOL(requiredStr.c_str()));
    }

    unknownExt->setElementType(elementType);

    unknownExt->setElement(el);
	//ExtensibilityElementPtr ret(unknownExt.get());
    
    return unknownExt;
}


WSDL_NAMESPACE_END

