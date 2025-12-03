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
#include "wsdl/ext/UnknownExtensibilityElement.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

UnknownExtensibilityElement::UnknownExtensibilityElement()
	: ExtensibilityElement(), mEl(0)
{
}

UnknownExtensibilityElement::~UnknownExtensibilityElement()
{
}

XMLChString UnknownExtensibilityElement::getTagName() 
{
    return toXmlStr("UnknownExtensibilityElement");
}

WSDL_NAMESPACE_END

