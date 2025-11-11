/*
 * %fv:DOMUtils.hpp-4 % 
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
 */
#ifndef DOMUTILS_HPP_
#define DOMUTILS_HPP_
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMElement.hpp>

#include "wsdl/wsdlbas.hpp"
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/Definitions.hpp"
#include "wsdl/QName.hpp"
#include "wsdl/WSDLException.hpp"


WSDL_NAMESPACE_BEGIN

class WSDL_EXPORT DOMUtils
{
	
public:
    static const XMLCh* ATTR_XMLNS;
	static const XMLCh* NS_URI_XMLNS;

	DOMUtils();
	virtual ~DOMUtils();
	
	static XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* getFirstChildElement (XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* elem);
	static XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* getNextSiblingElement (XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* elem);
	static XMLChString getAttribute (XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el, const XMLCh* attrName);
	static XMLChString getAttributeNS (XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el,
                                       const XMLCh* namespaceURI,
                                       const XMLCh* localPart);
                                       
	static XMLChString getNamespaceURIFromPrefix (
							XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* context, 
                            const XMLCh* prefix);
	
	static bool matches(QNamePtr qname, XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node);
	static QNamePtr getQName(XMLChString prefixedValue,
						    XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* contextEl,
						    DefinitionsPtr def) throw(WSDLException);
						    
	static void registerUniquePrefix(XMLChString prefix,
                                          XMLChString namespaceURI,
                                          DefinitionsPtr def);
	
	typedef std::list<XERCES_CPP_NAMESPACE_QUALIFIER DOMAttr*> AttrPtrList;
	DEFINE_PTR(AttrPtrList);
	
	static QNamePtr getQualifiedAttributeValue(
						XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el,
					     const XMLCh* attrName,
					     const XMLCh* elDesc,
					     bool isRequired,
					     DefinitionsPtr def,
					     AttrPtrListPtr remainingAttrs
	) throw(WSDLException);
	
	static QNamePtr getQualifiedAttributeValue(
						XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el,
					     const XMLCh* attrName,
					     const XMLCh* elDesc,
					     bool isRequired,
					     DefinitionsPtr def
	) throw(WSDLException);
                                                 
    static AttrPtrListPtr getAttributes (XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el);
	static XMLChString getAttribute (XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el, 
			const XMLCh* attrName, AttrPtrListPtr remainingAttrs);
		
	static QNamePtr newQName(XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node);
	
	static void throwWSDLException(XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* location, 
		AttrPtrListPtr remainingAttrs) throw(WSDLException);

	static void throwWSDLException(XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* location) throw(WSDLException);
    
};

WSDL_NAMESPACE_END

#endif /*DOMUTILS_HPP_*/
