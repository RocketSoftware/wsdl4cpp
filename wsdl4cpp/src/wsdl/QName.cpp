/*
 * %fv:QName.cpp-5 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#include "wsdl/wsdlxerces.hpp"
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/XMLString.hpp>
#include "wsdl/Constants.hpp"
#include "wsdl/QName.hpp"

WSDL_NAMESPACE_BEGIN

const XMLCh QName::DEFAULT_NS_PREFIX[] = { XERCES_CPP_NAMESPACE_QUALIFIER chNull };

const QNamePtr QName::Null = (QNamePtr)0;

QName::PtrSetPtr QName::createPtrSet(const QNamePtr* qps)
{
    PtrSetPtr ps(new PtrSet());
    for (int i=0; !qps[i].isNull(); i++)
    {
        ps->insert(qps[i]);
    }
    return ps;
}

QName::QName(XMLChString lp)
	: namespaceURI(Constants::NULL_NS_URI)
	, localPart(lp)
	, prefix(DEFAULT_NS_PREFIX)
{
}

QName::QName(
		XMLChString nsURI, 
		XMLChString lp,
		XMLChString pf)
	: namespaceURI(nsURI), localPart(lp), prefix(pf)
{
}

QName::~QName()
{
}

inline int QName::compare(QNamePtr another) const 
{
	int r = namespaceURI.compare(another->getNamespaceURI());
	if ( r ) 
		return r;
	return localPart.compare(another->getLocalPart());
}

XMLChString QName::toString() 
{
    if (namespaceURI.compare(Constants::NULL_NS_URI) == 0) {
        return localPart;
    } else {
    	XMLChString r(toXmlStr("{"));
    	r.append(namespaceURI)
    	.append(toXmlStr("}"))
    	.append(localPart);
        return r;
    }
}

WSDL_NAMESPACE_END
