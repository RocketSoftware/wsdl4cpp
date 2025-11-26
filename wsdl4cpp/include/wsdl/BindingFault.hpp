/*
 * %fv:BindingFault.hpp-4 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
 */
#ifndef BINDINGFAULT_HPP_
#define BINDINGFAULT_HPP_
#include "wsdl/wsdlbas.hpp"
#include "wsdl/ext/ElementExtensible.hpp"

WSDL_NAMESPACE_BEGIN

class BindingFault;

DEFINE_PTR(BindingFault);

class WSDL_EXPORT BindingFault : public NamedExtensible
{
public:
    typedef std::map<XMLChString, BindingFaultPtr, lessXMLCh> Map;
    DEFINE_PTR(Map);

	BindingFault();
	virtual ~BindingFault();
	
private:

    // NamedElement::
    virtual XMLChString getTagName();
	
};

WSDL_NAMESPACE_END

#endif /*BINDINGFAULT_HPP_*/
