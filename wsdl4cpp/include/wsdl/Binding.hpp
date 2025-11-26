/*
 * %fv:Binding.hpp-4 % 
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
 * 
 */
#ifndef BINDING_HPP_
#define BINDING_HPP_
#include <map>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/NamedElement.hpp"
#include "wsdl/BindingOperation.hpp"
#include "wsdl/PortType.hpp"
#include "wsdl/ext/ExtensibilityElement.hpp"

WSDL_NAMESPACE_BEGIN

class Binding;

DEFINE_PTR(Binding);

class WSDL_EXPORT Binding : 
    public NamedElement, 
    public ElementExtensible
{
public:
    typedef std::map<QNamePtr, BindingPtr, lessQNamePtr> Map;
    DEFINE_PTR(Map);

	Binding();
	virtual ~Binding();
	
    virtual void addBindingOperation(BindingOperationPtr operation){ mOperationList->push_back(operation);}
//    virtual BindingOperationPtr getBindingOperation(XMLChString name,
//        XMLChString inputName, XMLChString outputName) throw (WSDLException);
      /**
       * Get all the operation bindings defined here.
       */
    virtual BindingOperation::ListPtr getBindingOperations() { return mOperationList;}

	virtual bool isUndefined() { return undefined; }
	virtual void setUndefined(bool b) { undefined = b; }
	
	virtual PortTypePtr getPortType() { return mPortType; }
	virtual void setPortType(PortTypePtr pt) { mPortType = pt; }
	
	// NamedElement:: 
	virtual XMLChString toString();

private:

    BindingOperation::ListPtr mOperationList;
	bool undefined;
	PortTypePtr mPortType;
	
	virtual XMLChString getTagName();
};

WSDL_NAMESPACE_END

#endif /*BINDING_HPP_*/
