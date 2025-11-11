/*
 * %fv:SOAPBody.hpp-6 % 
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
