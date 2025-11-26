/*
 * %fv:SOAPHeader.hpp-3 % 
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
#ifndef SOAPHEADER_HPP_
#define SOAPHEADER_HPP_
#include <list>
#include <xercesc/dom/DOMElement.hpp>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/soap/SOAPHeaderFault.hpp"
#include "wsdl/util/StringUtils.hpp"

WSDL_NAMESPACE_BEGIN

class SOAPHeader;

DEFINE_PTR(SOAPHeader);

class WSDL_EXPORT SOAPHeader : public SOAPHeaderBasic
{
public:
    static QNamePtr DEFAULT_ELEM_TYPE;
	SOAPHeader():SOAPHeaderBasic(DEFAULT_ELEM_TYPE), soapHeaderFaults(new SOAPHeaderFault::List()){};
	virtual ~SOAPHeader(){};
	
    virtual void addSOAPHeaderFault(SOAPHeaderFaultPtr aFault){ soapHeaderFaults->push_back(aFault);}
    virtual SOAPHeaderFault::ListPtr getSOAPHeaderFaults() { return soapHeaderFaults;}

    virtual XMLChString toString() 
    {
        XMLChString s = SOAPHeaderBasic::toString();
        if ( !soapHeaderFaults )
            return s;
            
        if ( !soapHeaderFaults->empty() )
        {
            s.append(toXmlStr("\n  faults:"));
        }
        for (SOAPHeaderFault::List::iterator it = soapHeaderFaults->begin(), ie = soapHeaderFaults->end(); 
                it != ie; it++) 
        {
            s.append(toXmlStr("\n  "))
                .append(StringUtils::addIndent(it->get()->toString(), StringUtils::DEFAULT_INDENT));
        }
    
        return s;
    }
protected:
    SOAPHeaderFault::ListPtr soapHeaderFaults;
    virtual XMLChString getTagName() { return toXmlStr("header"); };
};

WSDL_NAMESPACE_END

#endif /*SOAPHEADER_HPP_*/
