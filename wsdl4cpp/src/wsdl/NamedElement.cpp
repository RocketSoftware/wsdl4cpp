/*
 * %fv:NamedElement.cpp-6 % 
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
#include <xercesc/util/XMLUniDefs.hpp>
#include "wsdl/NamedElement.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

NamedElement::NamedElement()
	: Documented(), mQName(0)
{
}

NamedElement::~NamedElement()
{
}

XMLChString NamedElement::toString()
{
    XMLChString strBuf("");

    strBuf.append(getTagName())
    	.append(toXmlStr(": "));
    	
    if ( mQName )
    {
        strBuf.append(toXmlStr("name="))
    	    .append(mQName->toString());
    }

//    if (parts != null)
//    {
//      Iterator partsIterator = parts.values().iterator();
//
//      while (partsIterator.hasNext())
//      {
//        strBuf.append("\n" + partsIterator.next());
//      }
//    }

    return strBuf;
}

WSDL_NAMESPACE_END

