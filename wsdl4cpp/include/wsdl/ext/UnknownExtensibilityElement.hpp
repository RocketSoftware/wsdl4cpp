/*
 * %fv:UnknownExtensibilityElement.hpp-3 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#ifndef UNKNOWNEXTENSIBILITYELEMENT_HPP_
#define UNKNOWNEXTENSIBILITYELEMENT_HPP_
#include <xercesc/dom/DOMElement.hpp>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/QName.hpp"
#include "wsdl/ext/ExtensibilityElement.hpp"

WSDL_NAMESPACE_BEGIN

class UnknownExtensibilityElement;

DEFINE_PTR(UnknownExtensibilityElement);

class WSDL_EXPORT UnknownExtensibilityElement : public ExtensibilityElement
{
protected:
    static const XMLCh EMPTY_STRING[];
public:
	UnknownExtensibilityElement();
	virtual ~UnknownExtensibilityElement();
	
    virtual XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* getElement() { return mEl; }
    virtual void setElement(XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el){mEl = el;}
    
private:
    XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* mEl;

    virtual XMLChString getTagName();
};

WSDL_NAMESPACE_END

#endif /*UNKNOWNEXTENSIBILITYELEMENT_HPP_*/
