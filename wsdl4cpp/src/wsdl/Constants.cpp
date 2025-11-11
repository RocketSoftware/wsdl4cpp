/*
 * %fv:Constants.cpp-8 % 
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
 * 
 * History:
 * 
 * revision  date    refnum    version  who  description
 * -----------------------------------------------------------------------
 * 01-04     060509            9.SOAP   mzu  Migrated from WSDL4J
 * 05        070109  t85163    9.SOAP   mzu  Add constants for attribute extentions
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 */
#include "wsdl/wsdlxerces.hpp"
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/XMLString.hpp>

#include "wsdl/Constants.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

#define LOCAL_EXTERN

// rev05
LOCAL_EXTERN const XMLCh Constants::NS_URI_XMLNS[] = { 
	chLatin_h, chLatin_t, chLatin_t, chLatin_p, 
	chColon, chForwardSlash, chForwardSlash, 
	chLatin_w, chLatin_w, chLatin_w, chPeriod, 
	chLatin_w, chDigit_3, chPeriod, 
	chLatin_o, chLatin_r, chLatin_g, chForwardSlash, 
	chDigit_2, chDigit_0, chDigit_0, chDigit_0, chForwardSlash, 
	chLatin_x, chLatin_m, chLatin_l, chLatin_n, chLatin_s, chForwardSlash, 
	chNull };
 

//LOCAL_EXTERN const XMLCh Constants::EMPTY_XMLSTRING[] = { chNull };

LOCAL_EXTERN const XMLCh Constants::XMLSTR_TRUE[] = {
    chLatin_t, chLatin_r, chLatin_u, chLatin_e, chNull };

LOCAL_EXTERN const XMLCh Constants::NULL_NS_URI[] = { chNull };

LOCAL_EXTERN const XMLCh Constants::DEFAULT_NS_PREFIX[] = { chNull };

LOCAL_EXTERN const XMLCh Constants::ATTR_MESSAGE[] = {
    chLatin_m, chLatin_e, chLatin_s, chLatin_s, chLatin_a, 
    chLatin_g, chLatin_e, chNull };
    
LOCAL_EXTERN const XMLCh Constants::ATTR_BINDING[] = {
    chLatin_b, chLatin_i, chLatin_n, chLatin_d, 
    chLatin_i, chLatin_n, chLatin_g, chNull };
    
//  public static final String ATTR_XMLNS = "xmlns";
LOCAL_EXTERN const XMLCh Constants::ATTR_NAMESPACE[] = {
    chLatin_n, chLatin_a, chLatin_m, chLatin_e, 
    chLatin_s, chLatin_p, chLatin_a, chLatin_c, chLatin_e, chNull };
LOCAL_EXTERN const XMLCh Constants::ATTR_LOCATION[] = {
    chLatin_l, chLatin_o, chLatin_c, chLatin_a, chLatin_t, 
    chLatin_i, chLatin_o, chLatin_n, chNull };
LOCAL_EXTERN const XMLCh Constants::ATTR_REQUIRED[] = {
    chLatin_r, chLatin_e, chLatin_q, chLatin_u, chLatin_i, 
    chLatin_r, chLatin_e, chLatin_d, chNull };
    
LOCAL_EXTERN const XMLCh Constants::ATTR_ELEMENT[] = {
	chLatin_e, chLatin_l, chLatin_e, chLatin_m, chLatin_e, 
	chLatin_n, chLatin_t, chNull };

LOCAL_EXTERN const XMLCh Constants::ATTR_NAME[] = { 
	chLatin_n, chLatin_a, chLatin_m, chLatin_e, chNull };

LOCAL_EXTERN const XMLCh Constants::ATTR_PARAMETER_ORDER[] = { 
	chLatin_p, chLatin_a, chLatin_r, chLatin_a, 
	chLatin_m, chLatin_e, chLatin_t, chLatin_e, chLatin_r, 
	chLatin_O, chLatin_r, chLatin_d, chLatin_e, chLatin_r, chNull };
	
LOCAL_EXTERN const XMLCh Constants::ATTR_TYPE[] = { 
	chLatin_t, chLatin_y, chLatin_p, chLatin_e, chNull };

LOCAL_EXTERN const XMLCh Constants::ATTR_TARGET_NAMESPACE[] = {
	chLatin_t, chLatin_a, chLatin_r, chLatin_g, chLatin_e, chLatin_t, 
	chLatin_N, chLatin_a, chLatin_m, chLatin_e, 
	chLatin_s, chLatin_p, chLatin_a, chLatin_c, chLatin_e, chNull };
	
