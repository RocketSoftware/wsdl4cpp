/*
 * %fv:Port.cpp-5 % 
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

