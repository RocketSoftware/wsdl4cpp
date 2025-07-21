/*
 * %fv:Schema.cpp-4 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * 
 * History:
 * 
 * revision  date    refnum    version  who  description
 * --------------------------------------------------------------------------
 * 01        060713            9.SOAP   mzu  Migrated from WSDL4J
 * 02        060713  t85128    9.SOAP   mzu  Change for xml schema cross-reference
 * --------------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 */
#include <xercesc/util/XMLUniDefs.hpp>
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/util/StringUtils.hpp"
#include "wsdl/schema/Schema.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

const XMLCh Schema::PREFIX[] = { 
    chLatin_x, chLatin_s, chLatin_d, chNull };
const XMLCh Schema::PREFIX_SEPARATOR[] = { 
    chColon, chNull };

Schema::Schema(QNamePtr elementType, bool b)
    : ExtensibilityElement(elementType, b)
    , element(0)
{
}

Schema::Schema()
    : ExtensibilityElement(Schema::DEFAULT_ELEM_TYPE, false)
    , element(0)
{
}

Schema::~Schema()
{
}

XMLChString Schema::toString()
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

