/*
 * %fv:SOAPConstants.cpp-7 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#include "wsdl/wsdlxerces.hpp"

#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/XMLString.hpp>

#include "wsdl/Constants.hpp"
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/soap/SOAPAddress.hpp"
#include "wsdl/soap/SOAPBinding.hpp"
#include "wsdl/soap/SOAPBody.hpp"
#include "wsdl/soap/SOAPFault.hpp"
#include "wsdl/soap/SOAPHeader.hpp"
#include "wsdl/soap/SOAPHeaderFault.hpp"
#include "wsdl/soap/SOAPOperation.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

// Namespace URIs.
const XMLCh SOAPConstants::NS_URI_SOAP[] = { 
    chLatin_h, chLatin_t, chLatin_t, chLatin_p, 
    chColon, chForwardSlash, chForwardSlash, 
    chLatin_s, chLatin_c, chLatin_h, chLatin_e, chLatin_m, chLatin_a, chLatin_s, 
    chPeriod, chLatin_x, chLatin_m, chLatin_l, chLatin_s, chLatin_o, chLatin_a, chLatin_p, 
    chPeriod, chLatin_o, chLatin_r, chLatin_g, chForwardSlash, 
    chLatin_w, chLatin_s, chLatin_d, chLatin_l, chForwardSlash, 
    chLatin_s, chLatin_o, chLatin_a, chLatin_p, chForwardSlash, 
    chNull };

	// Element names.
const XMLCh SOAPConstants::ELEM_BODY[] = {
    chLatin_b, chLatin_o, chLatin_d, chLatin_y, chNull };
const XMLCh SOAPConstants::ELEM_HEADER[] = {
    chLatin_h, chLatin_e, chLatin_a, chLatin_d, 
    chLatin_e, chLatin_r, chNull };
const XMLCh SOAPConstants::ELEM_HEADER_FAULT[] = {
    chLatin_h, chLatin_e, chLatin_a, chLatin_d, chLatin_e, 
    chLatin_r, chLatin_f, chLatin_a, chLatin_u, chLatin_l, 
    chLatin_t, chNull };
const XMLCh SOAPConstants::ELEM_ADDRESS[] = { 
    chLatin_a, chLatin_d, chLatin_d, chLatin_r, 
    chLatin_e, chLatin_s, chLatin_s, 
    chNull };
//
//  // Qualified element names.
QNamePtr SOAPConstants::Q_ELEM_SOAP_BINDING;
QNamePtr SOAPConstants::Q_ELEM_SOAP_BODY;
QNamePtr SOAPConstants::Q_ELEM_SOAP_HEADER;
QNamePtr SOAPConstants::Q_ELEM_SOAP_HEADER_FAULT;
QNamePtr SOAPConstants::Q_ELEM_SOAP_ADDRESS;
QNamePtr SOAPConstants::Q_ELEM_SOAP_OPERATION;
QNamePtr SOAPConstants::Q_ELEM_SOAP_FAULT;
    
//
//  // Attribute names.
const XMLCh SOAPConstants::ATTR_TRANSPORT[] = {
    chLatin_t, chLatin_r, chLatin_a, chLatin_n, chLatin_s, 
    chLatin_p, chLatin_o, chLatin_r, chLatin_t, chNull };
const XMLCh SOAPConstants::ATTR_STYLE[] = {
    chLatin_s, chLatin_t, chLatin_y, chLatin_l, chLatin_e, chNull };
const XMLCh SOAPConstants::ATTR_SOAP_ACTION[] = {
    chLatin_s, chLatin_o, chLatin_a, chLatin_p, 
    chLatin_A, chLatin_c, chLatin_t, chLatin_i, chLatin_o, chLatin_n, chNull };
const XMLCh SOAPConstants::ATTR_PARTS[] = {
    chLatin_p, chLatin_a, chLatin_r, chLatin_t, chLatin_s, chNull };
const XMLCh SOAPConstants::ATTR_USE[] = {
    chLatin_u, chLatin_s, chLatin_e, chNull };
const XMLCh SOAPConstants::ATTR_ENCODING_STYLE[] = {
    chLatin_e, chLatin_n, chLatin_c, chLatin_o, 
    chLatin_d, chLatin_i, chLatin_n, chLatin_g, 
    chLatin_S, chLatin_t, chLatin_y, chLatin_l, chLatin_e, chNull };
const XMLCh SOAPConstants::ATTR_PART[] = {
    chLatin_p, chLatin_a, chLatin_r, chLatin_t, chNull };
    
    // Extension of WSDL4C
const XMLCh SOAPConstants::STYLE_DOCUMENT[] = {
    chLatin_d, chLatin_o, chLatin_c, chLatin_u, 
    chLatin_m, chLatin_e, chLatin_n, chLatin_t, chNull };
const XMLCh SOAPConstants::STYLE_RPC[] = {
    chLatin_r, chLatin_p, chLatin_c, chNull };

QNamePtr SOAPAddress::DEFAULT_ELEM_TYPE = SOAPConstants::Q_ELEM_SOAP_ADDRESS;
QNamePtr SOAPBinding::DEFAULT_ELEM_TYPE = SOAPConstants::Q_ELEM_SOAP_BINDING;
QNamePtr SOAPBody::DEFAULT_ELEM_TYPE = SOAPConstants::Q_ELEM_SOAP_BODY;
QNamePtr SOAPFault::DEFAULT_ELEM_TYPE = SOAPConstants::Q_ELEM_SOAP_FAULT;
QNamePtr SOAPHeader::DEFAULT_ELEM_TYPE = SOAPConstants::Q_ELEM_SOAP_HEADER;
QNamePtr SOAPHeaderFault::DEFAULT_ELEM_TYPE = SOAPConstants::Q_ELEM_SOAP_HEADER_FAULT;
QNamePtr SOAPOperation::DEFAULT_ELEM_TYPE = SOAPConstants::Q_ELEM_SOAP_OPERATION;
    
void SOAPConstants::init() 
{
    Q_ELEM_SOAP_BINDING = 
        (QNamePtr)new QName(NS_URI_SOAP, Constants::ELEM_BINDING);
    Q_ELEM_SOAP_BODY = 
        (QNamePtr)new QName(NS_URI_SOAP, ELEM_BODY);
    Q_ELEM_SOAP_HEADER = 
        (QNamePtr)new QName(NS_URI_SOAP, ELEM_HEADER);
    Q_ELEM_SOAP_HEADER_FAULT = 
        (QNamePtr)new QName(NS_URI_SOAP, ELEM_HEADER_FAULT);
    Q_ELEM_SOAP_ADDRESS = 
        (QNamePtr)new QName(NS_URI_SOAP, ELEM_ADDRESS);
    Q_ELEM_SOAP_OPERATION = 
        (QNamePtr)new QName(NS_URI_SOAP, Constants::ELEM_OPERATION);
    Q_ELEM_SOAP_FAULT = 
        (QNamePtr)new QName(NS_URI_SOAP, Constants::ELEM_FAULT);

    SOAPAddress::DEFAULT_ELEM_TYPE = Q_ELEM_SOAP_ADDRESS;
    SOAPBinding::DEFAULT_ELEM_TYPE = Q_ELEM_SOAP_BINDING;
    SOAPBody::DEFAULT_ELEM_TYPE = Q_ELEM_SOAP_BODY;
    SOAPFault::DEFAULT_ELEM_TYPE = Q_ELEM_SOAP_FAULT;
    SOAPHeader::DEFAULT_ELEM_TYPE = Q_ELEM_SOAP_HEADER;
    SOAPHeaderFault::DEFAULT_ELEM_TYPE = Q_ELEM_SOAP_HEADER_FAULT;
    SOAPOperation::DEFAULT_ELEM_TYPE = Q_ELEM_SOAP_OPERATION;
}

void SOAPConstants::release() 
{
    SOAPAddress::DEFAULT_ELEM_TYPE = (QNamePtr)0;
    SOAPBinding::DEFAULT_ELEM_TYPE = (QNamePtr)0;
    SOAPBody::DEFAULT_ELEM_TYPE = (QNamePtr)0;
    SOAPFault::DEFAULT_ELEM_TYPE = (QNamePtr)0;
    SOAPHeader::DEFAULT_ELEM_TYPE = (QNamePtr)0;
    SOAPHeaderFault::DEFAULT_ELEM_TYPE = (QNamePtr)0;
    SOAPOperation::DEFAULT_ELEM_TYPE = (QNamePtr)0;

	Q_ELEM_SOAP_BINDING = (QNamePtr)0;
    Q_ELEM_SOAP_BODY = (QNamePtr)0;
    Q_ELEM_SOAP_HEADER = (QNamePtr)0;
    Q_ELEM_SOAP_HEADER_FAULT = (QNamePtr)0;
    Q_ELEM_SOAP_ADDRESS = (QNamePtr)0;
    Q_ELEM_SOAP_OPERATION = (QNamePtr)0;
    Q_ELEM_SOAP_FAULT = (QNamePtr)0;
}

WSDL_NAMESPACE_END
