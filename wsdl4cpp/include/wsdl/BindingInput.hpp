/*
 * %fv:BindingInput.hpp-6 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#ifndef BINDINGINPUT_HPP_
#define BINDINGINPUT_HPP_
#include "wsdl/wsdlbas.hpp"
#include "wsdl/ext/ElementExtensible.hpp"

WSDL_NAMESPACE_BEGIN

class BindingInput;

DEFINE_PTR(BindingInput);

class WSDL_EXPORT BindingInput :
    public NamedExtensible
{
public:
	BindingInput();
	virtual ~BindingInput();
	
private:

    // NamedElement::
    virtual XMLChString getTagName();
	
};

WSDL_NAMESPACE_END

#endif /*BINDINGINPUT_HPP_*/
