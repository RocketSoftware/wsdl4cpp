/*
 * %fv:BindingOperation.hpp-3 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#ifndef BINDINGOPERATION_HPP_
#define BINDINGOPERATION_HPP_
#include <map>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/BindingFault.hpp"
#include "wsdl/BindingInput.hpp"
#include "wsdl/BindingOutput.hpp"
#include "wsdl/NamedElement.hpp"
#include "wsdl/Operation.hpp"
#include "wsdl/ext/ElementExtensible.hpp"

WSDL_NAMESPACE_BEGIN

class BindingOperation;

DEFINE_PTR(BindingOperation);

class WSDL_EXPORT BindingOperation : 
    public NamedElement, 
    public ElementExtensible
{
public:
    typedef std::list<BindingOperationPtr> List;
    DEFINE_PTR(List);
    
	BindingOperation();
	virtual ~BindingOperation();
	
    virtual OperationPtr getOperation() { return mOperation; }
    virtual void setOperation(OperationPtr op) { mOperation = op; }

    virtual BindingInputPtr getBindingInput() { return mBindingInput; }
    virtual void setBindingInput(BindingInputPtr in) { mBindingInput = in; }

    virtual BindingOutputPtr getBindingOutput() { return mBindingOutput; }
    virtual void setBindingOutput(BindingOutputPtr out) { mBindingOutput = out; }

    virtual void addBindingFault(BindingFaultPtr aBindingFault)
    { 
        mBindingFaultMap->insert(BindingFault::Map::value_type(
            aBindingFault->getName(), aBindingFault));
    }
    virtual BindingFaultPtr getBindingFault(XMLChString name) 
    {
        BindingFault::Map::iterator i = mBindingFaultMap->find(name);
        if (i == mBindingFaultMap->end()) return (BindingFaultPtr)0;
        return i->second; 
    }
    virtual BindingFault::MapPtr getBindingFaults() { return mBindingFaultMap; }
    
	virtual bool isUndefined() { return undefined; }
	virtual void setUndefined(bool b) { undefined = b; }
	
	// NamedElement:: 
	virtual XMLChString toString();

private:

	bool undefined;
    OperationPtr mOperation;
    BindingInputPtr mBindingInput;
    BindingOutputPtr mBindingOutput;
    BindingFault::MapPtr mBindingFaultMap;
	
	virtual XMLChString getTagName();
};

WSDL_NAMESPACE_END

#endif /*BINDINGOPERATION_HPP_*/
