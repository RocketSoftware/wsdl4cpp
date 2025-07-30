/*
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
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
