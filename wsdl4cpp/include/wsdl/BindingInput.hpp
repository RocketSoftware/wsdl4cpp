/*
 * %fv:BindingInput.hpp-6 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
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
