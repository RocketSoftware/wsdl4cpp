/*
 * %fv:Service.cpp-4 % 
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

