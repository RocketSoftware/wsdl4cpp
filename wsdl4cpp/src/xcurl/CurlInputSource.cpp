/*
 * $Id: CurlInputSource.cpp $
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * Written by Ming Zhu, Jan 2007
 * 
 */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#ifndef WIN32
#include <unistd.h>
#endif

//#include <xercesc/util/BinFileInputStream.hpp>
#include <xercesc/util/Janitor.hpp>
#include <xercesc/util/XMLURL.hpp>
#include <xercesc/util/XMLString.hpp>
#include "xcurl/CurlInputSource.hpp"
#include "xcurl/CurlInputStream.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  CurlInputSource: Constructors and Destructor
// ---------------------------------------------------------------------------
CurlInputSource::CurlInputSource( const XMLURL&         urlId
                              , MemoryManager* const  manager) :

    InputSource(manager)
    , fURL(urlId)
{
    setSystemId(fURL.getURLText());
}

CurlInputSource::CurlInputSource( const XMLCh* const    baseId
                              , const XMLCh* const    systemId
                              , MemoryManager* const  manager) :
    InputSource(manager)
    , fURL(baseId, systemId)
{
    // Create a URL that will build up the full URL and store as the system id
    setSystemId(fURL.getURLText());
}

CurlInputSource::CurlInputSource( const XMLCh* const    baseId
                              , const XMLCh* const    systemId
                              , const XMLCh* const    publicId
                              , MemoryManager* const  manager) :
    InputSource(0, publicId, manager)
    , fURL(baseId, systemId)
{
    setSystemId(fURL.getURLText());
}

CurlInputSource::CurlInputSource( const XMLCh* const    baseId
                              , const char* const     systemId
                              , MemoryManager* const  manager) :
    InputSource(manager)
    , fURL(baseId, systemId)
{
    setSystemId(fURL.getURLText());
}

CurlInputSource::CurlInputSource( const   XMLCh* const   baseId
                                , const char* const    systemId
                                , const char* const    publicId
                                , MemoryManager* const  manager) :
    InputSource(0, publicId, manager)
    , fURL(baseId, systemId)
{
    setSystemId(fURL.getURLText());
}

CurlInputSource::~CurlInputSource()
{
}


// ---------------------------------------------------------------------------
//  CurlInputSource: Implementation of the input source interface
// ---------------------------------------------------------------------------
BinInputStream* CurlInputSource::makeStream() const
{
    // Ask the URL to create us an appropriate input stream
	// Just create a CurlURLInputStream
	// We defer any checking of the url type for curl in CurlURLInputStream
	CurlInputStream* retStrm =
		new (fURL.getMemoryManager()) CurlInputStream(fURL, 0, getInputSourceEnv());
	return retStrm;            
}

WSDL_NAMESPACE_END

