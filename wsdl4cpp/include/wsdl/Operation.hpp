/*
 * %fv:Operation.hpp-3 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#ifndef OPERATION_HPP_
#define OPERATION_HPP_
#include <map>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/Fault.hpp"
#include "wsdl/Input.hpp"
#include "wsdl/NamedElement.hpp"
#include "wsdl/OperationType.hpp"
#include "wsdl/Output.hpp"

WSDL_NAMESPACE_BEGIN

class Operation;

DEFINE_PTR(Operation);

class WSDL_EXPORT Operation : public NamedElement
{
public:
    typedef std::list<OperationPtr> List;
    DEFINE_PTR(List);

	Operation();
	virtual ~Operation();
	
    virtual XMLChString::ListPtr getParameterOrdering() { return mParameterOrdering; }
    virtual void setParameterOrdering(XMLChString::ListPtr elementName) { mParameterOrdering = elementName; }

    virtual OperationTypePtr getStyle() { return mStyle; }
    virtual void setStyle(OperationTypePtr ot) { mStyle = ot; }

    virtual InputPtr getInput() { return mInput; }
    virtual void setInput(InputPtr in) { mInput = in; }

    virtual OutputPtr getOutput() { return mOutput; }
    virtual void setOutput(OutputPtr in) { mOutput = in; }

    virtual void addFault(FaultPtr aFault)
    { 
        mFaultMap->insert(Fault::Map::value_type(
            aFault->getName(), aFault));
    }
    virtual FaultPtr getFault(XMLChString name) 
    {
        Fault::Map::iterator i = mFaultMap->find(name);
        if (i == mFaultMap->end()) return (FaultPtr)0;
        return i->second; 
    }
    virtual Fault::MapPtr getFaults() { return mFaultMap; }
    
	virtual bool isUndefined() { return undefined; }
	virtual void setUndefined(bool b) { undefined = b; }
	
	// NamedElement:: 
	virtual XMLChString toString();

private:

	bool undefined;
    XMLChString::ListPtr mParameterOrdering;
    OperationTypePtr mStyle;
    InputPtr mInput;
    OutputPtr mOutput;
    Fault::MapPtr mFaultMap;
	
	virtual XMLChString getTagName();
};

WSDL_NAMESPACE_END

#endif /*OPERATION_HPP_*/
