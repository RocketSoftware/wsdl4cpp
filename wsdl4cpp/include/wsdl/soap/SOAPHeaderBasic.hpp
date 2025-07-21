/*
 * %fv:SOAPHeaderBasic.hpp-2 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#ifndef SOAPHEADERBASIC_HPP_
#define SOAPHEADERBASIC_HPP_
#include <list>
#include <xercesc/dom/DOMElement.hpp>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/soap/SOAPBodyBasic.hpp"

WSDL_NAMESPACE_BEGIN

class SOAPHeaderBasic;

DEFINE_PTR(SOAPHeaderBasic);

class WSDL_EXPORT SOAPHeaderBasic : public SOAPBodyBasic
{
public:
    SOAPHeaderBasic(QNamePtr elementType, bool b = false)
        : SOAPBodyBasic(elementType, b)
    {}
        
    SOAPHeaderBasic():SOAPBodyBasic(){};
    virtual ~SOAPHeaderBasic(){};
    
    virtual QNamePtr getMessage() { return message; }
    virtual void setMessage(QNamePtr aMessage){message = aMessage;}
    
    virtual XMLChString getPart() { return part; }
    virtual void setPart(XMLChString aPart){part = aPart;}
    
    virtual XMLChString toString() 
    {
        XMLChString s = SOAPBodyBasic::toString();
        if ( message ) {
            s.append(toXmlStr("\n  message="))
            .append(getMessage()->toString());
        }
        if ( part != null ) {
            s.append(toXmlStr("\n  part="))
            .append(getPart());
        }
        return s;
    }
    
protected:
    QNamePtr message;
    XMLChString part;
    
    virtual XMLChString getTagName() = 0;
};

WSDL_NAMESPACE_END

#endif /*SOAPHEADERBASIC_HPP_*/
