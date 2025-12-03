/*
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
 */
#ifndef SOAPBODY_HPP_
#define SOAPBODY_HPP_
#include <list>
#include <xercesc/dom/DOMElement.hpp>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/soap/SOAPBodyBasic.hpp"

WSDL_NAMESPACE_BEGIN

class SOAPBody;

DEFINE_PTR(SOAPBody);

class WSDL_EXPORT SOAPBody : public SOAPBodyBasic
{
public:
    static QNamePtr DEFAULT_ELEM_TYPE;
	SOAPBody():SOAPBodyBasic(DEFAULT_ELEM_TYPE)
        ,parts(new XMLChString::List()){};
	virtual ~SOAPBody(){};
	
    virtual XMLChString::ListPtr getParts() { return parts; }
    virtual void setParts(XMLChString::ListPtr sl){parts = sl;}
    
    virtual XMLChString toString() 
    {
        XMLChString s = SOAPBodyBasic::toString();
        if ( parts && !(parts->empty()) ) {
            s.append(toXmlStr("\n  parts="));
            for (XMLChString::List::iterator si = parts->begin(),
                se = parts->end(); si != se; si++ )
            {
                s.append(*si).append(toXmlStr(" "));
            }
        }
        return s;
    }
    
protected:
    XMLChString::ListPtr parts;

    virtual XMLChString getTagName() { return toXmlStr("body"); };
};

WSDL_NAMESPACE_END

#endif /*SOAPBODY_HPP_*/
