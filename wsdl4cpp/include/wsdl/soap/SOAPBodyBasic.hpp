/*
 * %fv:SOAPBodyBasic.hpp-3 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#ifndef SOAPBODYBASIC_HPP_
#define SOAPBODYBASIC_HPP_
#include "wsdl/wsdlbas.hpp"
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/soap/SOAPElement.hpp"

WSDL_NAMESPACE_BEGIN

class SOAPBodyBasic;

DEFINE_PTR(SOAPBodyBasic);

/**
 * Abstract class for SOAPBody and SOAPFault
 */
class WSDL_EXPORT SOAPBodyBasic : public SOAPElement
{
public:
    SOAPBodyBasic(QNamePtr elementType, bool b = false)
        : SOAPElement(elementType, b)
		, encodingStyles(new XMLChString::List())
	{}
        
	SOAPBodyBasic():SOAPElement()
        , encodingStyles(new XMLChString::List()){};
	virtual ~SOAPBodyBasic(){};
	
    virtual XMLChString getUse() { return use; }
    virtual void setUse(XMLChString s){use = s;}
    
    virtual XMLChString getNamespaceURI() { return namespaceURI; }
    virtual void setNamespaceURI(XMLChString tUri){namespaceURI = tUri;}
    
    virtual XMLChString::ListPtr getEncodingStyles() { return encodingStyles; }
    virtual void setEncodingStyles(XMLChString::ListPtr sl){encodingStyles = sl;}
    
    virtual XMLChString toString() 
    {
        XMLChString s = SOAPElement::toString();
        if ( use != null ) {
            s.append(toXmlStr("\n  use="))
            .append(getUse());
        }
        if ( namespaceURI != null ) {
            s.append(toXmlStr("\n  namespace="))
            .append(getNamespaceURI());
        }
        if ( !encodingStyles->empty() ) {
            s.append(toXmlStr("\n  encodingStyle="));
        }
        for (XMLChString::List::iterator si = encodingStyles->begin(),
            se = encodingStyles->end(); si != se; si++ )
        {
            s.append(*si).append(toXmlStr(" "));
        }
        return s;
    }
    
protected:
    XMLChString use;
    XMLChString namespaceURI;
    XMLChString::ListPtr encodingStyles;

    virtual XMLChString getTagName() = 0;
};

WSDL_NAMESPACE_END

#endif /*SOAPBODYBASIC_HPP_*/
