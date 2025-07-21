/*
 * %fv:SchemaConstants.hpp-3 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#ifndef SCHEMACONSTANTS_HPP_
#define SCHEMACONSTANTS_HPP_

#include "wsdl/wsdlbas.hpp"
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/QName.hpp"

WSDL_NAMESPACE_BEGIN

/**
 * Constants used for handling XML Schemas
 * 
 * @author Ming Zhu <ming.zhu@compuware.com>
 */
class WSDL_EXPORT SchemaConstants 
{
public:
    //Schema attribute names
    static const XMLCh ATTR_ID[];
    static const XMLCh ATTR_SCHEMA_LOCATION[];
    
    //Schema element names
    static const XMLCh ELEM_SCHEMA[];
    static const XMLCh ELEM_INCLUDE[];
    static const XMLCh ELEM_REDEFINE[];

    //Schema uri
    static const XMLCh NS_URI_XSD_1999[];
    static const XMLCh NS_URI_XSD_2000[];
    static const XMLCh NS_URI_XSD_2001[];
    
    //Schema qnames
    static QNamePtr Q_ELEM_XSD_1999;
    static QNamePtr Q_ELEM_XSD_2000;
    static QNamePtr Q_ELEM_XSD_2001; // Supported by Xerces
    static QName::PtrSetPtr XSD_QNAME_LIST;
    
    //Schema import qnames
    static QNamePtr Q_ELEM_IMPORT_XSD_1999;
    static QNamePtr Q_ELEM_IMPORT_XSD_2000;
    static QNamePtr Q_ELEM_IMPORT_XSD_2001;
    static QName::PtrSetPtr XSD_IMPORT_QNAME_LIST;


    //Schema include qnames
    static QNamePtr Q_ELEM_INCLUDE_XSD_1999;
    static QNamePtr Q_ELEM_INCLUDE_XSD_2000;
    static QNamePtr Q_ELEM_INCLUDE_XSD_2001;
    static QName::PtrSetPtr XSD_INCLUDE_QNAME_LIST;

    //Schema redefine qnames
    static QNamePtr Q_ELEM_REDEFINE_XSD_1999;
    static QNamePtr Q_ELEM_REDEFINE_XSD_2000;
    static QNamePtr Q_ELEM_REDEFINE_XSD_2001;
    static QName::PtrSetPtr XSD_REDEFINE_QNAME_LIST;

	static void init();
	static void release();
};

WSDL_NAMESPACE_END

#endif /*SCHEMACONSTANTS_HPP_*/
