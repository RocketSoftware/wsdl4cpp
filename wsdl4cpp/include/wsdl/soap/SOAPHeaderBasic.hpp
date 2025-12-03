/*
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
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
