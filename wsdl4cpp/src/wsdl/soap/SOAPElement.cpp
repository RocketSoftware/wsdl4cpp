/*
 * %fv:SOAPElement.cpp-4 % 
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
#include "wsdl/soap/SOAPElement.hpp"
#include "wsdl/util/StringUtils.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

const XMLCh SOAPElement::PREFIX[] = { 
    chLatin_s, chLatin_o, chLatin_a, chLatin_p, chNull };
const XMLCh SOAPElement::PREFIX_SEPARATOR[] = { 
    chColon, chNull };

XMLChString SOAPElement::toString()
{
    XMLChString strBuf("");

    if ( getElementType() )
    {
        strBuf.append(PREFIX)
            .append(PREFIX_SEPARATOR)
            .append(getElementType()->getLocalPart());
    }

    return strBuf;
}

WSDL_NAMESPACE_END

