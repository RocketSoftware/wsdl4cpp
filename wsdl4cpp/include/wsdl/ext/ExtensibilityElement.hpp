/*
 * %fv:ExtensibilityElement.hpp-3 % 
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
#ifndef EXTENSIBILITYELEMENT_HPP_
#define EXTENSIBILITYELEMENT_HPP_
#include <list>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/QName.hpp"

WSDL_NAMESPACE_BEGIN

class ExtensibilityElement;

DEFINE_PTR(ExtensibilityElement);

class WSDL_EXPORT ExtensibilityElement
{
public:
    typedef std::list<ExtensibilityElementPtr> List;
    DEFINE_PTR(List);
    
    ExtensibilityElement(QNamePtr elementType, bool b = false)
        : mElementType(elementType), required(b){}
    
	ExtensibilityElement()
        : mElementType(0), required(false){}
    
	virtual ~ExtensibilityElement(){};
	
	virtual QNamePtr getElementType() { return mElementType; }
	virtual void setElementType(QNamePtr et) { mElementType = et; }

    virtual bool isRequired() { return required; }
    virtual void setRequired(bool b) { required = b; }
    
	virtual XMLChString toString();
	
protected:
    static const char id[];
	QNamePtr mElementType;
    bool required;
    
private:
    virtual XMLChString getTagName() = 0;
};

WSDL_NAMESPACE_END

#endif /*EXTENSIBILITYELEMENT_HPP_*/
