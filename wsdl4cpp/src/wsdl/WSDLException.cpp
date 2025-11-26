/*
 * %fv:WSDLException.cpp-5 % 
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

#include "wsdl/wsdlxerces.hpp"
#include <iostream>
#include "wsdl/WSDLException.hpp"

USING_STD

WSDL_NAMESPACE_BEGIN

const char WSDLException::ACCESS_ERROR[] = "ACCESS_ERROR";
const char WSDLException::INVALID_WSDL[] = "INVALID_WSDL";
const char WSDLException::PARSER_ERROR[] = "PARSER_ERROR";
const char WSDLException::OTHER_ERROR[] = "OTHER_ERROR";
const char WSDLException::CONFIGURATION_ERROR[] = "CONFIGURATION_ERROR";
const char WSDLException::UNBOUND_PREFIX[] = "UNBOUND_PREFIX";
const char WSDLException::NO_PREFIX_SPECIFIED[] = "NO_PREFIX_SPECIFIED";

WSDLException::WSDLException()
{
}

WSDLException::WSDLException(string exCode, string msg)
	: faultCode (exCode) , message(msg)
{
}

WSDLException::WSDLException(const WSDLException &other)
	: faultCode(other.faultCode), message(other.message)
{
}

WSDLException::~WSDLException() throw()
{
}

const char* WSDLException::what() const throw() {
    static std::string gMessage;
    stringstream ss;
    ss << "WSDLException: faultCode " << faultCode << ", "
       << message;
    gMessage= ss.str();
    return gMessage.c_str();
//    return "WSDLException";
}

WSDL_NAMESPACE_END
