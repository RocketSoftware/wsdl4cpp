/*
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * Written by Ming Zhu, Jan 2007
 */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include    <xercesc/util/XMLString.hpp>

#include    "xcurl/CurlInputSource.hpp"
#include    "xcurl/CurlInputSourceBuilder.hpp"

WSDL_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  CurlInputSourceBuilder: Destructor
// ---------------------------------------------------------------------------
CurlInputSourceBuilder::~CurlInputSourceBuilder()
{
}

// ---------------------------------------------------------------------------
//  CurlInputSourceBuilder: Implementation
// ---------------------------------------------------------------------------
InputSource* CurlInputSourceBuilder::createInputSource
    (const   XMLCh* const   url) const
{
	CurlInputSource* cis = new CurlInputSource(url, getMemoryManager());
	cis->setInputSourceEnv(getInputSourceEnv());
	return cis;
}

InputSource* CurlInputSourceBuilder::createInputSource
    (
        const   XMLCh* const   baseURL
        , const XMLCh* const   relativeURL) const
{
	CurlInputSource* cis = new CurlInputSource(baseURL, relativeURL, getMemoryManager());
	cis->setInputSourceEnv(getInputSourceEnv());
	return cis;
}

InputSource* CurlInputSourceBuilder::createInputSource
    (
        const   XMLCh* const   baseURL
        , const char* const   relativeURL) const
{
	CurlInputSource* cis = new CurlInputSource(baseURL, relativeURL, getMemoryManager());
	cis->setInputSourceEnv(getInputSourceEnv());
	return cis;
}

// ---------------------------------------------------------------------------
//  CurlInputSourceBuilder: Constructors
// ---------------------------------------------------------------------------
CurlInputSourceBuilder::CurlInputSourceBuilder(MemoryManager* const manager)
: InputSourceBuilder(manager)
{
}

WSDL_NAMESPACE_END

