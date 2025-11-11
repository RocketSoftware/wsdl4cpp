/*
 * %fv:BindingOperation.cpp-5 % 
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
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/NamedElement.hpp"
#include "wsdl/BindingOperation.hpp"
#include "wsdl/util/StringUtils.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

BindingOperation::BindingOperation()
	: NamedElement(), mBindingFaultMap(new BindingFault::Map())
{
}

BindingOperation::~BindingOperation()
{
}

XMLChString BindingOperation::getTagName() 
{
    return toXmlStr("operation");
}

XMLChString BindingOperation::toString()
{
    XMLChString strBuf("");

    strBuf.append(getTagName())
    	.append(toXmlStr(": name="))
    	.append(getName());
    	
    if ( mOperation )
    {
        strBuf.append(toXmlStr(", operation="))
            .append(mOperation->getName());
    }
        
    strBuf.append(ElementExtensible::toString());
        
    if ( getBindingInput() )
    {
        strBuf.append(toXmlStr("\n\n  "))
            .append(StringUtils::addIndent(
                getBindingInput()->toString()));
    }
        
    if ( getBindingOutput() )
    {
        strBuf.append(toXmlStr("\n\n  "))
            .append(StringUtils::addIndent(
                getBindingOutput()->toString()));
    }
        
    for (BindingFault::Map::iterator it = mBindingFaultMap->begin(), ie = mBindingFaultMap->end(); 
            it != ie; it++) 
    {
        strBuf.append(toXmlStr("\n\n  "))
            .append(StringUtils::addIndent(
                it->second->toString()));
    }
    
    return strBuf;
}

WSDL_NAMESPACE_END

