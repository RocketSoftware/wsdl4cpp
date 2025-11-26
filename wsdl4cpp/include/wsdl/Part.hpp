/*
 * %fv:Part.hpp-4 % 
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
 * -----------------------------------------------------------------------
 * 01-02                       9.SOAP   mzu  Migrated from WSDL4J
 * 03        070109  t85163    9.SOAP   mzu  Implementation for attribute extension
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 */
#ifndef PART_HPP_
#define PART_HPP_
#include <list>
#include <map>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/Constants.hpp"
#include "wsdl/NamedElement.hpp"
#include "wsdl/ext/AttributeExtensible.hpp"

WSDL_NAMESPACE_BEGIN

class Part;

DEFINE_PTR(Part);

class WSDL_EXPORT Part : public AttributeExtensible, public NamedElement
{
public:
    typedef std::list<PartPtr> List;
    typedef std::map<XMLChString, PartPtr, lessXMLCh> Map;
    DEFINE_PTR(List);
    DEFINE_PTR(Map);

	Part();
	virtual ~Part();
	
	virtual QNamePtr getElementName() { return mElementName; }
	virtual void setElementName(QNamePtr elementName) { mElementName = elementName; }

	virtual QNamePtr getTypeName() { return mTypeName; }
	virtual void setTypeName(QNamePtr typeName) { mTypeName = typeName; }

    /**
     * @since revision @03
     */
    virtual XMLChString::SetPtr getNativeAttributeNames() const 
    	{ return Constants::PART_ATTR_NAMES_SET; };

	// NamedElement:: 
	virtual XMLChString toString();
private:

	QNamePtr mElementName;
	QNamePtr mTypeName;
	
	virtual XMLChString getTagName();
};

WSDL_NAMESPACE_END

#endif /*PART_HPP_*/
