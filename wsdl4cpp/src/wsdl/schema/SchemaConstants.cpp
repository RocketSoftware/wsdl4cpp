/*
 * %fv:SchemaConstants.cpp-3 % 
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
#include "wsdl/wsdlxerces.hpp"

#include <xercesc/util/XMLUniDefs.hpp>
#include "wsdl/Constants.hpp"
#include "wsdl/schema/SchemaConstants.hpp"
#include "wsdl/schema/Schema.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

    //Schema attribute names
const XMLCh SchemaConstants::ATTR_ID[] = {
    chLatin_i, chLatin_d, chNull
};
const XMLCh SchemaConstants::ATTR_SCHEMA_LOCATION[] = {
    chLatin_s, chLatin_c, chLatin_h, chLatin_e, chLatin_m, chLatin_a,
    chLatin_L, chLatin_o, chLatin_c, chLatin_a, chLatin_t, chLatin_i,
    chLatin_o, chLatin_n, chNull
};

    
    //Schema element names
const XMLCh SchemaConstants::ELEM_SCHEMA[] = {
    chLatin_s, chLatin_c, chLatin_h, chLatin_e, chLatin_m, chLatin_a, chNull
};
const XMLCh SchemaConstants::ELEM_INCLUDE[] = {
    chLatin_i, chLatin_n, chLatin_c, chLatin_l, chLatin_u, chLatin_d,
    chLatin_e, chNull
};
const XMLCh SchemaConstants::ELEM_REDEFINE[] = {
    chLatin_r, chLatin_e, chLatin_d, chLatin_e, chLatin_f, chLatin_i,
    chLatin_n, chLatin_e, chNull
};


//Schema uri
const XMLCh SchemaConstants::NS_URI_XSD_1999[] =
{ //        "http://www.w3.org/1999/XMLSchema"
    chLatin_h, chLatin_t, chLatin_t, chLatin_p, chColon, chForwardSlash,
    chForwardSlash, chLatin_w, chLatin_w, chLatin_w, chPeriod, chLatin_w,
    chDigit_3, chPeriod, chLatin_o, chLatin_r, chLatin_g, chForwardSlash,
    chDigit_1, chDigit_9, chDigit_9, chDigit_9, chForwardSlash,
    chLatin_X, chLatin_M, chLatin_L, chLatin_S,
    chLatin_c, chLatin_h, chLatin_e, chLatin_m, chLatin_a, chNull
};
const XMLCh SchemaConstants::NS_URI_XSD_2000[] =
{ //        "http://www.w3.org/2000/10/XMLSchema";
    chLatin_h, chLatin_t, chLatin_t, chLatin_p, chColon, chForwardSlash,
    chForwardSlash, chLatin_w, chLatin_w, chLatin_w, chPeriod, chLatin_w,
    chDigit_3, chPeriod, chLatin_o, chLatin_r, chLatin_g, chForwardSlash,
    chDigit_2, chDigit_0, chDigit_0, chDigit_0, chForwardSlash, chDigit_1, chDigit_0, chForwardSlash, 
    chLatin_X, chLatin_M, chLatin_L, chLatin_S,
    chLatin_c, chLatin_h, chLatin_e, chLatin_m, chLatin_a, chNull
};

const XMLCh SchemaConstants::NS_URI_XSD_2001[] = {
    chLatin_h, chLatin_t, chLatin_t, chLatin_p, chColon, chForwardSlash,
    chForwardSlash, chLatin_w, chLatin_w, chLatin_w, chPeriod, chLatin_w,
    chDigit_3, chPeriod, chLatin_o, chLatin_r, chLatin_g, chForwardSlash,
    chDigit_2, chDigit_0, chDigit_0, chDigit_1, chForwardSlash,
    chLatin_X, chLatin_M, chLatin_L, chLatin_S,
    chLatin_c, chLatin_h, chLatin_e, chLatin_m, chLatin_a, chNull
};
    
    //Schema qnames
QNamePtr SchemaConstants::Q_ELEM_XSD_1999;
QNamePtr SchemaConstants::Q_ELEM_XSD_2000;
QNamePtr SchemaConstants::Q_ELEM_XSD_2001;
QName::PtrSetPtr SchemaConstants::XSD_QNAME_LIST;
    
    //Schema import qnames
QNamePtr SchemaConstants::Q_ELEM_IMPORT_XSD_1999;
QNamePtr SchemaConstants::Q_ELEM_IMPORT_XSD_2000;
QNamePtr SchemaConstants::Q_ELEM_IMPORT_XSD_2001;
QName::PtrSetPtr SchemaConstants::XSD_IMPORT_QNAME_LIST;


    //Schema include qnames
QNamePtr SchemaConstants::Q_ELEM_INCLUDE_XSD_1999;
QNamePtr SchemaConstants::Q_ELEM_INCLUDE_XSD_2000;
QNamePtr SchemaConstants::Q_ELEM_INCLUDE_XSD_2001;
QName::PtrSetPtr SchemaConstants::XSD_INCLUDE_QNAME_LIST ;

    //Schema redefine qnames
QNamePtr SchemaConstants::Q_ELEM_REDEFINE_XSD_1999;
QNamePtr SchemaConstants::Q_ELEM_REDEFINE_XSD_2000;
QNamePtr SchemaConstants::Q_ELEM_REDEFINE_XSD_2001;
QName::PtrSetPtr SchemaConstants::XSD_REDEFINE_QNAME_LIST;

QNamePtr Schema::DEFAULT_ELEM_TYPE = SchemaConstants::Q_ELEM_XSD_2001;

void SchemaConstants::init() 
{
    //Schema qnames
    Q_ELEM_XSD_1999 =
        (QNamePtr)new QName(NS_URI_XSD_1999, ELEM_SCHEMA);
    Q_ELEM_XSD_2000 =
        (QNamePtr)new QName(NS_URI_XSD_2000, ELEM_SCHEMA);
    Q_ELEM_XSD_2001 =
        (QNamePtr)new QName(NS_URI_XSD_2001, ELEM_SCHEMA);

	XSD_QNAME_LIST = (QName::PtrSetPtr)new QName::PtrSet();
	XSD_QNAME_LIST->insert(Q_ELEM_XSD_1999);
	XSD_QNAME_LIST->insert(Q_ELEM_XSD_2000);
	XSD_QNAME_LIST->insert(Q_ELEM_XSD_2001);
    
    //Schema import qnames
    Q_ELEM_IMPORT_XSD_1999 =
        (QNamePtr)new QName(NS_URI_XSD_1999, Constants::ELEM_IMPORT);
    Q_ELEM_IMPORT_XSD_2000 =
        (QNamePtr)new QName(NS_URI_XSD_2000, Constants::ELEM_IMPORT);
    Q_ELEM_IMPORT_XSD_2001 =
        (QNamePtr)new QName(NS_URI_XSD_2001, Constants::ELEM_IMPORT);

	XSD_IMPORT_QNAME_LIST = (QName::PtrSetPtr)new QName::PtrSet();
	XSD_IMPORT_QNAME_LIST->insert(Q_ELEM_IMPORT_XSD_1999);
	XSD_IMPORT_QNAME_LIST->insert(Q_ELEM_IMPORT_XSD_2000);
	XSD_IMPORT_QNAME_LIST->insert(Q_ELEM_IMPORT_XSD_2001);


    //Schema include qnames
    Q_ELEM_INCLUDE_XSD_1999 =
        (QNamePtr)new QName(NS_URI_XSD_1999, ELEM_INCLUDE);
    Q_ELEM_INCLUDE_XSD_2000 =
        (QNamePtr)new QName(NS_URI_XSD_2000, ELEM_INCLUDE);
    Q_ELEM_INCLUDE_XSD_2001 =
        (QNamePtr)new QName(NS_URI_XSD_2001, ELEM_INCLUDE);

	XSD_INCLUDE_QNAME_LIST = (QName::PtrSetPtr)new QName::PtrSet();
	XSD_INCLUDE_QNAME_LIST->insert(Q_ELEM_INCLUDE_XSD_1999);
	XSD_INCLUDE_QNAME_LIST->insert(Q_ELEM_INCLUDE_XSD_2000);
	XSD_INCLUDE_QNAME_LIST->insert(Q_ELEM_INCLUDE_XSD_2001);

    //Schema redefine qnames
    Q_ELEM_REDEFINE_XSD_1999 =
        (QNamePtr)new QName(NS_URI_XSD_1999, ELEM_REDEFINE);
    Q_ELEM_REDEFINE_XSD_2000 =
        (QNamePtr)new QName(NS_URI_XSD_2000, ELEM_REDEFINE);
    Q_ELEM_REDEFINE_XSD_2001 =
        (QNamePtr)new QName(NS_URI_XSD_2001, ELEM_REDEFINE);

	XSD_REDEFINE_QNAME_LIST = (QName::PtrSetPtr)new QName::PtrSet();
	XSD_REDEFINE_QNAME_LIST->insert(Q_ELEM_REDEFINE_XSD_1999);
	XSD_REDEFINE_QNAME_LIST->insert(Q_ELEM_REDEFINE_XSD_2000);
	XSD_REDEFINE_QNAME_LIST->insert(Q_ELEM_REDEFINE_XSD_2001);

    Schema::DEFAULT_ELEM_TYPE = Q_ELEM_XSD_2001;
}

void SchemaConstants::release() 
{
    Schema::DEFAULT_ELEM_TYPE = (QNamePtr)0;

    //Schema qnames
	XSD_QNAME_LIST->clear();
	XSD_QNAME_LIST = (QName::PtrSetPtr)0;
    Q_ELEM_XSD_1999 = (QNamePtr)0;
    Q_ELEM_XSD_2000 = (QNamePtr)0;
    Q_ELEM_XSD_2001 = (QNamePtr)0;
    
    //Schema import qnames
	XSD_IMPORT_QNAME_LIST->clear();
	XSD_IMPORT_QNAME_LIST = (QName::PtrSetPtr)0;
    Q_ELEM_IMPORT_XSD_1999 = (QNamePtr)0;
    Q_ELEM_IMPORT_XSD_2000 = (QNamePtr)0;
    Q_ELEM_IMPORT_XSD_2001 = (QNamePtr)0;

    //Schema include qnames
	XSD_INCLUDE_QNAME_LIST->clear();
	XSD_INCLUDE_QNAME_LIST = (QName::PtrSetPtr)0;
    Q_ELEM_INCLUDE_XSD_1999 = (QNamePtr)0;
    Q_ELEM_INCLUDE_XSD_2000 = (QNamePtr)0;
    Q_ELEM_INCLUDE_XSD_2001 = (QNamePtr)0;

    //Schema redefine qnames
	XSD_REDEFINE_QNAME_LIST->clear();
	XSD_REDEFINE_QNAME_LIST = (QName::PtrSetPtr)0;
    Q_ELEM_REDEFINE_XSD_1999 = (QNamePtr)0;
    Q_ELEM_REDEFINE_XSD_2000 = (QNamePtr)0;
    Q_ELEM_REDEFINE_XSD_2001 = (QNamePtr)0;


}

WSDL_NAMESPACE_END