LOCAL_EXTERN const XMLCh Constants::NS_URI_WSDL[] = { 
    // http://schemas.xmlsoap.org/wsdl/
	chLatin_h, chLatin_t, chLatin_t, chLatin_p, 
	chColon, chForwardSlash, chForwardSlash, 
	chLatin_s, chLatin_c, chLatin_h, chLatin_e, chLatin_m, chLatin_a, chLatin_s, chPeriod, 
	chLatin_x, chLatin_m, chLatin_l, chLatin_s, chLatin_o, chLatin_a, chLatin_p, chPeriod, 
	chLatin_o, chLatin_r, chLatin_g, chForwardSlash, 
	chLatin_w, chLatin_s, chLatin_d, chLatin_l, chForwardSlash, 
	chNull };

LOCAL_EXTERN XMLCh Constants::ELEM_DEFINITIONS[] = {
    chLatin_d, chLatin_e, chLatin_f, chLatin_i, chLatin_n, chLatin_i, 
    chLatin_t, chLatin_i, chLatin_o, chLatin_n, chLatin_s, chNull};
LOCAL_EXTERN XMLCh Constants::ELEM_IMPORT[] = {
    chLatin_i, chLatin_m, chLatin_p, chLatin_o, chLatin_r, chLatin_t, chNull};
LOCAL_EXTERN XMLCh Constants::ELEM_TYPES[] = {
    chLatin_t, chLatin_y, chLatin_p, chLatin_e, chLatin_s, chNull};
LOCAL_EXTERN XMLCh Constants::ELEM_MESSAGE[] = {
    chLatin_m, chLatin_e, chLatin_s, chLatin_s, chLatin_a, chLatin_g, chLatin_e, chNull};
LOCAL_EXTERN XMLCh Constants::ELEM_PORT_TYPE[] = {
    chLatin_p, chLatin_o, chLatin_r, chLatin_t, 
    chLatin_T, chLatin_y, chLatin_p, chLatin_e, chNull};
LOCAL_EXTERN XMLCh Constants::ELEM_BINDING[] = {
    chLatin_b, chLatin_i, chLatin_n, chLatin_d, 
    chLatin_i, chLatin_n, chLatin_g, chNull};
LOCAL_EXTERN XMLCh Constants::ELEM_SERVICE[] = {
    chLatin_s, chLatin_e, chLatin_r, chLatin_v, chLatin_i, chLatin_c, chLatin_e, chNull};
LOCAL_EXTERN XMLCh Constants::ELEM_DOCUMENTATION[] = {
    chLatin_d, chLatin_o, chLatin_c, chLatin_u, 
    chLatin_m, chLatin_e, chLatin_n, chLatin_t, chLatin_a, 
    chLatin_t, chLatin_i, chLatin_o, chLatin_n, chNull};

LOCAL_EXTERN XMLCh Constants::ELEM_PART[] = {
    chLatin_p, chLatin_a, chLatin_r, chLatin_t, chNull};
LOCAL_EXTERN XMLCh Constants::ELEM_OPERATION[] = {
    chLatin_o, chLatin_p, chLatin_e, chLatin_r, chLatin_a, 
    chLatin_t, chLatin_i, chLatin_o, chLatin_n, chNull};
LOCAL_EXTERN XMLCh Constants::ELEM_INPUT[] = {
    chLatin_i, chLatin_n, chLatin_p, chLatin_u, chLatin_t, chNull};
LOCAL_EXTERN XMLCh Constants::ELEM_OUTPUT[] = {
    chLatin_o, chLatin_u, chLatin_t, chLatin_p, chLatin_u, chLatin_t, chNull};
LOCAL_EXTERN XMLCh Constants::ELEM_FAULT[] = {
    chLatin_f, chLatin_a, chLatin_u, chLatin_l, chLatin_t, chNull};
LOCAL_EXTERN XMLCh Constants::ELEM_PORT[] = {
    chLatin_p, chLatin_o, chLatin_r, chLatin_t, chNull};

  // Top-level qualified element names.
LOCAL_EXTERN QNamePtr Constants::Q_ELEM_DEFINITIONS;
LOCAL_EXTERN QNamePtr Constants::Q_ELEM_IMPORT;
LOCAL_EXTERN QNamePtr Constants::Q_ELEM_TYPES;
LOCAL_EXTERN QNamePtr Constants::Q_ELEM_MESSAGE;
LOCAL_EXTERN QNamePtr Constants::Q_ELEM_PORT_TYPE;
LOCAL_EXTERN QNamePtr Constants::Q_ELEM_BINDING;
LOCAL_EXTERN QNamePtr Constants::Q_ELEM_SERVICE;

