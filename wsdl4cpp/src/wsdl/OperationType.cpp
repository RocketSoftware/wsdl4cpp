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

const OperationTypePtr OperationType::ONE_WAY(
    new OperationType(XMLCH_ONE_WAY));
const OperationTypePtr OperationType::REQUEST_RESPONSE(
    new OperationType(XMLCH_REQUEST_RESPONSE));
const OperationTypePtr OperationType::SOLICIT_RESPONSE(
    new OperationType(XMLCH_SOLICIT_RESPONSE));
const OperationTypePtr OperationType::NOTIFICATION(
    new OperationType(XMLCH_NOTIFICATION));

OperationType::OperationType(XMLChString theId)
    : id(theId)
{
}

OperationType::~OperationType()
{
}

WSDL_NAMESPACE_END

