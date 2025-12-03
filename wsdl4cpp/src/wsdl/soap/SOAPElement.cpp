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

