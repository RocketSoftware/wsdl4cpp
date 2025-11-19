/*
 * %fv:OperationType.cpp-3 % 
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
 * (c) 2025 Rocket Software, Inc. or its affiliates
 */
/*******************************************************************************
date   refnum    version who description
120101 c29155    E103    ahn Determine operation type, oneway, requestresponse, etc correctly on RSD
date   refnum    version who description
*******************************************************************************/

#include <xercesc/util/XMLUniDefs.hpp>
#include "wsdl/OperationType.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

const XMLCh XMLCH_ONE_WAY[] = {
    chLatin_O, chLatin_N, chLatin_E, chUnderscore, 
    chLatin_W, chLatin_A, chLatin_Y, chNull };

const XMLCh XMLCH_REQUEST_RESPONSE[] = {
    chLatin_R, chLatin_E, chLatin_Q, chLatin_U, chLatin_E, chLatin_S, chLatin_T, chUnderscore, 
    chLatin_R, chLatin_E, chLatin_S, chLatin_P, chLatin_O, chLatin_N, chLatin_S, chLatin_E, chNull };

const XMLCh XMLCH_SOLICIT_RESPONSE[] = {
    chLatin_S, chLatin_O, chLatin_L, chLatin_I, chLatin_C, chLatin_I, chLatin_T, chUnderscore, 
    chLatin_R, chLatin_E, chLatin_S, chLatin_P, chLatin_O, chLatin_N, chLatin_S, chLatin_E, chNull };

const XMLCh XMLCH_NOTIFICATION[] = {
    chLatin_N, chLatin_O, chLatin_T, chLatin_I, 
    chLatin_F, chLatin_I, chLatin_C, chLatin_A, 
    chLatin_T, chLatin_I, chLatin_O, chLatin_N, chNull };

// @c29155 only a declaration here
OperationTypePtr OperationType::ONE_WAY;
OperationTypePtr OperationType::REQUEST_RESPONSE;
OperationTypePtr OperationType::SOLICIT_RESPONSE;
OperationTypePtr OperationType::NOTIFICATION;

OperationType::OperationType(XMLChString theId)
    : id(theId)
{
}

OperationType::~OperationType()
{
}

// @c29155 explicitly initialise
void OperationType::init()
{
    ONE_WAY = (OperationTypePtr)new OperationType(XMLCH_ONE_WAY);
    REQUEST_RESPONSE = (OperationTypePtr)new OperationType(XMLCH_REQUEST_RESPONSE);
    SOLICIT_RESPONSE = (OperationTypePtr)new OperationType(XMLCH_SOLICIT_RESPONSE);
    NOTIFICATION = (OperationTypePtr)new OperationType(XMLCH_NOTIFICATION);
}

// @c29155 explicitly release
void OperationType::release()
{
    ONE_WAY = (OperationTypePtr)0;
    REQUEST_RESPONSE = (OperationTypePtr)0;
    SOLICIT_RESPONSE = (OperationTypePtr)0;
    NOTIFICATION = (OperationTypePtr)0;
}

WSDL_NAMESPACE_END

