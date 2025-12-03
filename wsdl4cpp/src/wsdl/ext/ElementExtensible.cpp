/*
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
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

