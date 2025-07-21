/*
 * %fv:SOAPHeaderFault.hpp-3 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#ifndef SOAPHEADERFAULT_HPP_
#define SOAPHEADERFAULT_HPP_
#include <list>
#include <xercesc/dom/DOMElement.hpp>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/soap/SOAPHeaderBasic.hpp"

WSDL_NAMESPACE_BEGIN

class SOAPHeaderFault;

DEFINE_PTR(SOAPHeaderFault);

class WSDL_EXPORT SOAPHeaderFault : public SOAPHeaderBasic
{
public:
    typedef std::list<SOAPHeaderFaultPtr> List;
    DEFINE_PTR(List);
    
    static QNamePtr DEFAULT_ELEM_TYPE;
	SOAPHeaderFault():SOAPHeaderBasic(DEFAULT_ELEM_TYPE){};
	virtual ~SOAPHeaderFault(){};
	
protected:
    virtual XMLChString getTagName() { return toXmlStr("headerfault"); };
};

WSDL_NAMESPACE_END

#endif /*SOAPHEADERFAULT_HPP_*/
