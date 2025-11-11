/*
 * %fv:SchemaDeserializer.hpp-2 % 
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
 */
#ifndef SCHEMADESERIALIZER_HPP_
#define SCHEMADESERIALIZER_HPP_
#include <xercesc/dom/DOMElement.hpp>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/ext/ExtensibilityElement.hpp"
#include "wsdl/ext/ExtensionRegistry.hpp"
#include "wsdl/Definitions.hpp"
#include "wsdl/QName.hpp"

WSDL_NAMESPACE_BEGIN

class SchemaDeserializer;

DEFINE_PTR(SchemaDeserializer);

class WSDL_EXPORT SchemaDeserializer : public ExtensionDeserializer
{
public:
	SchemaDeserializer();
	virtual ~SchemaDeserializer();
    
    virtual ExtensibilityElementPtr unmarshall(
        QNamePtr parentType, QNamePtr elementType, 
        XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el, 
        DefinitionsPtr def, 
        ExtensionRegistryPtr extReg) throw (WSDLException);
	
protected:
    static void normalizeSchemaInWsdl(
        XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el
        , DefinitionsPtr def);

};

WSDL_NAMESPACE_END

#endif /*SCHEMADESERIALIZER_HPP_*/
