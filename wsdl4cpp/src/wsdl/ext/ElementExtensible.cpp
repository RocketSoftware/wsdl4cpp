/*
 * %fv:ElementExtensible.cpp-3 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#include <xercesc/util/XMLUniDefs.hpp>
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/ext/ElementExtensible.hpp"
#include "wsdl/util/StringUtils.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

XMLChString ElementExtensible::toString()
{
    XMLChString strBuf("");
    if ( !extElements->empty() )
    {
        strBuf.append(toXmlStr("\n"));
    }
    for(ExtensibilityElement::List::iterator i = extElements->begin(), l = extElements->end();
        i != l; i++)
    {
        strBuf.append(toXmlStr("  "));
        
        ExtensibilityElementPtr ee(*i);
        ExtensibilityElement* p = ee.get();
        
        strBuf.append(StringUtils::addIndent(p->toString(), StringUtils::DEFAULT_INDENT))
            .append(toXmlStr("\n"));
    }
    return strBuf;
}

#ifdef NO_METHOD_TEMPLATES
ExtensibilityElementPtr ElementExtensible::getFirstExtensibilityElement(QNamePtr elementType)
{
    for(ExtensibilityElement::List::iterator i = extElements->begin(), l = extElements->end();
        i != l; i++)
    {
        if ( i->get()->getElementType()->compare(elementType) == 0 
            //&& T::typeId == i->get()->typeId
            )
        {
            return (*i);
        }
    }
    return (ExtensibilityElementPtr)0;
}
#endif

WSDL_NAMESPACE_END

