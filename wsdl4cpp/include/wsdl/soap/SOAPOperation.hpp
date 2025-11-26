/*
 * %fv:SOAPOperation.hpp-4 % 
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
#ifndef SOAPOPERATION_HPP_
#define SOAPOPERATION_HPP_
#include <xercesc/dom/DOMElement.hpp>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/Constants.hpp"
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/soap/SOAPElement.hpp"

WSDL_NAMESPACE_BEGIN

class SOAPOperation;

DEFINE_PTR(SOAPOperation);

class WSDL_EXPORT SOAPOperation : public SOAPElement
{
public:
    static QNamePtr DEFAULT_ELEM_TYPE;
	SOAPOperation():SOAPElement(DEFAULT_ELEM_TYPE){};
	virtual ~SOAPOperation(){};
	
    virtual XMLChString getStyle() { return style; }
    virtual void setStyle(XMLChString s){style = s;}
    
    virtual XMLChString getSoapActionURI() { return soapActionURI; }
    virtual void setSoapActionURI(XMLChString tUri){soapActionURI = tUri;}
    
    virtual XMLChString toString() 
    {
        XMLChString s = SOAPElement::toString();
        if ( !getStyle().empty() ) {
            s.append(toXmlStr("\n  style="))
            .append(getStyle());
        }
        if ( !getSoapActionURI().empty() ) {
            s.append(toXmlStr("\n  soapAction="))
            .append(getSoapActionURI());
        }
        return s;
    }
    
protected:
    XMLChString style;
    XMLChString soapActionURI;

    virtual XMLChString getTagName() { return toXmlStr("binding"); };
};

WSDL_NAMESPACE_END

#endif /*SOAPOPERATION_HPP_*/
