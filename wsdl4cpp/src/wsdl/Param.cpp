/*
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
 * -----------------------------------------------------------------------
 * 01-03     060509            9.SOAP   mzu  Migrated from WSDL4J
 * 04        070109  t85163    9.SOAP   mzu  Add constants for attribute extentions
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 */
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/NamedElement.hpp"
#include "wsdl/Param.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

Param::Param()
	: AttributeExtensible(), NamedElement() //rev04
{
}

Param::~Param()
{
}

XMLChString Param::toString()
{
    XMLChString strBuf("");

    strBuf.append(getTagName())
    	.append(toXmlStr(": "));
        
    if ( getName() != null )
    {
        strBuf.append(toXmlStr("name="))
    	.append(getName());
    }
    	
    if ( mMessage )
    {
        if ( getName() != null )
        {
            strBuf.append(toXmlStr(", "));
        }
    	strBuf.append(toXmlStr("message="))
    		.append(mMessage->getQName()->toString());
    }
    	
    return strBuf;
}

WSDL_NAMESPACE_END

