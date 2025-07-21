/*
 * %fv:BindingFault.hpp-4 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
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
