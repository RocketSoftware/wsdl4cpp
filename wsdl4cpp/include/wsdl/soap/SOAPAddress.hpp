/*
 * %fv:SOAPAddress.hpp-4 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#ifndef SOAPADDRESS_HPP_
#define SOAPADDRESS_HPP_
#include <xercesc/dom/DOMElement.hpp>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/soap/SOAPElement.hpp"

WSDL_NAMESPACE_BEGIN

class SOAPAddress;

DEFINE_PTR(SOAPAddress);

class WSDL_EXPORT SOAPAddress : public SOAPElement
{
public:
    static QNamePtr DEFAULT_ELEM_TYPE;
	SOAPAddress():SOAPElement(DEFAULT_ELEM_TYPE){};
	virtual ~SOAPAddress(){};
	
    virtual XMLChString getLocationURI() { return locationURI; }
    virtual void setLocationURI(XMLChString el){locationURI = el;}
    
    virtual XMLChString toString() 
    {
        return SOAPElement::toString()
            .append(toXmlStr("\n  location="))
            .append(getLocationURI());
    }
    
private:
    XMLChString locationURI;

    virtual XMLChString getTagName() { return toXmlStr("address"); };
};

WSDL_NAMESPACE_END

#endif /*SOAPADDRESS_HPP_*/
