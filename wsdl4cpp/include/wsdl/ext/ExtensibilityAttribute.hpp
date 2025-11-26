/*
 * %fv:ExtensibilityAttribute.hpp-2 % 
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
 * 01        070109  t85163    9.SOAP   mzu  Migrated from WSDL4J
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 */
#ifndef EXTENSIBILITYATTRIBUTE_HPP_
#define EXTENSIBILITYATTRIBUTE_HPP_
#include <map>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/QName.hpp"

WSDL_NAMESPACE_BEGIN

class ExtensibilityAttribute;

DEFINE_PTR(ExtensibilityAttribute);

class WSDL_EXPORT ExtensibilityAttribute
{
public:
    static const int NO_DECLARED_TYPE;
    static const int STRING_TYPE;
    static const int QNAME_TYPE;
    static const int LIST_OF_STRINGS_TYPE;
    static const int LIST_OF_QNAMES_TYPE;

    typedef std::map<QNamePtr, ExtensibilityAttributePtr, lessQNamePtr> Map;
    DEFINE_PTR(Map);
    
	ExtensibilityAttribute()
        : type(NO_DECLARED_TYPE)
        , _string(null)
        , qName(0)
        , sList(0)
        , qnList(0)
        {}
    
	virtual ~ExtensibilityAttribute(){};
	
	virtual int getType() { return type; }
	virtual void setType(int t) { type = t; }

	virtual XMLChString getString() { return _string; }
	virtual void setString(XMLChString s) { _string = s; }

	virtual QNamePtr getQName() { return qName; }
	virtual void setQName(QNamePtr qn) { qName = qn; }

	virtual XMLChString::ListPtr getStringList() { return sList; }
	virtual void setStringList(XMLChString::ListPtr sl) { sList = sl; }

	virtual QName::ListPtr getQNameList() { return qnList; }
	virtual void setQNameList(QName::ListPtr ql) { qnList = ql; }

	virtual XMLChString toString();
	
protected:
    
	int type;
	
	XMLChString _string;
	QNamePtr qName;
	XMLChString::ListPtr sList;
	QName::ListPtr qnList;
		
};

WSDL_NAMESPACE_END

#endif /*EXTENSIBILITYATTRIBUTE_HPP_*/
