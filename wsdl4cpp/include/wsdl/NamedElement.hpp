/*
 * %fv:NamedElement.hpp-3 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#ifndef NAMEDELEMENT_HPP_
#define NAMEDELEMENT_HPP_
#include "wsdl/wsdlbas.hpp"
#include "wsdl/Documented.hpp"
#include "wsdl/QName.hpp"

WSDL_NAMESPACE_BEGIN

class NamedElement;

DEFINE_PTR(NamedElement);

class WSDL_EXPORT NamedElement : public Documented
{
public:
	NamedElement();
	virtual ~NamedElement();
	
	virtual QNamePtr getQName() { return mQName; }
	virtual void setQName(QNamePtr n) { mQName = n; }

    virtual XMLChString getName() { 
        return mQName.isNull() ? null : mQName->getLocalPart(); }
    
    virtual void setName(XMLChString name) { 
        if ( name == null )
        {
            setQName((QNamePtr)0);
        }
        else
        {
            if ( mQName.isNull() ) mQName = (QNamePtr)new QName(name);
            else mQName->setLocalPart(name); 
        }
    }

	virtual XMLChString toString();
	
protected:
	QNamePtr mQName;
    
private:
	virtual XMLChString getTagName() = 0;
};

WSDL_NAMESPACE_END

#endif /*NAMEDELEMENT_HPP_*/
