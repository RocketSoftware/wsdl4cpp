/*
 * %fv:Binding.cpp-5 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
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

