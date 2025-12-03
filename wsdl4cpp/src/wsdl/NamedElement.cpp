/*
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
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

