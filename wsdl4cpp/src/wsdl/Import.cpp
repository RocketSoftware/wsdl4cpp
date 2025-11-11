/*
 * %fv:Import.cpp-4 % 
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
 * 01        060509            9.SOAP   mzu  Migrated from WSDL4J
 * 02        070109  t85163    9.SOAP   mzu  Add constants for attribute extentions
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 */
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/Import.hpp"
#include "wsdl/Definitions.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

Import::Import() : AttributeExtensible(), Documented() //rev02
{
}

Import::~Import()
{
}

DefinitionsPtr Import::getDefinition() 
{ 
    return definition; 
}

void Import::setDefinition(DefinitionsPtr def) 
{ 
    definition=def; 
}


XMLChString Import::toString() 
{ 
    XMLChString strBuf = getTagName();
    
    strBuf.append(toXmlStr(": "));

    if (namespaceURI != null)
    {
        strBuf.append(toXmlStr("\n  namespaceURI=")).append(namespaceURI);
    }

    if (locationURI != null)
    {
      strBuf.append(toXmlStr("\n  locationURI=")).append(locationURI);
    }

    if (definition)
    {
      strBuf.append(toXmlStr("\n  definition=")).append(definition->toString());
    }

//    Iterator keys = extensionAttributes.keySet().iterator();
//
//    while (keys.hasNext())
//    {
//      QName name = (QName)keys.next();
//
//      strBuf.append("\nextension attribute: " + name + "=" +
//                    extensionAttributes.get(name));
//    }

    return strBuf;
}


WSDL_NAMESPACE_END

