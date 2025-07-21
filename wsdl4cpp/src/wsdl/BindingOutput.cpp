/*
 * %fv:BindingOutput.cpp-4 % 
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
#include "wsdl/BindingOutput.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

BindingOutput::BindingOutput()
//	: Param()
{
}

BindingOutput::~BindingOutput()
{
}

XMLChString BindingOutput::getTagName() 
{
    return toXmlStr("output");
}


WSDL_NAMESPACE_END

