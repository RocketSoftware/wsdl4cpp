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

