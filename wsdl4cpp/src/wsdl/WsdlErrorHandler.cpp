/*
 * %fv:WsdlErrorHandler.cpp-4 % 
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
#include <iostream>
#include <string>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMError.hpp>
#include <xercesc/dom/DOMLocator.hpp>
#include "wsdl/WsdlErrorHandler.hpp"

//USING_STD

XERCES_CPP_NAMESPACE_USE
#ifdef XERCES_STD_QUALIFIER
#undef XERCES_STD_QUALIFIER
#endif
#define XERCES_STD_QUALIFIER std::
WSDL_NAMESPACE_BEGIN

WsdlErrorHandler::WsdlErrorHandler() :
    fSawErrors(false)
{
}

WsdlErrorHandler::~WsdlErrorHandler()
{
}

void WsdlErrorHandler::warning(const SAXParseException& toCatch)
{
    fSawErrors = true;
	XERCES_STD_QUALIFIER cerr << "Warning at file \"" << TO_LOCAL(toCatch.getSystemId())
		 << "\", line " << toCatch.getLineNumber()
		 << ", column " << toCatch.getColumnNumber()
         << "\n   Message: " << TO_LOCAL(toCatch.getMessage()) << XERCES_STD_QUALIFIER endl;
}

void WsdlErrorHandler::error(const SAXParseException& toCatch)
{
    fSawErrors = true;
    XERCES_STD_QUALIFIER cerr << "Error at file \"" << TO_LOCAL(toCatch.getSystemId())
		 << "\", line " << toCatch.getLineNumber()
		 << ", column " << toCatch.getColumnNumber()
         << "\n   Message: " << TO_LOCAL(toCatch.getMessage()) << XERCES_STD_QUALIFIER endl;
}

void WsdlErrorHandler::fatalError(const SAXParseException& toCatch)
{
    fSawErrors = true;
    XERCES_STD_QUALIFIER cerr << "Fatal Error at file \"" << TO_LOCAL(toCatch.getSystemId())
		 << "\", line " << toCatch.getLineNumber()
		 << ", column " << toCatch.getColumnNumber()
         << "\n   Message: " << TO_LOCAL(toCatch.getMessage()) << XERCES_STD_QUALIFIER endl;
}

void WsdlErrorHandler::resetErrors()
{
    fSawErrors = false;
}

WSDL_NAMESPACE_END

