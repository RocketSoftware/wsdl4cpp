/*
 * %fv:Port.cpp-5 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/NamedElement.hpp"
#include "wsdl/Port.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

Port::Port()
	: NamedElement()
{
}

Port::~Port()
{
}

XMLChString Port::getTagName() 
{
    return toXmlStr("port");
}

XMLChString Port::toString()
{
    XMLChString strBuf("");

    strBuf.append(getTagName())
    	.append(toXmlStr(": name="))
    	.append(getName());
    	
    if ( getBinding() )
    {
        strBuf.append(toXmlStr(", binding="))
            .append(getBinding()->getQName()->toString());
    }
    
    strBuf.append(ElementExtensible::toString());
        
    return strBuf;
}

WSDL_NAMESPACE_END

