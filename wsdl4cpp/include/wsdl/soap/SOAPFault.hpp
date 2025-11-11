/*
 * %fv:SOAPFault.hpp-3 % 
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
#ifndef SOAPFAULT_HPP_
#define SOAPFAULT_HPP_
#include <list>
#include <xercesc/dom/DOMElement.hpp>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/soap/SOAPBodyBasic.hpp"

WSDL_NAMESPACE_BEGIN

class SOAPFault;

DEFINE_PTR(SOAPFault);

class WSDL_EXPORT SOAPFault : public SOAPBodyBasic
{
public:
    static QNamePtr DEFAULT_ELEM_TYPE;
	SOAPFault():SOAPBodyBasic(DEFAULT_ELEM_TYPE){};
	virtual ~SOAPFault(){};
	
    virtual XMLChString getName() { return name; }
    virtual void setName(XMLChString tUri){name = tUri;}
    
    virtual XMLChString toString() 
    {
        XMLChString s = SOAPBodyBasic::toString();
        if ( name != null ) {
            s.append(toXmlStr("\n  name="))
            .append(getName());
        }
        return s;
    }
    
protected:
    XMLChString name;

    virtual XMLChString getTagName() { return toXmlStr("body"); };
};

WSDL_NAMESPACE_END

#endif /*SOAPFAULT_HPP_*/
