/*
 * %fv:WsdlReader.hpp-7 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0.
 * 
 * History:
 * 
 * revision  date    refnum    version  who  description
 * --------------------------------------------------------------------------
 * 01-05     060509            9.SOAP   mzu  Migrated from WSDL4J
 * 06        060704  cr24024   9.SOAP   mzu  Add method createXMLSchemaTypes
 * 09        070109  t85163    9.SOAP   mzu  Better format
 * 10        070223  c25551    9.2.01   mzu  Adding InputSourceEnv for integrating 
 *                                           with libcurl
 * --------------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 * 
 */
#ifndef WSDLREADER_HPP_
#define WSDLREADER_HPP_
#include <map>
#include <string>
#include <vector>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>

#include <xercesc/parsers/XercesDOMParser.hpp>

#include "wsdl/Constants.hpp"
#include "wsdl/Definitions.hpp"
#include "wsdl/InputSourceEnv.hpp"
#include "wsdl/Part.hpp"
#include "wsdl/util/DOMUtils.hpp"
#include "wsdl/WSDLException.hpp"
#include "wsdl/schema/Schema.hpp"

WSDL_NAMESPACE_BEGIN

class WSDL_EXPORT WsdlReader
{
public:
	WsdlReader(XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* 
		fMemoryManager = XERCES_CPP_NAMESPACE_QUALIFIER XMLPlatformUtils::fgMemoryManager);
	WsdlReader(const WsdlReader& aReader);
	virtual ~WsdlReader();
	
    virtual void setFeature(XMLChString name, bool value) throw (WSDLException);
    
    static const XMLCh DEFAULT_SOAPENC_BASE_URI[];
    /**
     * Returns the base URI of the soapencoding.xsd.
     * @return the base URI of the soapencoding.xsd.
     */
    virtual XMLChString getSOAPEncBaseURI() const;

    /**
     * Set the base URI of the soapencoding.xsd.
     * @param uri the base URI of the soapencoding.xsd.
     */
    virtual void setSOAPEncBaseURI(XMLChString uri);

    virtual DefinitionsPtr readWsdl(XMLChString wsdlURI) throw (WSDLException);
    
      /**
       * Read the WSDL document accessible via the specified
       * URI into a WSDL definition.
       *
       * @param contextURI the context in which to resolve the
       * wsdlURI, if the wsdlURI is relative. Can be null, in which
       * case it will be ignored.
       * @param wsdlURI a URI (can be a filename or URL) pointing to a
       * WSDL XML definition.
       * @return the definition.
       */
    virtual DefinitionsPtr readWsdl(XMLChString contextURI, XMLChString wsdlURI) 
        throw (WSDLException);
	
    /**
     * Returns the input source environment.
     * @return the input source environment.
     */
	InputSourceEnvPtr getInputSourceEnv() const { return isePtr; }

    /**
     * Returns the input source environment.
     * @return the input source environment.
     */
	void setInputSourceEnv(const InputSourceEnvPtr ptr) { isePtr = ptr;}

protected:
    typedef std::map<XMLChString, DefinitionsPtr, lessXMLCh> StrDefMap;
    DEFINE_PTR(StrDefMap);
    
	virtual DefinitionsPtr readWsdl(XMLChString documentBaseURI, 
        XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* definitionsElement)
         throw (WSDLException) ;
	
    virtual DefinitionsPtr readWSDL(XMLChString documentBaseURI,
                                XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* definitionsElement,
                                StrDefMapPtr importedDefs)
                                  throw (WSDLException);
                                  
    virtual DefinitionsPtr parseDefinitions(
		XMLChString documentBaseURI, 
		XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* definitionsElement,
		StrDefMapPtr importedDefs) throw (WSDLException);
	
    virtual TypesPtr parseTypes(XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* typesEl, DefinitionsPtr def)
            throw (WSDLException);
    
    virtual ExtensibilityElementPtr parseSchema( 
        QNamePtr parentType,
        XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el,
        DefinitionsPtr def)
        throw (WSDLException);
    
    virtual ExtensibilityElementPtr parseSchema(
        QNamePtr parentType,
        XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el,
        DefinitionsPtr def,
        ExtensionRegistryPtr extReg)
        throw (WSDLException);

    virtual BindingPtr parseBinding(
		XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* bindingEl, DefinitionsPtr def) throw(WSDLException);
		
