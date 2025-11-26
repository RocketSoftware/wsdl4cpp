/*
 * %fv:Operation.cpp-6 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
 */
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/NamedElement.hpp"
#include "wsdl/Operation.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

Operation::Operation()
	: NamedElement()
    , undefined(true)
	, mFaultMap(new Fault::Map())
{
}

Operation::~Operation()
{
}

XMLChString Operation::getTagName() 
{
    return toXmlStr("operation");
}

XMLChString Operation::toString()
{
    XMLChString strBuf("");

    strBuf.append(getTagName())
    	.append(toXmlStr(": name="))
    	.append(getName());
    	
    if ( mParameterOrdering )
    {
        strBuf.append(toXmlStr(", parameterOrdering="));
        for (XMLChString::List::iterator si=mParameterOrdering->begin(), se = mParameterOrdering->end();
                si != se; si++)
        {
            strBuf.append(toXmlStr(si==mParameterOrdering->begin()?"{":","));
            strBuf.append(*si);
        }
        strBuf.append(toXmlStr("}"));
    }
        
    if ( getStyle() )
    {
        strBuf.append(toXmlStr(", style="))
            .append(getStyle()->getId());
    }
        
    if ( getInput() )
    {
        strBuf.append(toXmlStr("\n    "))
            .append(getInput()->toString());
    }
        
    if ( getOutput() )
    {
        strBuf.append(toXmlStr("\n    "))
            .append(getOutput()->toString());
    }
        
    for (Fault::Map::iterator it = mFaultMap->begin(), ie = mFaultMap->end(); 
            it != ie; it++) 
    {
        strBuf.append(toXmlStr("\n    "))
            .append(it->second->toString());
    }
    
    return strBuf;
}

WSDL_NAMESPACE_END

