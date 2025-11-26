/*
 * %fv:Message.cpp-5 % 
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
#include "wsdl/Message.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

Message::Message()
	: NamedElement()
    , undefined(true)
    , additionOrderOfParts(new XMLChString::List())
    , mPartMap(new Part::Map())
{
}

Message::~Message()
{
}

XMLChString Message::getTagName() 
{
    return toXmlStr("message");
}

Part::ListPtr Message::getOrderedParts(XMLChString::ListPtr partOrder)
{
    Part::ListPtr orderedParts(new Part::List());

    if (!partOrder)
    {
        partOrder = additionOrderOfParts;
    }
    
    for (XMLChString::List::iterator pi = partOrder->begin(),
        pe = partOrder->end(); pi != pe; pi++)
    {
        PartPtr part = getPart(*pi);
        if ( part ) 
        {
            orderedParts->push_back(part);
        }
    }
        
    return orderedParts;
}

XMLChString Message::toString()
{
	XMLChString strBuf = NamedElement::toString();
    
    Part::ListPtr pList = getOrderedParts();
	
    for (Part::List::iterator it = pList->begin(), ie = pList->end(); 
            it != ie; it++) 
    {
        strBuf.append(toXmlStr("\n  "))
            .append((*it)->toString());
    }

	return strBuf;
}

WSDL_NAMESPACE_END

