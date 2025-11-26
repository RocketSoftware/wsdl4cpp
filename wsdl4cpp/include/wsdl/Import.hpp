/*
 * %fv:Import.hpp-3 % 
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
 * 
 * History:
 * 
 * revision  date    refnum    version  who  description
 * -----------------------------------------------------------------------
 * 01                          9.SOAP   mzu  Migrated from WSDL4J
 * 02        070109  t85163    9.SOAP   mzu  Implementation for attribute extension
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 */
#ifndef IMPORT_HPP_
#define IMPORT_HPP_
#include <list>
#include <map>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/Constants.hpp"
#include "wsdl/Documented.hpp"
#include "wsdl/ext/AttributeExtensible.hpp"

WSDL_NAMESPACE_BEGIN

class WSDL_EXPORT Import 
	: public AttributeExtensible
	, public Documented
{
public:
    typedef std::list<ImportPtr> List;
    DEFINE_PTR(List);
    typedef std::map<XMLChString, ListPtr, lessXMLCh> ListMap;
    DEFINE_PTR(ListMap);

	Import();
	virtual ~Import();
    
    virtual DefinitionsPtr getDefinition();
    virtual void setDefinition(DefinitionsPtr def);

    virtual XMLChString getLocationURI() { return locationURI; }
    virtual void setLocationURI(XMLChString uri) { locationURI=uri; }

    virtual XMLChString getNamespaceURI() { return namespaceURI; }
    virtual void setNamespaceURI(XMLChString uri) { namespaceURI=uri; }
    
    virtual XMLChString::SetPtr getNativeAttributeNames() const 
    	{ return Constants::IMPORT_ATTR_NAMES_SET; };

    virtual XMLChString toString();
private:
    XMLChString namespaceURI;
    XMLChString locationURI;
    
    DefinitionsPtr definition;
       
	virtual XMLChString getTagName() { return toXmlStr("import");}
};

WSDL_NAMESPACE_END

#endif /*IMPORT_HPP_*/
