/*
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
 */
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/NamedElement.hpp"
#include "wsdl/Binding.hpp"
#include "wsdl/util/StringUtils.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

Binding::Binding()
	: NamedElement(), mOperationList(new BindingOperation::List()), undefined(true)
{
}

Binding::~Binding()
{
}

XMLChString Binding::getTagName() 
{
    return toXmlStr("binding");
}

XMLChString Binding::toString()
{
	XMLChString r = NamedElement::toString();
	if ( mPortType ) 
	{
        r.append(toXmlStr(", portType="));
		r.append(getPortType()->getQName()->toString());
	}
	
    r.append(ElementExtensible::toString());
        
    for (BindingOperation::List::iterator it = mOperationList->begin(), 
        ie = mOperationList->end(); 
            it != ie; it++) 
    {
        r.append(toXmlStr("\n\n"))
         .append(StringUtils::DEFAULT_INDENT)
            .append(StringUtils::addIndent(
                (*it)->toString(), 
                StringUtils::DEFAULT_INDENT));
    }

	return r;
}

WSDL_NAMESPACE_END