LOCAL_EXTERN QNamePtr Constants::Q_ELEM_PART;
LOCAL_EXTERN QNamePtr Constants::Q_ELEM_OPERATION;
LOCAL_EXTERN QNamePtr Constants::Q_ELEM_INPUT;
LOCAL_EXTERN QNamePtr Constants::Q_ELEM_OUTPUT;
LOCAL_EXTERN QNamePtr Constants::Q_ELEM_FAULT;
LOCAL_EXTERN QNamePtr Constants::Q_ELEM_PORT;
LOCAL_EXTERN QNamePtr Constants::Q_ELEM_DOCUMENTATION;


LOCAL_EXTERN XMLChString::Vector Constants::STYLE_ONE_WAY;
LOCAL_EXTERN XMLChString::Vector Constants::STYLE_REQUEST_RESPONSE;
LOCAL_EXTERN XMLChString::Vector Constants::STYLE_SOLICIT_RESPONSE;
LOCAL_EXTERN XMLChString::Vector Constants::STYLE_NOTIFICATION;

  // Feature names.
LOCAL_EXTERN const XMLCh Constants::FEATURE_VERBOSE[] = { 
    chLatin_v, chLatin_e, chLatin_r, chLatin_b, chLatin_o, chLatin_s, chLatin_e, chNull };
LOCAL_EXTERN const XMLCh Constants::FEATURE_IMPORT_DOCUMENTS[] = { 
    chLatin_i, chLatin_m, chLatin_p, chLatin_o, chLatin_r, chLatin_t, 
    chLatin_D, chLatin_o, chLatin_c, chLatin_u, 
    chLatin_m, chLatin_e, chLatin_n, chLatin_t, chLatin_s, chNull };

// rev05 begin
LOCAL_EXTERN XMLChString::SetPtr Constants::FAULT_ATTR_NAMES_SET;

LOCAL_EXTERN XMLChString::SetPtr Constants::IMPORT_ATTR_NAMES_SET;

LOCAL_EXTERN XMLChString::SetPtr Constants::INPUT_ATTR_NAMES_SET;

LOCAL_EXTERN XMLChString::SetPtr Constants::OUTPUT_ATTR_NAMES_SET;

LOCAL_EXTERN XMLChString::SetPtr Constants::PART_ATTR_NAMES_SET;

LOCAL_EXTERN XMLChString::SetPtr Constants::PORTTYPE_ATTR_NAMES_SET;
// rev05 end

/**
 * Constants for WSDL4C extentions
 */
LOCAL_EXTERN const XMLCh Constants::ATTR_ARRAYTYPE[] = { 
    // "arrayType"
	chLatin_a, chLatin_r, chLatin_r, chLatin_a, chLatin_y, 
	chLatin_T, chLatin_y, chLatin_p, chLatin_e, 
	chNull };
	
