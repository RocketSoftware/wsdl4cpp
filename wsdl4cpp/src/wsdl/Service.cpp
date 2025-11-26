/*
 * %fv:Service.cpp-4 % 
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
 */
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/NamedElement.hpp"
#include "wsdl/Service.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

Service::Service()
	: NamedElement(), mPortMap(new Port::Map())
{
}

Service::~Service()
{
}

XMLChString Service::getTagName() 
{
    return toXmlStr("service");
}

XMLChString Service::toString()
{
    XMLChString strBuf = NamedElement::toString();
    
    // Add message information
    //strBuf.append(toXmlStr("\n"));
    for (Port::Map::iterator it = mPortMap->begin(), ie = mPortMap->end(); 
            it != ie; it++) 
    {
        strBuf.append(toXmlStr("\n  "))
            .append(it->second->toString());
    }

    return strBuf;
}

WSDL_NAMESPACE_END

