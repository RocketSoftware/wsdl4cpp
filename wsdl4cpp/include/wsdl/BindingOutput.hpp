/*
 * %fv:BindingOutput.hpp-4 % 
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
#ifndef BINDINGOUTPUT_HPP_
#define BINDINGOUTPUT_HPP_
#include "wsdl/wsdlbas.hpp"
#include "wsdl/ext/ElementExtensible.hpp"

WSDL_NAMESPACE_BEGIN

class BindingOutput;

DEFINE_PTR(BindingOutput);

class WSDL_EXPORT BindingOutput
    : public NamedExtensible
{
public:
	BindingOutput();
	virtual ~BindingOutput();
	
private:

    // NamedElement::
    virtual XMLChString getTagName();
	
};

WSDL_NAMESPACE_END

#endif /*BINDINGOUTPUT_HPP_*/
