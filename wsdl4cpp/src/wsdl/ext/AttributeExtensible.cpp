/*
 * %fv:AttributeExtensible.cpp-3 % 
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

#include <xercesc/util/XMLUniDefs.hpp>
#include "wsdl/ext/AttributeExtensible.hpp"
#include "wsdl/util/StringUtils.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

XMLChString AttributeExtensible::toString()
{
    XMLChString strBuf("");
//    if ( !extAttributes->empty() )
//    {
//        strBuf.append(toXmlStr("\n"));
//    }
//    for(ExtensibilityAttribute::List::iterator i = extAttributes->begin(), l = extAttributes->end();
//        i != l; i++)
//    {
//        strBuf.append(toXmlStr("  "));
//        
//        ExtensibilityAttributePtr ee(*i);
//        ExtensibilityAttribute* p = ee.get();
//        
//        strBuf.append(StringUtils::addIndent(p->toString(), StringUtils::DEFAULT_INDENT))
//            .append(toXmlStr("\n"));
//    }
    return strBuf;
}

WSDL_NAMESPACE_END

