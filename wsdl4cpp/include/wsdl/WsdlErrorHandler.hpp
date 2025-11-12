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
/*
 * From release 1.0.0, WSDL4CPP is under the Eclipse Public License - v 2.0 (EPL 2.0)
 *
 * (c) Rocket Software, Inc. or its affiliates
 */
/*******************************************************************************
date   refnum    version who description
120907 b29663    E110    ahn better error reporting
date   refnum    version who description
*******************************************************************************/
#ifndef WSDLERRORHANDLER_HPP_
#define WSDLERRORHANDLER_HPP_
#include <string>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/util/XMLExceptMsgs.hpp>
#include <xercesc/framework/XMLErrorReporter.hpp>
#include "wsdl/wsdlbas.hpp"

WSDL_NAMESPACE_BEGIN

XERCES_CPP_NAMESPACE_USE

class WsdlErrorHandler;
DEFINE_PTR(WsdlErrorHandler);

// ---------------------------------------------------------------------------
//  Simple error handler deriviative to install on parser
//  @b29663 we also need a user defined error reporter for DOM XSD parsers
// ---------------------------------------------------------------------------
class WSDL_EXPORT WsdlErrorHandler : public XERCES_CPP_NAMESPACE_QUALIFIER ErrorHandler
                                    , public XERCES_CPP_NAMESPACE_QUALIFIER XMLErrorReporter
{
public:
    // @ b29663 in order of severity
    enum ErrType
    {
        ErrType_Unknown
        , ErrType_Warning
        , ErrType_Error
        , ErrType_Fatal
    };

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
    const char* getMessage();
    ErrType getErrorType();
    XMLExcepts::Codes getErrorCode();

    // -----------------------------------------------------------------------
    //  Implementation of the DOM ErrorHandler interface
    // -----------------------------------------------------------------------
    void resetErrors();

    // -----------------------------------------------------------------------
    //  @b29663 Implementation of the XMLErrorReporter interface
    // -----------------------------------------------------------------------
    void error
    (
        const   unsigned int        errCode
        , const XMLCh* const        errDomain
        , const XERCES_CPP_NAMESPACE_QUALIFIER XMLErrorReporter::ErrTypes type
        , const XMLCh* const        errorText
        , const XMLCh* const        systemId
        , const XMLCh* const        publicId
        , const XMLFileLoc          lineNum
        , const XMLFileLoc          colNum
    );


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
    ErrType fType;
    std::string fMessage;
    XMLExcepts::Codes ferrCode;
};

inline bool WsdlErrorHandler::getSawErrors() const
{
    return fSawErrors;
}

inline const char* WsdlErrorHandler::getMessage()
{
    return fMessage.c_str();
}

inline WsdlErrorHandler::ErrType WsdlErrorHandler::getErrorType()
{
    return fType;
}

inline XMLExcepts::Codes WsdlErrorHandler::getErrorCode()
{
    return ferrCode;
}

WSDL_NAMESPACE_END

#endif /*WSDLERRORHANDLER_HPP_*/
