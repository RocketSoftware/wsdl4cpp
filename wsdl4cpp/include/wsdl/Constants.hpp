/*
 * %fv:Constants.hpp-7 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
 * 
 * History:
 * 
 * revision  date    refnum    version  who  description
 * -----------------------------------------------------------------------
 * 01-03     060509            9.SOAP   mzu  Migrated from WSDL4J
 * 04        070109  t85163    9.SOAP   mzu  Add constants for attribute extentions
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 * 
 */
#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_
#include <xercesc/util/XercesDefs.hpp>

#include "wsdl/wsdlbas.hpp"
#include "wsdl/QName.hpp"

WSDL_NAMESPACE_BEGIN

//  // Namespace URIs.
//  public static final String NS_URI_WSDL =
//    "http://schemas.xmlsoap.org/wsdl/";
//
//
//  // Non top-level element names.

class WSDL_EXPORT Constants
{
public:

    static const XMLCh NS_URI_XMLNS[];

    static XMLChString::Vector STYLE_ONE_WAY;
    static XMLChString::Vector STYLE_REQUEST_RESPONSE;
    static XMLChString::Vector STYLE_SOLICIT_RESPONSE;
    static XMLChString::Vector STYLE_NOTIFICATION;

    //static const XMLCh EMPTY_XMLSTRING[];
    
    static const XMLCh XMLSTR_TRUE[];
    
  // Attribute names.
    static const XMLCh ATTR_MESSAGE[];
    static const XMLCh ATTR_BINDING[];
//  public static final String ATTR_XMLNS = "xmlns";
    static const XMLCh ATTR_NAMESPACE[];
    static const XMLCh ATTR_LOCATION[];
    static const XMLCh ATTR_REQUIRED[];
	static const XMLCh ATTR_ELEMENT[];
	static const XMLCh ATTR_NAME[];
	static const XMLCh ATTR_PARAMETER_ORDER[];
	static const XMLCh ATTR_TYPE[];
	static const XMLCh ATTR_TARGET_NAMESPACE[];
	
	static const XMLCh NULL_NS_URI[];
	static const XMLCh NS_URI_WSDL[];
	static const XMLCh DEFAULT_NS_PREFIX[];
	
	static XMLCh ELEM_DEFINITIONS[];
	static XMLCh ELEM_IMPORT[];
	static XMLCh ELEM_TYPES[];
	static XMLCh ELEM_MESSAGE[];
	static XMLCh ELEM_PORT_TYPE[];
	static XMLCh ELEM_BINDING[];
	static XMLCh ELEM_SERVICE[];
	static XMLCh ELEM_DOCUMENTATION[];
	static XMLCh ELEM_PART[];
	static XMLCh ELEM_OPERATION[];
	static XMLCh ELEM_INPUT[];
	static XMLCh ELEM_OUTPUT[];
	static XMLCh ELEM_FAULT[];
	static XMLCh ELEM_PORT[];
	
  // Top-level qualified element names.
    static QNamePtr Q_ELEM_DEFINITIONS;
    static QNamePtr Q_ELEM_IMPORT;
    static QNamePtr Q_ELEM_TYPES;
    static QNamePtr Q_ELEM_MESSAGE;
    static QNamePtr Q_ELEM_PORT_TYPE;
    static QNamePtr Q_ELEM_BINDING;
    static QNamePtr Q_ELEM_SERVICE;

    // Non top-level qualified element names.
    static QNamePtr Q_ELEM_DOCUMENTATION;
    static QNamePtr Q_ELEM_FAULT;
    static QNamePtr Q_ELEM_INPUT;
    static QNamePtr Q_ELEM_OPERATION;
    static QNamePtr Q_ELEM_OUTPUT;
    static QNamePtr Q_ELEM_PART;
    static QNamePtr Q_ELEM_PORT;

  // Feature names.
    static const XMLCh FEATURE_VERBOSE[];
    static const XMLCh FEATURE_IMPORT_DOCUMENTS[];
    
    // Native attribute names:
    static XMLChString::SetPtr FAULT_ATTR_NAMES_SET;
    static XMLChString::SetPtr IMPORT_ATTR_NAMES_SET;
    static XMLChString::SetPtr INPUT_ATTR_NAMES_SET;
    static XMLChString::SetPtr OUTPUT_ATTR_NAMES_SET;
    static XMLChString::SetPtr PART_ATTR_NAMES_SET;
    static XMLChString::SetPtr PORTTYPE_ATTR_NAMES_SET;

	////////////////////////////////////
	// Constants for WSDL4C extention //
	////////////////////////////////////

	/**
	 * Local name of "arrayType" attribute.
	 */
	static const XMLCh ATTR_ARRAYTYPE[];

	static void init();
	static void release();

};

WSDL_NAMESPACE_END

#endif /*CONSTANTS_HPP_*/
