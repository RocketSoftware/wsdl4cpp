/*
 * %fv:QName.hpp-4 % 
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
 * 01-02                       9.SOAP   mzu  Migrated from WSDL4J
 * 03        070109  t85163    9.SOAP   mzu  Implementation for attribute extension
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 */
#ifndef QNAME_HPP_
#define QNAME_HPP_
#include <functional>
#include <list>
#include <set>
#include "wsdl/wsdlxerces.hpp"

WSDL_NAMESPACE_BEGIN

class QName;

DEFINE_PTR(QName);

struct lessQNamePtr;

class WSDL_EXPORT QName
{
public:
    typedef std::list<QNamePtr> List;  // @03
    DEFINE_PTR(List);                  // @03
    
    typedef std::set<QNamePtr, lessQNamePtr> PtrSet;
    DEFINE_PTR(PtrSet);
    
    static const QNamePtr Null;
    
    static PtrSetPtr createPtrSet(const QNamePtr* qps);
        
    
	static const XMLCh DEFAULT_NS_PREFIX[];

	QName(XMLChString localPart);
	QName(
		XMLChString namespaceURI, 
		XMLChString localPart,
		XMLChString prefix = DEFAULT_NS_PREFIX);
	virtual ~QName();
	virtual XMLChString getNamespaceURI() {return namespaceURI;}
	virtual XMLChString getLocalPart() {return localPart;}
	virtual XMLChString getPrefix() {return prefix;}
	
    virtual void setLocalPart(XMLChString lName) {localPart = lName;}

	virtual int compare(QNamePtr another) const;
	
	virtual XMLChString toString();

private:
	XMLChString namespaceURI;
	XMLChString localPart;
	XMLChString prefix;
};

struct WSDL_EXPORT lessQNamePtr : public std::binary_function<QNamePtr, QNamePtr, bool>
{
    bool
    operator()(const QNamePtr& __x, const QNamePtr& __y) const
    { return (__x.isNull() ? !__y.isNull() : __x->compare(__y) < 0); }
};

WSDL_NAMESPACE_END

#endif /*QNAME_HPP_*/