void Constants::init() 
{
    	
   FAULT_ATTR_NAMES_SET = (XMLChString::SetPtr)new XMLChString::Set();
   FAULT_ATTR_NAMES_SET->insert((XMLChString)Constants::ATTR_NAME);
   FAULT_ATTR_NAMES_SET->insert((XMLChString)Constants::ATTR_MESSAGE);

   IMPORT_ATTR_NAMES_SET = (XMLChString::SetPtr)new XMLChString::Set();
   IMPORT_ATTR_NAMES_SET->insert((XMLChString)Constants::ATTR_NAMESPACE);
   IMPORT_ATTR_NAMES_SET->insert((XMLChString)Constants::ATTR_LOCATION);

   INPUT_ATTR_NAMES_SET = (XMLChString::SetPtr)new XMLChString::Set();
   INPUT_ATTR_NAMES_SET->insert((XMLChString)Constants::ATTR_NAME);
   INPUT_ATTR_NAMES_SET->insert((XMLChString)Constants::ATTR_MESSAGE);

   OUTPUT_ATTR_NAMES_SET = (XMLChString::SetPtr)new XMLChString::Set();
   OUTPUT_ATTR_NAMES_SET->insert((XMLChString)Constants::ATTR_NAME);
   OUTPUT_ATTR_NAMES_SET->insert((XMLChString)Constants::ATTR_MESSAGE);

   PART_ATTR_NAMES_SET = (XMLChString::SetPtr)new XMLChString::Set();
   PART_ATTR_NAMES_SET->insert((XMLChString)Constants::ATTR_NAME);
   PART_ATTR_NAMES_SET->insert((XMLChString)Constants::ATTR_TYPE);
   PART_ATTR_NAMES_SET->insert((XMLChString)Constants::ATTR_ELEMENT);

   PORTTYPE_ATTR_NAMES_SET = (XMLChString::SetPtr)new XMLChString::Set();
   PORTTYPE_ATTR_NAMES_SET->insert((XMLChString)Constants::ATTR_NAME);

// Top-level qualified element names.
	Q_ELEM_DEFINITIONS =
			(QNamePtr)new QName(NS_URI_WSDL, ELEM_DEFINITIONS);
	Q_ELEM_IMPORT =
			(QNamePtr)new QName(NS_URI_WSDL, ELEM_IMPORT);
	Q_ELEM_TYPES =
			(QNamePtr)new QName(NS_URI_WSDL, ELEM_TYPES);
	Q_ELEM_MESSAGE =
			(QNamePtr)new QName(NS_URI_WSDL, ELEM_MESSAGE);
	Q_ELEM_PORT_TYPE =
			(QNamePtr)new QName(NS_URI_WSDL, ELEM_PORT_TYPE);
	Q_ELEM_BINDING =
			(QNamePtr)new QName(NS_URI_WSDL, ELEM_BINDING);
	Q_ELEM_SERVICE =
			(QNamePtr)new QName(NS_URI_WSDL, ELEM_SERVICE);

	Q_ELEM_PART =
			(QNamePtr)new QName(NS_URI_WSDL, ELEM_PART);
	Q_ELEM_OPERATION =
			(QNamePtr)new QName(NS_URI_WSDL, ELEM_OPERATION);
	Q_ELEM_INPUT =
			(QNamePtr)new QName(NS_URI_WSDL, ELEM_INPUT);
	Q_ELEM_OUTPUT =
			(QNamePtr)new QName(NS_URI_WSDL, ELEM_OUTPUT);
	Q_ELEM_FAULT =
			(QNamePtr)new QName(NS_URI_WSDL, ELEM_FAULT);
	Q_ELEM_PORT =
			(QNamePtr)new QName(NS_URI_WSDL, ELEM_PORT);
	Q_ELEM_DOCUMENTATION = 
			(QNamePtr)new QName(NS_URI_WSDL, ELEM_DOCUMENTATION);

  // Used for determining the style of operations.
    STYLE_ONE_WAY.push_back(ELEM_INPUT);
    
    STYLE_REQUEST_RESPONSE.push_back(ELEM_INPUT);
    STYLE_REQUEST_RESPONSE.push_back(ELEM_OUTPUT);
    
    STYLE_SOLICIT_RESPONSE.push_back(ELEM_OUTPUT);
    STYLE_SOLICIT_RESPONSE.push_back(ELEM_INPUT);
    
    STYLE_NOTIFICATION.push_back(ELEM_OUTPUT);
    
}

void Constants::release() 
{
	STYLE_NOTIFICATION.clear();
	STYLE_REQUEST_RESPONSE.clear();
	STYLE_ONE_WAY.clear();

	  // Top-level qualified element names.
	Q_ELEM_DEFINITIONS = (QNamePtr)0;
	Q_ELEM_IMPORT = (QNamePtr)0;
	Q_ELEM_TYPES = (QNamePtr)0;
	Q_ELEM_MESSAGE = (QNamePtr)0;
	Q_ELEM_PORT_TYPE = (QNamePtr)0;
	Q_ELEM_BINDING = (QNamePtr)0;
	Q_ELEM_SERVICE = (QNamePtr)0;

	Q_ELEM_PART = (QNamePtr)0;
	Q_ELEM_OPERATION = (QNamePtr)0;
	Q_ELEM_INPUT = (QNamePtr)0;
	Q_ELEM_OUTPUT = (QNamePtr)0;
	Q_ELEM_FAULT = (QNamePtr)0;
	Q_ELEM_PORT = (QNamePtr)0;
	Q_ELEM_DOCUMENTATION = (QNamePtr)0;

   FAULT_ATTR_NAMES_SET->clear();
   IMPORT_ATTR_NAMES_SET->clear();
   INPUT_ATTR_NAMES_SET->clear();
   OUTPUT_ATTR_NAMES_SET->clear();
   PART_ATTR_NAMES_SET->clear();
   PORTTYPE_ATTR_NAMES_SET->clear();

   FAULT_ATTR_NAMES_SET = (XMLChString::SetPtr)0;
   IMPORT_ATTR_NAMES_SET = (XMLChString::SetPtr)0;
   INPUT_ATTR_NAMES_SET = (XMLChString::SetPtr)0;
   OUTPUT_ATTR_NAMES_SET = (XMLChString::SetPtr)0;
   PART_ATTR_NAMES_SET = (XMLChString::SetPtr)0;
   PORTTYPE_ATTR_NAMES_SET = (XMLChString::SetPtr)0;
}

WSDL_NAMESPACE_END
