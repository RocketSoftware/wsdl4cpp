/*
 * %fv:Types.hpp-5 % 
 * 
 * Written by Ming Zhu (ming.zhu@nl.compuware.com), March 2006
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
 * --------------------------------------------------------------------------
 * 01-02     060509            9.SOAP   mzu  Migrated from WSDL4J
 * 03        060713  cr24024   9.SOAP   mzu  Add methods: addSchema, 
 *                                           isSchemaDefined
 * 04        060713  t85128    9.SOAP   mzu  Change for xml schema cross-reference
 * --------------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 * 
 */
#ifndef TYPES_HPP_
#define TYPES_HPP_
#include "wsdl/wsdlbas.hpp"
#include "wsdl/Constants.hpp"
#include "wsdl/Documented.hpp"
#include "wsdl/ext/ElementExtensible.hpp"
#include "wsdl/util/StringUtils.hpp"
#include "wsdl/schema/SchemaXercesc.hpp"
#include "wsdl/schema/SchemaModel.hpp"
#include "wsdl/util/XercesUtils.hpp"

WSDL_NAMESPACE_BEGIN

class Types;

DEFINE_PTR(Types);

/**
 * This class represents the &lt;types&gt; section of a WSDL document.
 * 
 * @author  Matthew J. Duftler (duftler@us.ibm.com, for original java 
 *                              implementation)
 * @author  Ming Zhu (ming.zhu@nl.compuware.com, for C++ migration) 
 */
class WSDL_EXPORT Types : 
    public Documented 
    , public ElementExtensible
    , public SchemaModel //@rev04
{
public:
    typedef std::list<TypesPtr> List;
    DEFINE_PTR(List);
    
	Types()
	  : SchemaModel() //@rev04
	  , schemaDefined(false) // @rev03
	  {}
	  
	virtual ~Types(){}
	
	virtual XMLChString toString();
    
    /**
     * Add a schema to the extensibility element list.
     * @param schema the schema.
     * @since rev03
     */
    virtual void addSchema(ExtensibilityElementPtr schema)
    {
    	if ( schema )
    	{
	        addExtensibilityElement(schema);
	        schemaDefined = true;
    	}
    }
    
    /**
     * Check if the schema is defined.
     * @return true if and only if the schema is defined.
     * @since rev03
     */
    virtual bool isSchemaDefined() { return schemaDefined; }
    
protected:
	
	bool schemaDefined;
	virtual XMLChString getTagName() { return Constants::ELEM_TYPES; }
	
};

WSDL_NAMESPACE_END

#endif /*TYPES_HPP_*/
