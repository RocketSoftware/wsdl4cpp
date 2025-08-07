/*
 * %fv:SchemaDeserializer.cpp-10 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * History:
 * 
 * revision  date    refnum    version  who  description
 * --------------------------------------------------------------------------
 * 01        060713            9.SOAP   mzu  Migrated from WSDL4J
 * 02        060713  c24141    9.SOAP   ahn  Change customized import
 * 03        060713  t85128    9.SOAP   mzu  Change for xml schema cross-reference
 * --------------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 * 
 */
/*******************************************************************************
date   refnum    version who description
070202 c25507    9.SOAP  ahn direct import of soapencoding.xsd
150724 b30601    X702    ahn ns prefix scoping
date   refnum    version who description
*******************************************************************************/
#include "wsdl/wsdlxerces.hpp"

#include <iostream>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/framework/XMLGrammarPoolImpl.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/Constants.hpp"
#include "wsdl/util/DOMUtils.hpp"
#include "wsdl/util/SOAPEncodingUtils.hpp"
#include "wsdl/util/XercesUtils.hpp"
#include "wsdl/ext/UnknownExtensibilityElement.hpp"
#include "wsdl/schema/Schema.hpp"
#include "wsdl/schema/SchemaDeserializer.hpp"

USING_STD

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

SchemaDeserializer::SchemaDeserializer()
{
}

SchemaDeserializer::~SchemaDeserializer()
{
}

ExtensibilityElementPtr SchemaDeserializer::unmarshall(
        QNamePtr parentType, QNamePtr elementType, 
        DOMElement* el, 
        DefinitionsPtr def, 
        ExtensionRegistryPtr extReg)
    throw (WSDLException)
{
    //SOAPAddressPtr eePtr(extReg->createExtension(parentType, elementType));
    ExtensibilityElementPtr eePtr0(extReg->createExtension(parentType, elementType));
    
    SchemaPtr eePtr = eePtr0.downcastTo<Schema>();
    eePtr->setDocumentBaseURI(def->getDocumentBaseURI());
    eePtr->setElement(el);
                                            
    try 
    {
        normalizeSchemaInWsdl(eePtr->getElement(), def);
    }
    catch (const WSDLException& e)
    {
        throw e;
    }
    catch (...)
    {
    	XMLChString uri = eePtr->getDocumentBaseURI();
        throw WSDLException(WSDLException::PARSER_ERROR,
            string("\nUnexpected exception during parsing: '")
            + uri.toLocal() + "'\n");
        //errorCode = 5;        
    }
    
    return eePtr;
}

void SchemaDeserializer::normalizeSchemaInWsdl(
        DOMElement* schemaElement, DefinitionsPtr def) 
{
    DOMDocument* doc = schemaElement->getOwnerDocument();
    DOMElement* docEl = doc->getDocumentElement();
    
    // Add namespaces from top node
    DOMNamedNodeMap* aMap = docEl->getAttributes();
    DOMNamedNodeMap* saMap = schemaElement->getAttributes();
    for (int i=0, l=aMap->getLength(); i<l; i++) {
        DOMNode* node = aMap->item(i);
		if ( XMLString::compareString(DOMUtils::ATTR_XMLNS, node->getPrefix()) == 0 ){
            if (!saMap->getNamedItemNS(node->getNamespaceURI(), node->getLocalName())) // @b30601
                saMap->setNamedItemNS(node->cloneNode(false));
        }
    }
    
    // @c25507 Add import element of soapencoding.xsd
    SOAPEncodingUtils::addImport(schemaElement, def);
    
}

WSDL_NAMESPACE_END

