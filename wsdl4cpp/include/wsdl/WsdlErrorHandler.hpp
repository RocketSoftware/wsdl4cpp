/*
 * %fv: WsdlErrorHandler.hpp-2 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#ifndef WSDLERRORHANDLER_HPP_
#define WSDLERRORHANDLER_HPP_
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include "wsdl/wsdlbas.hpp"

WSDL_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  Simple error handler deriviative to install on parser
// ---------------------------------------------------------------------------
class WSDL_EXPORT WsdlErrorHandler : public XERCES_CPP_NAMESPACE_QUALIFIER ErrorHandler
{
public:
	WsdlErrorHandler();
	virtual ~WsdlErrorHandler();

    // -----------------------------------------------------------------------
    //  Implementation of the error handler interface
    // -----------------------------------------------------------------------
    void warning(const XERCES_CPP_NAMESPACE_QUALIFIER SAXParseException& toCatch);
    void error(const XERCES_CPP_NAMESPACE_QUALIFIER SAXParseException& toCatch);
    void fatalError(const XERCES_CPP_NAMESPACE_QUALIFIER SAXParseException& toCatch);

    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------
    bool getSawErrors() const;


    // -----------------------------------------------------------------------
    //  Implementation of the DOM ErrorHandler interface
    // -----------------------------------------------------------------------
    void resetErrors();


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    WsdlErrorHandler(const WsdlErrorHandler&);
    void operator=(const WsdlErrorHandler&);


    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fSawErrors
    //      This is set if we get any errors, and is queryable via a getter
    //      method. Its used by the main code to suppress output if there are
    //      errors.
    // -----------------------------------------------------------------------
    bool    fSawErrors;
};

inline bool WsdlErrorHandler::getSawErrors() const
{
    return fSawErrors;
}

WSDL_NAMESPACE_END

#endif /*WSDLERRORHANDLER_HPP_*/