    virtual BindingOperationPtr parseBindingOperation(
        XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* bindingOperationEl,
        PortTypePtr portType,
        DefinitionsPtr def)
          throw (WSDLException);
    virtual BindingFaultPtr parseBindingFault(
        XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* bindingInputEl, DefinitionsPtr def) throw (WSDLException);
    virtual ImportPtr parseImport(XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* importEl,
                               DefinitionsPtr def,
                               StrDefMapPtr importedDefs)
                                 throw (WSDLException);
    virtual BindingInputPtr parseBindingInput(
        XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* bindingInputEl, DefinitionsPtr def) throw (WSDLException);
    virtual BindingOutputPtr parseBindingOutput(
        XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* bindingInputEl, DefinitionsPtr def) throw (WSDLException);

	virtual MessagePtr parseMessage(
		XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* msgEl, DefinitionsPtr def) throw(WSDLException);
		
	virtual PortTypePtr parsePortType(
		XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* portTypeEl, DefinitionsPtr def) throw(WSDLException);
		
	virtual ServicePtr parseService(
		XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* serviceEl, DefinitionsPtr def) throw(WSDLException);
		
	virtual PartPtr parsePart(
		XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* partEl, DefinitionsPtr def) throw(WSDLException);
			
	virtual OperationPtr parseOperation(XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* opEl,
                         PortTypePtr portType,
                         DefinitionsPtr def) throw(WSDLException);
                         
    virtual InputPtr parseInput(XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* inputEl, DefinitionsPtr def)
                    throw (WSDLException);
    virtual OutputPtr parseOutput(XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* outputEl, DefinitionsPtr def)
                    throw (WSDLException);
    virtual FaultPtr parseFault(XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* faultEl, DefinitionsPtr def)
                    throw (WSDLException);

    virtual PortPtr parsePort(XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* portEl, DefinitionsPtr def)
                    throw (WSDLException);
    
    virtual ExtensibilityElementPtr parseExtensibilityElement(
            QNamePtr parentType,
            XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el,
            DefinitionsPtr def)
      throw (WSDLException);
      
	/**
	 * @since rev07
	 */
	virtual void parseExtensibilityAttributes(
			  XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el,
              QNamePtr parentType,
              AttributeExtensiblePtr attrExt,
              DefinitionsPtr def)
         throw (WSDLException);
         
	/**
	 * @since rev07
	 */
    virtual ExtensibilityAttributePtr parseExtensibilityAttribute(
		  XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el,
		  int attrType,
		  XMLChString strValue,
		  DefinitionsPtr def)
         throw (WSDLException);
		  
protected:

    bool verbose;
    bool importDocuments;
    XMLChString soapEncBaseURI;
	InputSourceEnvPtr isePtr;
	bool usingCURL;
    
	XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* fMemoryManager;
	XERCES_CPP_NAMESPACE_QUALIFIER DOMImplementation* impl;

	XERCES_CPP_NAMESPACE_QUALIFIER XercesDOMParser *parser;
    
    /**
     * Contains all schemas used by this wsdl, either in-line or nested 
     * via wsdl imports or schema imports, includes or redefines
     */
    Schema::MapPtr allSchemas;

	virtual XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument* getDocument(XMLChString docURI) 
        throw(WSDLException);
	
	virtual void checkElementName(
        XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node, 
        const XMLCh* localName, 
		const XMLCh* namespaceURI = Constants::NS_URI_WSDL);
        
	virtual bool match(
        XERCES_CPP_NAMESPACE_QUALIFIER DOMNode* node, 
        const XMLCh* localName, 
		const XMLCh* namespaceURI = Constants::NS_URI_WSDL);
        
    /**
     * Create Types for the XML Schema types.
     * @param DOMElement the dom element;
     * @param def the definitions.
     * @return the Types.
     * @since rev06
     */
    virtual TypesPtr createXMLSchemaTypes(
        XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* defEl, DefinitionsPtr def)
        throw (WSDLException);
        
    /**
     * Initialize the parser; called by constructors.
     */
    virtual void initParser();

	virtual void scanSchemas(TypesPtr types);

	static QNamePtr getQualifiedAttributeValue(
		XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el,
	    const XMLCh* attrName,
	    const XMLCh* elDesc,
	    DefinitionsPtr def,
	    DOMUtils::AttrPtrListPtr remainingAttrs)
    throw(WSDLException);
    
	static QNamePtr getQualifiedAttributeValue(XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el,
                                  const XMLCh* attrName,
                                  const XMLCh* elDesc,
                                  DefinitionsPtr def)
                                    throw(WSDLException);
};

DEFINE_PTR(WsdlReader);

WSDL_NAMESPACE_END

#endif /*WSDLREADER_HPP_*/
