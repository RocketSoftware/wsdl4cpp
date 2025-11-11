/*
 * %fv:ExtensibilityElement.cpp-4 % 
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
#include <xercesc/util/XMLUniDefs.hpp>
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/ext/ExtensibilityElement.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

const char ExtensibilityElement::id[] = "wsdl::ExtensibilityElement";

XMLChString ExtensibilityElement::toString()
{
    XMLChString strBuf("");

//    strBuf.append(getTagName())
//    	.append(toXmlStr(": elementType="));
//    	
    if ( mElementType )
    	strBuf.append(mElementType->toString());

    return strBuf;
}

template <typename T> T* newinstance()
{
    return new T();
}

WSDL_NAMESPACE_END

