/*
 * Written by Ming Zhu, March 2006
 * 
 * This part is an extension to WSDL4J.
 */
#ifndef SCHEMAXERCESC_HPP_
#define SCHEMAXERCESC_HPP_

#include "wsdl/wsdlbas.hpp"
#include "wsdl/wsdlxerces.hpp"
#include <xercesc/framework/XMLGrammarPool.hpp>

WSDL_NAMESPACE_BEGIN

typedef counted_owned_ptr<
    XERCES_CPP_NAMESPACE_QUALIFIER XSModel, 
    XERCES_CPP_NAMESPACE_QUALIFIER XMLGrammarPool> XSModelPtr;

typedef counted_owned_ptr<
    XERCES_CPP_NAMESPACE_QUALIFIER XSTypeDefinition, 
    XERCES_CPP_NAMESPACE_QUALIFIER XMLGrammarPool> XSTypeDefinitionPtr;

typedef counted_owned_ptr<
    XERCES_CPP_NAMESPACE_QUALIFIER XSElementDeclaration, 
    XERCES_CPP_NAMESPACE_QUALIFIER XMLGrammarPool> XSElementDeclarationPtr;

typedef counted_ptr<XERCES_CPP_NAMESPACE_QUALIFIER XMLGrammarPool> XMLGrammarPoolPtr;

WSDL_NAMESPACE_END

#endif /*SCHEMAXERCESC_HPP_*/
