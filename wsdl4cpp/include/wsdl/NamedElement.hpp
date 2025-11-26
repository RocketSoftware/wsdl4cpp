/*
 * %fv:NamedElement.hpp-3 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
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
