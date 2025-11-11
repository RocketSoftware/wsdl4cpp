/*
 * %fv:Port.hpp-3 % 
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
#ifndef PORT_HPP_
#define PORT_HPP_
#include <map>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/Binding.hpp"
#include "wsdl/ext/ExtensibilityElement.hpp"
#include "wsdl/NamedElement.hpp"

WSDL_NAMESPACE_BEGIN

class Port;

DEFINE_PTR(Port);

class WSDL_EXPORT Port 
    : public NamedElement
    , public ElementExtensible
{

public:
    typedef std::map<XMLChString, PortPtr, lessXMLCh> Map;
    DEFINE_PTR(Map);

	Port();
	virtual ~Port();
	
    virtual BindingPtr getBinding() { return mBinding; }
    virtual void setBinding(BindingPtr b) { mBinding = b; }

	virtual bool isUndefined() { return undefined; }
	virtual void setUndefined(bool b) { undefined = b; }
	
	// NamedElement:: 
	virtual XMLChString toString();

private:

	bool undefined;
    BindingPtr mBinding;
	
	virtual XMLChString getTagName();
};

WSDL_NAMESPACE_END

#endif /*PORT_HPP_*/
