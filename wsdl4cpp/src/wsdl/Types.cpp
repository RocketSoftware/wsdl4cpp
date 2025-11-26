/*
 * %fv:Types.cpp-5 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
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
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/Types.hpp"
#include "wsdl/schema/Schema.hpp"
#include "wsdl/schema/SchemaConstants.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

XMLChString Types::toString()
{
    XMLChString strBuf("");

    strBuf.append(getTagName())
        .append(toXmlStr(": "));
    
    //@rev02
    strBuf.append(StringUtils::addIndent(SchemaModel::toString()));
    strBuf.append(ElementExtensible::toString());
    strBuf.append(toXmlStr("\n"));
    return strBuf;
}

WSDL_NAMESPACE_END

