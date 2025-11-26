/*
 * %fv: WsdlFramework.cpp-2 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
 */
/*******************************************************************************
date   refnum    version who description
120101 c29155    E103    ahn Determine operation type, oneway, requestresponse, etc correctly on RSD
date   refnum    version who description
*******************************************************************************/

#include "wsdl/wsdlxerces.hpp"

#include <iostream>
#include <string.h>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>

#include "wsdl/WsdlFramework.hpp"
#include "wsdl/Constants.hpp"
#include "wsdl/schema/SchemaConstants.hpp"
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/OperationType.hpp"               // @c29155

USING_WSDL_NAMESPACE

XERCES_CPP_NAMESPACE_USE

// TODO: rename to WsdlFramework
WsdlFramework::WsdlFramework(const char* const locale, bool recognizeNEL)
    throw(XMLException)
{
#ifdef _DEBUG
	std::cout << "XMLPlatformUtils::Initialize()" << std::endl;
#endif
    if (locale && strlen(locale) )
    {
        XMLPlatformUtils::Initialize(locale);
    }
    else
    {
        XMLPlatformUtils::Initialize();
    }

    if (recognizeNEL)
    {
        XMLPlatformUtils::recognizeNEL(recognizeNEL);
    }
    
    XMLChString::init();
    Constants::init();
	SchemaConstants::init();
	SOAPConstants::init();
    OperationType::init();                      // @c29155
}

WsdlFramework::~WsdlFramework()
{
    OperationType::release();                   // @c29155
	SOAPConstants::release();
	SchemaConstants::release();
    Constants::release();
    XMLChString::release();
    
#ifdef _DEBUG
	std::cout << "XMLPlatformUtils::Terminate()"  << std::endl;
#endif
    // And call the termination method
    XMLPlatformUtils::Terminate();
}
