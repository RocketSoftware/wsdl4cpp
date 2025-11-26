/*
 * %fv:WsdlErrorHandler.cpp-4 % 
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
/*******************************************************************************
date   refnum    version who description
120907 b29663    E110    ahn better error reporting
180907 b29663;1  E110    ahn better error reporting, remove unknown source messages
date   refnum    version who description
*******************************************************************************/
#include "wsdl/wsdlxerces.hpp"
#include <iostream>
#include <sstream>                                  // @b29663
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
    , fType(ErrType_Unknown)
    , ferrCode(XMLExcepts::NoError)
{
}

WsdlErrorHandler::~WsdlErrorHandler()
{
}

void WsdlErrorHandler::warning(const SAXParseException& toCatch)
{
    error(
          0                                     // const unsigned int errCode
        , (const XMLCh* const)0                 // errDomain
        , XMLErrorReporter::ErrType_Warning     // const XMLErrorReporter::ErrTypes type
        , toCatch.getMessage()                  // const XMLCh* const        errorText
        , toCatch.getSystemId()                 // const XMLCh* const        systemId
        , toCatch.getPublicId()                 // const XMLCh* const        publicId
        , toCatch.getLineNumber()               // const XMLSSize_t          lineNum
        , toCatch.getColumnNumber());             // const XMLSSize_t          colNum)

}

void WsdlErrorHandler::error(const SAXParseException& toCatch)
{
    error(
          0                                     // const unsigned int errCode
        , (const XMLCh* const)0                 // errDomain
        , XMLErrorReporter::ErrType_Error       // const XMLErrorReporter::ErrTypes type
        , toCatch.getMessage()                  // const XMLCh* const        errorText
        , toCatch.getSystemId()                 // const XMLCh* const        systemId
        , toCatch.getPublicId()                 // const XMLCh* const        publicId
        , toCatch.getLineNumber()               // const XMLSSize_t          lineNum
        , toCatch.getColumnNumber());             // const XMLSSize_t          colNum)

}

void WsdlErrorHandler::fatalError(const SAXParseException& toCatch)
{
    error(
        toCatch.getErrorCode()                  // const unsigned int errCode
        , (const XMLCh* const)0                 // errDomain
        , XMLErrorReporter::ErrType_Fatal       // const XMLErrorReporter::ErrTypes type
        , toCatch.getMessage()                  // const XMLCh* const        errorText
        , toCatch.getSystemId()                 // const XMLCh* const        systemId
        , toCatch.getPublicId()                 // const XMLCh* const        publicId
        , toCatch.getLineNumber()               // const XMLSSize_t          lineNum
        , toCatch.getColumnNumber());             // const XMLSSize_t          colNum)
}

void WsdlErrorHandler::resetErrors()
{
    fSawErrors = false;
}

// @b29663
void WsdlErrorHandler::error(
        const unsigned int          errCode
        , const XMLCh* const        errDomain
        , const XMLErrorReporter::ErrTypes type
        , const XMLCh* const        errorText
        , const XMLCh* const        systemId
        , const XMLCh* const        publicId
        , const XMLFileLoc          lineNum
        , const XMLFileLoc          colNum)
{
    fSawErrors = true;
    ferrCode = (XMLExcepts::Codes)errCode;
    // @b29663;1 restructure to remove useless bits
    if ((systemId && *systemId) || (publicId && *publicId))
    {
        if (!fMessage.empty())
            fMessage += "\n";

        if (type == XMLErrorReporter::ErrType_Warning)
        {
            fMessage += "Warning ";
            if (fType < ErrType_Warning)
                fType = ErrType_Warning;
        }
        else if (type == XMLErrorReporter::ErrType_Error)
        {
            fMessage += "Error ";
            if (fType < ErrType_Error)
                fType = ErrType_Error;
        }
        else if (type == XMLErrorReporter::ErrType_Fatal)
        {
            fMessage += "Fatal Error ";
            if (fType < ErrType_Fatal)
                fType = ErrType_Fatal;
        }
        else if (type == XMLErrorReporter::ErrTypes_Unknown)
            fMessage += "Unknown Error ";

        fMessage += "in ";
        if (systemId && *systemId)
            fMessage += TO_LOCAL(systemId);
        else
            fMessage += TO_LOCAL(publicId);

        if (lineNum || colNum)
        {
            XERCES_STD_QUALIFIER stringstream format;
            format << "\nat line " << (long)lineNum << " at col " << (long)colNum ;

            fMessage += format.str();
        }
    }

    if (errorText && *errorText)
    {
        if (!fMessage.empty())
            fMessage += "\n";

        fMessage += TO_LOCAL(errorText);
    }
}
WSDL_NAMESPACE_END

