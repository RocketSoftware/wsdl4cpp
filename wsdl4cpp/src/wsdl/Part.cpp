/*
 * %fv:Part.cpp-6 % 
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
#include "wsdl/Part.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

Part::Part()
	: AttributeExtensible(), NamedElement() //rev04
{
}

Part::~Part()
{
}

XMLChString Part::getTagName() 
{
    return toXmlStr("part");
}

XMLChString Part::toString()
{
    XMLChString strBuf("");

    strBuf.append(getTagName())
    	.append(toXmlStr(": name="))
    	.append(getName());
    	
    if ( mElementName )
    {
    	strBuf.append(toXmlStr(", element="))
    		.append(mElementName->toString());
    }
    	
    if ( mTypeName )
    {
    	strBuf.append(toXmlStr(", type="))
    		.append(mTypeName->toString());
    }
    return strBuf;
}

WSDL_NAMESPACE_END

