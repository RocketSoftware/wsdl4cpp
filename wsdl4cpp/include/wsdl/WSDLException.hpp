/*
 * %fv:WSDLException.hpp-3 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#ifndef WSDLEXCEPTION_HPP_
#define WSDLEXCEPTION_HPP_
#include <exception>
#include <sstream>
#include <xercesc/util/XMLString.hpp>

#include "wsdl/wsdlbas.hpp"
#include "wsdl/wsdlxerces.hpp"


WSDL_NAMESPACE_BEGIN

class WSDLException;

DEFINE_PTR(WSDLException);

class WSDL_EXPORT WSDLException : public std::exception
{
public:
    static const char ACCESS_ERROR[];
    static const char INVALID_WSDL[];
    static const char PARSER_ERROR[];
    static const char OTHER_ERROR[];
    static const char CONFIGURATION_ERROR[];
    static const char UNBOUND_PREFIX[];
    static const char NO_PREFIX_SPECIFIED[];

//    enum ExceptionCode {
//         INVALID_WSDL   = 1,
//         PARSER_ERROR   = 2
//        };
//        
	WSDLException();
	WSDLException(std::string code, std::string message);
	WSDLException(const WSDLException &other);
	virtual ~WSDLException() throw();
	
	virtual const char* what() const throw();
	
	virtual std::string getMessage() { return message; }
	virtual void setMessage(std::string msg) { message = msg; }
	
	virtual std::string getFaultCode() const { return faultCode; }
	virtual void setFaultCode(std::string aCode) { faultCode = aCode; }

	//TODO: setLocation
	
private:
	std::string faultCode;
	std::string message;
	
};

WSDL_NAMESPACE_END

#endif /*WSDLEXCEPTION_HPP_*/
