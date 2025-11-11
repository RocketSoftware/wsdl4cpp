/*
 * %fv:SOAPConstants.hpp-6 % 
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
#ifndef SOAPCONSTANTS_HPP_
#define SOAPCONSTANTS_HPP_
#include <vector>
#include <xercesc/util/XercesDefs.hpp>

#include "wsdl/wsdlbas.hpp"
#include "wsdl/QName.hpp"

WSDL_NAMESPACE_BEGIN

class WSDL_EXPORT SOAPConstants
{
public:
    // Namespace URIs.
    static const XMLCh NS_URI_SOAP[];

    // Element names.
    static const XMLCh ELEM_BODY[];
    static const XMLCh ELEM_HEADER[];
    static const XMLCh ELEM_HEADER_FAULT[];
    static const XMLCh ELEM_ADDRESS[];

    // Qualified element names.
    static QNamePtr Q_ELEM_SOAP_BINDING;
    static QNamePtr Q_ELEM_SOAP_BODY;
    static QNamePtr Q_ELEM_SOAP_HEADER;
    static QNamePtr Q_ELEM_SOAP_HEADER_FAULT;
    static QNamePtr Q_ELEM_SOAP_ADDRESS;
    static QNamePtr Q_ELEM_SOAP_OPERATION;
    static QNamePtr Q_ELEM_SOAP_FAULT;

    // Attribute names.
    static const XMLCh ATTR_TRANSPORT[];
    static const XMLCh ATTR_STYLE[];
    static const XMLCh ATTR_SOAP_ACTION[];
    static const XMLCh ATTR_PARTS[];
    static const XMLCh ATTR_USE[];
    static const XMLCh ATTR_ENCODING_STYLE[];
    static const XMLCh ATTR_PART[];
    
    // Extension of WSDL4C
    static const XMLCh STYLE_DOCUMENT[];
    static const XMLCh STYLE_RPC[];
    
	static void init();
	static void release();
};

WSDL_NAMESPACE_END

#endif /*SOAPCONSTANTS_HPP_*/
