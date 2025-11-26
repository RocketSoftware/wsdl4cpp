/*
 * %fv:SOAPBinding.hpp-5 % 
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
 */
#ifndef SOAPBINDING_HPP_
#define SOAPBINDING_HPP_
#include <xercesc/dom/DOMElement.hpp>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/soap/SOAPElement.hpp"

WSDL_NAMESPACE_BEGIN

class SOAPBinding;

DEFINE_PTR(SOAPBinding);

class WSDL_EXPORT SOAPBinding : public SOAPElement
{
public:
    static QNamePtr DEFAULT_ELEM_TYPE;
	SOAPBinding():SOAPElement(DEFAULT_ELEM_TYPE), style(SOAPConstants::STYLE_DOCUMENT){};
	virtual ~SOAPBinding(){};
	
    virtual XMLChString getStyle() { return style; }
    virtual void setStyle(XMLChString s){style = s;}
    
    virtual XMLChString getTransportURI() { return transportURI; }
    virtual void setTransportURI(XMLChString tUri){transportURI = tUri;}
    
    virtual XMLChString toString() 
    {
        return SOAPElement::toString()
            .append(toXmlStr("\n  style="))
            .append(getStyle())
            .append(toXmlStr("\n  transport="))
            .append(getTransportURI());
    }
    
protected:
    XMLChString style;
    XMLChString transportURI;

    virtual XMLChString getTagName() { return toXmlStr("binding"); };
};

WSDL_NAMESPACE_END

#endif /*SOAPBINDING_HPP_*/
