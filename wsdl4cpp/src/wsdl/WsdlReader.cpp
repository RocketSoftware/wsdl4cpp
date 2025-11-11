/*
 * %fv:WsdlReader.cpp-16 % 
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
 * History:
 * 
 * revision  date    refnum    version  who  description
 * --------------------------------------------------------------------------
 * 01-05     060509            9.SOAP   mzu  Migrated from WSDL4J
 * 06        060704  cr24024   9.SOAP   mzu  Add method createXMLSchemaTypes
 * 07        060713  cr24024   9.SOAP   mzu  Additional fix for cr24024
 * 08        060713  t85128    9.SOAP   mzu  Change for xml schema cross-reference
 * 09        070109  t85163    9.SOAP   mzu  Add constants for attribute extentions
 * 10        070213  cr25551   9.SOAP   mzu  Integrate libcurl
 * --------------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 * 
 */
/*******************************************************************************
date   refnum    version who description
070213 c25514    920101  ahn one way services
070215 c25552    920101  ahn import, set default soapencoding.xsd location
120907 b29663    E110    ahn better error reporting
date   refnum    version who description
*******************************************************************************/

#include "wsdl/wsdlxerces.hpp"

#include <iostream>
#include <string>
#include <vector>

#include <xercesc/util/XMLString.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/framework/XMLGrammarPoolImpl.hpp>
#include <xercesc/sax/InputSource.hpp>
#include <xercesc/framework/psvi/XSModel.hpp>
#include <xercesc/validators/schema/SchemaGrammar.hpp>

#include <xercesc/framework/URLInputSource.hpp>
#include <xercesc/util/XMLURL.hpp>

#include "wsdl/WsdlReader.hpp"
#include "wsdl/Constants.hpp"
#include "wsdl/ext/AttributeExtensible.hpp"
#include "wsdl/ext/ExtensionDeserializer.hpp"
#include "wsdl/ext/ExtensionRegistry.hpp"
#include "wsdl/OperationType.hpp"
#include "wsdl/QName.hpp"
#include "wsdl/WSDLException.hpp"
#include "wsdl/util/DOMUtils.hpp"
#include "wsdl/util/StringUtils.hpp"
#include "wsdl/util/XercesUtils.hpp"
#include "wsdl/schema/SchemaConstants.hpp"

#include "wsdl/WsdlErrorHandler.hpp"

USING_STD

USING_WSDL_NAMESPACE

XERCES_CPP_NAMESPACE_USE

const XMLCh WsdlReader::DEFAULT_SOAPENC_BASE_URI[] = // "."
{
    chPeriod
    //, chForwardSlash
    , chNull
};

WsdlReader::WsdlReader(const WsdlReader& aReader)
    : verbose(aReader.verbose)
    , importDocuments(aReader.importDocuments)
    , soapEncBaseURI(aReader.soapEncBaseURI)
    , isePtr(aReader.isePtr)
	, usingCURL(aReader.usingCURL)  //@rev10
	, fMemoryManager(aReader.fMemoryManager)
    , errPtr(aReader.errPtr)
{
	initParser();
}

WsdlReader::WsdlReader(MemoryManager* fMM) 
    : verbose(true)
    , importDocuments(true)
    , soapEncBaseURI(DEFAULT_SOAPENC_BASE_URI)
#ifdef WSDL_USE_CURL
	, usingCURL(true)  //@rev10
#else
	, usingCURL(false)  //@rev10
#endif
	, fMemoryManager(fMM)
{
	initParser();
    errPtr = (WsdlErrorHandlerPtr) new WsdlErrorHandler();
}

void WsdlReader::initParser() 
{
    AbstractDOMParser::ValSchemes valScheme = AbstractDOMParser::Val_Auto;
    bool                 doNamespaces       = true;
    bool                 doSchema           = false;
    bool                 schemaFullChecking = false;

    // Instantiate the DOM parser.
    // parser = new (fMemoryManager)XercesDOMParser(0, fMemoryManager, 0);
    parser = new (fMemoryManager)WsdlDOMParser(0, fMemoryManager, 0);
    parser->setValidationScheme(valScheme);

    parser->setDoNamespaces(doNamespaces);
    parser->setDoSchema(doSchema);
    parser->setValidationSchemaFullChecking(schemaFullChecking);

}

WsdlReader::~WsdlReader()
{
	delete parser;
    errPtr.release();
}

XMLChString WsdlReader::getSOAPEncBaseURI() const
{
    return soapEncBaseURI;
}

void WsdlReader::setSOAPEncBaseURI(XMLChString uri)
{
    soapEncBaseURI = uri;
}

void WsdlReader::setFeature(XMLChString name, bool value)
    throw (WSDLException)
{
    if (name == null)
    {
      throw WSDLException(WSDLException::OTHER_ERROR, string("Feature name must not be null."));
    }

    if (name == (XMLChString)Constants::FEATURE_VERBOSE)
    {
      verbose = value;
    }
    else if (name == (XMLChString)Constants::FEATURE_IMPORT_DOCUMENTS)
    {
      importDocuments = value;
    }
    else
    {
        throw WSDLException(WSDLException::OTHER_ERROR, 
            string("Feature name '").append(name.toLocal()).append("' not recognized."));
    }
}

DOMDocument* WsdlReader::getDocument(XMLChString docURI) 
	throw(WSDLException)
{
    std::string lErrorMsg;    
    parser->setErrorHandler((ErrorHandler* const)errPtr.get());

    const XMLCh* xmlFile = docURI.c_str();
    
    bool errorOccurred = false;
    bool URIIncluded = false;

    DOMDocument* doc;

    try
    {
        // reset document pool
        parser->resetDocumentPool();

		if ( usingCURL )  //@rev10
		{
			InputSource* srcToUse = XercesUtils::createInputSource(xmlFile,
        		fMemoryManager, getInputSourceEnv(), false
        		);
	        
			Janitor<InputSource> janSrc(srcToUse);

			parser->parse(*srcToUse);
			doc = parser->getDocument();
		}
		else
		{
			parser->parse(xmlFile);
			doc = parser->getDocument();
		}
        
    }

    catch (const XMLException& toCatch)
    {
	lErrorMsg = toLocal(toCatch.getMessage());
        if ( verbose )
        {
            cerr << "\nError during parsing: '" << xmlFile << "'\n"
                 << "Exception message is:  \n"
                 << toLocal(toCatch.getMessage()) << "\n" << endl;
        }
        errorOccurred = true;
    }
    catch (const DOMException& toCatch)
    {
        const unsigned int maxChars = 2047;
        XMLCh errText[maxChars + 1];
    
        if (DOMImplementation::loadDOMExceptionMsg(toCatch.code, errText, maxChars))
        {
    	    lErrorMsg = toLocal(errText);
        }
	
        if ( verbose )
        {
            const unsigned int maxChars = 2047;
            XMLCh errText[maxChars + 1];
    
            cerr << "\nDOM Error during parsing: '" << xmlFile << "'\n"
                 << "DOMException code is:  " << toCatch.code << endl;
    
            if (DOMImplementation::loadDOMExceptionMsg(toCatch.code, errText, maxChars))
                 cerr << "Message is: " << toLocal(errText) << endl;

        }
        errorOccurred = true;
    }
    catch (...)
    {
	    lErrorMsg = "Unexpected error during parsing.";

        // @b29663 because it is an exception we treat it as a real error
        if (errPtr->getSawErrors())
            lErrorMsg += errPtr->getMessage();

        if ( verbose )
        {
            cerr << "\nUnexpected exception during parsing: '" << xmlFile << "'" << endl;
        }
        errorOccurred = true;
    }

    // @b29663 detect real errors and throw an exception
    // otherwise allow the caller to decide what to do with warnings
    if (errPtr->getSawErrors())
    {
        lErrorMsg = errPtr->getMessage();
        XMLExcepts::Codes errCode = errPtr->getErrorCode();

        // @28519
        if ((errCode >= XMLExcepts::NetAcc_InternalError && errCode <= XMLExcepts::NetAcc_UnsupportedMethod) || errCode == XMLExcepts::File_CouldNotOpenFile)
        {
            throw WSDLException(WSDLException::ACCESS_ERROR,
                              lErrorMsg);
        }

        if ( lErrorMsg.length() == 0 ) 
        {
            lErrorMsg = "Errors occurred, no output available.";
            errorOccurred = true;
        }

        // @b29663
        if (errPtr->getErrorType() == WsdlErrorHandler::ErrType_Fatal)
        {
            URIIncluded = true;                     // the message will include the WSDL URI already
            errorOccurred = true;
        }
    }
    
    if (errorOccurred)
    {
        std::string lmsg = "Problem parsing ";

        if (!URIIncluded)
            lmsg += "'" + docURI.toLocal() + "': ";
        else
            lmsg += ": ";

        throw WSDLException(WSDLException::PARSER_ERROR,
                              lmsg + lErrorMsg);
    }

    return doc;
}

DefinitionsPtr WsdlReader::readWsdl(XMLChString wsdlURL)
	throw (WSDLException)
{
	DOMDocument* pDocument = getDocument(wsdlURL);
	if ( pDocument )
	{
		DOMElement* pDocElement = pDocument->getDocumentElement();
		
		return readWsdl(wsdlURL, pDocElement);
	}
	
	throw WSDLException(WSDLException::INVALID_WSDL, 
		string("Can not open wsdl \"") + wsdlURL.toLocal() + "\"");
}

DefinitionsPtr WsdlReader::readWsdl(XMLChString contextURI, XMLChString wsdlURI)
    throw (WSDLException)
{
    contextURI = (contextURI != null)
                       ? StringUtils::getURI(null, contextURI)
                       : null;
    wsdlURI = StringUtils::getURI(contextURI, wsdlURI);

    return readWsdl(wsdlURI);
}

DefinitionsPtr WsdlReader::readWSDL(XMLChString documentBaseURI,
                                DOMElement* definitionsElement,
                                StrDefMapPtr importedDefs)
                                  throw (WSDLException)
{
    return parseDefinitions(documentBaseURI, definitionsElement, importedDefs);
}

DefinitionsPtr WsdlReader::readWsdl(XMLChString documentBaseURI, DOMElement* defEl)
    throw (WSDLException)
{
	return parseDefinitions(documentBaseURI, defEl, (StrDefMapPtr)0);
}

DefinitionsPtr WsdlReader::parseDefinitions(
	XMLChString documentBaseURI, 
	DOMElement* defEl,
	StrDefMapPtr importedDefs)
    throw (WSDLException)
{
    checkElementName(defEl, Constants::ELEM_DEFINITIONS, Constants::NS_URI_WSDL);
    
    DefinitionsPtr def(new Definitions());
    def->setSOAPEncBaseURI(getSOAPEncBaseURI());
    
    def->setExtensionRegistry((ExtensionRegistryPtr)new ExtensionRegistry());
    
    def->setDocumentBaseURI(documentBaseURI);

    XMLChString targetNamespace = DOMUtils::getAttribute(defEl,
                                         Constants::ATTR_TARGET_NAMESPACE);

    if ( targetNamespace != null )
    {
        def->setTargetNamespace(targetNamespace);
    }
    
    XMLChString name = DOMUtils::getAttribute(defEl, Constants::ATTR_NAME);
    if ( name != null )
    {
        def->setQName(QNamePtr(new WSDL_NAMESPACE::QName(targetNamespace, name)));
    }

    DOMNamedNodeMap* attrs = defEl->getAttributes();
    XMLSize_t size = attrs->getLength();

    for (XMLSize_t i = 0; i < size; i++)
    {
		DOMAttr* attr = (DOMAttr*)attrs->item(i);
		const XMLCh* namespaceURI = attr->getNamespaceURI();
		const XMLCh* localPart = attr->getLocalName();
    	const XMLCh* value = attr->getValue();

        if (namespaceURI && XMLString::equals(namespaceURI, XMLUni::fgXMLNSURIName) )
        {
	        if (localPart && !XMLString::equals(localPart, XMLUni::fgXMLNSString))
	        {
	          	def->addNamespace(localPart, value);
	        }
	        else
	        {
  	            def->addNamespace(Constants::DEFAULT_NS_PREFIX, value);
	        }
        }
    }
    
    DOMElement* tempEl = DOMUtils::getFirstChildElement(defEl);
    
    while (tempEl)
    {
        if ( match(tempEl, Constants::ELEM_IMPORT) )
        {
            if (!importedDefs)
            {
                importedDefs = (StrDefMapPtr)new StrDefMap();
            }
    
            if (documentBaseURI != null)
            {
                importedDefs->insert(StrDefMap::value_type(documentBaseURI, def));
            }

            def->addImport(parseImport(tempEl, def, importedDefs));
        }
        else if (match(tempEl, Constants::ELEM_DOCUMENTATION))
        {
//        def->setDocumentationElement(tempEl);
        }
        else if (match(tempEl, Constants::ELEM_TYPES))
        {
            def->setTypes(parseTypes(tempEl, def));
        }
        else if (match(tempEl, Constants::ELEM_MESSAGE))
        {
            def->addMessage(parseMessage(tempEl, def));
        }
        else if (match(tempEl, Constants::ELEM_PORT_TYPE))
        {
            def->addPortType(parsePortType(tempEl, def));
        }
        else if (match(tempEl, Constants::ELEM_BINDING))
        {
        	def->addBinding(parseBinding(tempEl, def));
        }
        else if (match(tempEl, Constants::ELEM_SERVICE))
        {
            def->addService(parseService(tempEl, def));
        }
//      else
        {
//        def->addExtensibilityElement(
//          parseExtensibilityElement(Definition.class, tempEl, def));
        }
        
        tempEl = DOMUtils::getNextSiblingElement(tempEl);

    }
    
    // rev06: if xml schema types are not ready, create a new types
    //        by calling createXMLSchemaTypes().
    if ( !(def->isBasicTypesReady()) ) {
        if ( def->isTypeDefinitionIncluded() ) //rev07
        {
            throw WSDLException(WSDLException::OTHER_ERROR, "Types parsing error!");
        }
        else
        {
            def->setTypes(createXMLSchemaTypes(defEl, def));
        }
    }
    
    // @b29663
    if (errPtr->getSawErrors() && errPtr->getErrorType() == WsdlErrorHandler::ErrType_Fatal)
    {
        std::string lmsg = "Problem parsing : ";

        lmsg += errPtr->getMessage();
        throw WSDLException(WSDLException::PARSER_ERROR, lmsg);
    }

    return def;
}

ImportPtr WsdlReader::parseImport(DOMElement* importEl,
                               DefinitionsPtr def,
                               StrDefMapPtr importedDefs)
                                 throw (WSDLException)
{
    ImportPtr theImport = def->createImport();

    try
    { //1
        XMLChString namespaceURI = DOMUtils::getAttribute(importEl,
                                                  Constants::ATTR_NAMESPACE);
        XMLChString locationURI = DOMUtils::getAttribute(importEl,
                                                 Constants::ATTR_LOCATION);
        XMLChString contextURI = null;

        if (namespaceURI != null)
        {
            theImport->setNamespaceURI(namespaceURI);
        }

        if (locationURI != null)
        {//2
            theImport->setLocationURI(locationURI);

            if (importDocuments)
            {//3
                try
                { //4
                    contextURI = def->getDocumentBaseURI();
                    DefinitionsPtr importedDef;

                    XMLChString theURI;
                    
                    contextURI = (contextURI != null)
                                           ? StringUtils::getURI(null, contextURI)
                                           : null;
                                           
                    theURI = StringUtils::getURI(contextURI, locationURI);

                    StrDefMap::iterator it = importedDefs->find(theURI);
        
                    if (it == importedDefs->end())
                    { //5
                      WsdlReaderPtr reader(new WsdlReader(*this));   // @RevXX 
                      //WsdlReaderPtr reader(new WsdlReader());
            
                      DOMDocument* doc = reader->getDocument(theURI);
            
//                      if (inputStream != null)
//                      {
//                        inputStream.close();
//                      }
//            
                      DOMElement* documentElement = doc->getDocumentElement();
            
                      /*
                        Check if it's a wsdl document.
                        If it's not, don't retrieve and process it.
                        This should later be extended to allow other types of
                        documents to be retrieved and processed, such as schema
                        documents (".xsd"), etc...
                      */
                      if (DOMUtils::matches(Constants::Q_ELEM_DEFINITIONS,
                                             documentElement))
                      {//6.1
                            if (verbose)
                            {
                               cout << endl << "Retrieving document at '" << locationURI.toLocal() 
                                               <<  "'";
                               if (contextURI == null) cout << ".";
                               else cout << ", relative to '" << contextURI.toLocal() << "'.";
                            }
                
                
                            importedDef = reader->readWSDL(theURI,
                                                   documentElement,
                                                   importedDefs);
                      }//6.1
                      else
                      {//6.2
                        QNamePtr docElementQName = DOMUtils::newQName(documentElement);
            
                        if ((SchemaConstants::XSD_QNAME_LIST)->find(docElementQName) 
                                != (SchemaConstants::XSD_QNAME_LIST)->end() )
                        { // 7
//                          if (verbose)
//                          {
//                            System.out.println("Retrieving schema wsdl:imported from '" + locationURI +
//                                               "'" +
//                                               (contextURI == null
//                                                ? "."
//                                                : ", relative to '" + contextURI + "'."));
//                          }
//                            
//                          WSDLFactory factory = getWSDLFactory();
//            
//                          importedDef = factory.newDefinition();
//            
//                          if (extReg != null)
//                          {
//                            importedDef->setExtensionRegistry(extReg);
//                          }
//            
//                          XMLChString urlString =
//                            (loc != null)
//                            ? loc.getLatestImportURI()
//                            : (url != null)
//                              ? url.toString()
//                              : locationURI;
//            
//                          importedDef->setDocumentBaseURI(urlString);
//            
//                          //TODO:
////                          TypesPtr types = importedDef->createTypes();
////                          types->addExtensibilityElement(
////                              parseSchema(TypesPtr.class, documentElement, importedDef));
////                          importedDef->setTypes(types);
                        }//7
                    }//6.2
                }//5
    
                if (importedDef)
                {
                     theImport->setDefinition(importedDef);
                }
            } //4
            catch (const WSDLException& e)
            {//4.1
                throw e;
            }//4.1
            catch (...)
            {//4.2
              string msg("Unable to resolve imported document at '");
              msg.append(locationURI.toLocal())
                  .append("'");
              if ( contextURI == null )
              {
                msg.append("'.");
              }
              else
              {
                msg.append("', relative to '")
                  .append(contextURI.toLocal())
                  .append("'");
              }
              throw WSDLException(WSDLException::OTHER_ERROR, msg);
            }//4.2
        } //3
      } //2
  
    }//1
    catch (const WSDLException& e)
    {
        //TODO:
//      if (e.getLocation() == null)
//      {
//        e.setLocation(XPathUtils.getXPathExprFromNode(importEl));
//      }
//      else
//      {
//        //If definitions are being parsed recursively for nested imports
//        //the exception location must be built up recursively too so
//        //prepend this element's xpath to exception location.
//            XMLChString loc = XPathUtils.getXPathExprFromNode(importEl) + e.getLocation();
//            e.setLocation(loc);
//      }

      throw e; 
    }

    DOMElement* tempEl = DOMUtils::getFirstChildElement(importEl);

    while (tempEl)
    {
      if (DOMUtils::matches(Constants::Q_ELEM_DOCUMENTATION, tempEl))
      {
        theImport->setDocumentationElement(tempEl);
      }
      else
      {
        DOMUtils::throwWSDLException(tempEl);
      }

      tempEl = DOMUtils::getNextSiblingElement(tempEl);
     }

    parseExtensibilityAttributes(importEl, Constants::Q_ELEM_IMPORT, theImport, def); //@rev09
    
    return theImport; 
    
}

// Introduced since rev06
TypesPtr WsdlReader::createXMLSchemaTypes(DOMElement* defEl, DefinitionsPtr def)
    throw (WSDLException)
{
    DOMDocument* doc = defEl->getOwnerDocument();
    
    DOMElement* typesElement = doc->createElementNS(defEl->getNamespaceURI(), Constants::ELEM_TYPES);
    DOMElement* schemaElement = doc->createElementNS(SchemaConstants::NS_URI_XSD_2001, SchemaConstants::ELEM_SCHEMA);
    typesElement->appendChild(schemaElement);
    return parseTypes(typesElement, def);
}

TypesPtr WsdlReader::parseTypes(DOMElement* typesEl, DefinitionsPtr def)
    throw (WSDLException)
  {
  
    DOMUtils::AttrPtrListPtr  remainingAttrs = DOMUtils::getAttributes(typesEl);
    
    //This element cannot contain extension attributes, so check for
    //unexpected remaining attributes.
    if (!remainingAttrs->empty()) {
        DOMUtils::throwWSDLException(typesEl, remainingAttrs);;
    }
      
    TypesPtr types = def->createTypes();
        
  try 
  {
    DOMElement* tempEl = DOMUtils::getFirstChildElement(typesEl);
    QNamePtr tempElType;

    while (tempEl)
    {
      tempElType = DOMUtils::newQName(tempEl);
      
      if (DOMUtils::matches(Constants::Q_ELEM_DOCUMENTATION, tempEl))
      {
        types->setDocumentationElement(tempEl);
      }
      else if ((SchemaConstants::XSD_QNAME_LIST)->find(tempElType) 
            != (SchemaConstants::XSD_QNAME_LIST)->end() )
      {
		  types->addSchema(
		      parseSchema(Constants::Q_ELEM_TYPES, tempEl, def));
      }
      else
      {
        types->addExtensibilityElement(
          parseExtensibilityElement(Constants::Q_ELEM_TYPES, tempEl, def));
      }

      tempEl = DOMUtils::getNextSiblingElement(tempEl);
    }

	scanSchemas(types);  //@rev10
    }
    catch  (XMLErrs::Codes eCode)
    {
	std::stringstream l_str;
	l_str << errPtr->getMessage() << "\nXML Parser Exception" << (int)eCode;
	throw WSDLException(WSDLException::PARSER_ERROR , l_str.str().c_str());
    }
    return types;
}
  
void WsdlReader::scanSchemas(TypesPtr types)
{
    // @rev08 begin: Parse and Scan schema list
	// @rev10 add fmm field
	XMLGrammarPoolPtr grammarPoolPtr = (XMLGrammarPoolPtr)new (fMemoryManager) XMLGrammarPoolImpl(fMemoryManager);

    GrammarResolver grammarResolver(grammarPoolPtr.get(), fMemoryManager);

    //  Create a scanner and tell it what validator to use. Then set us
    //  as the document event handler so we can fill the DOM document.
    WsdlXMLScanner scanner(0, &grammarResolver, fMemoryManager);
	scanner.setInputSourceEnv(getInputSourceEnv()); //@rev10
	scanner.setUsingCURL(usingCURL); //@rev10
    scanner.setURIStringPool(grammarResolver.getStringPool());
	scanner.setGenerateSyntheticAnnotations(true);

    // @b29663 our WsdlErrorHandler also implements the XMLErrorReporter methods
    scanner.setErrorReporter((XMLErrorReporter* const)errPtr.get());
    
    scanner.scanExtElementList(types->getExtensibilityElements());
    
    types->setGrammarPool(grammarPoolPtr);
    //@rev08 end
}

ExtensibilityElementPtr WsdlReader::parseSchema( 
    QNamePtr parentType,
    DOMElement* el,
    DefinitionsPtr def)
    throw (WSDLException)
{
    QNamePtr elementType;
    ExtensionRegistryPtr extReg;

    try
    {
      extReg = def->getExtensionRegistry();

      if (!extReg)
      {
        throw WSDLException(WSDLException::CONFIGURATION_ERROR,
                                string("No ExtensionRegistry set for this ") +
                                "Definition, so unable to deserialize " +
                                "a schema element in the " +
                                "context of a '" + parentType->toString().toLocal() +
                                "'.");
      }

      return parseSchema(parentType, el, def, extReg);
    }
    catch (const WSDLException& e)
    {
//      if (e.getLocation() == null)
//      {
//        e.setLocation(XPathUtils.getXPathExprFromNode(el));
//      }
       
      throw e;
    }
}
          

ExtensibilityElementPtr WsdlReader::parseSchema(
    QNamePtr parentType,
    DOMElement* el,
    DefinitionsPtr def,
    ExtensionRegistryPtr extReg)
    throw (WSDLException)
{
    /*
     * This method returns ExtensibilityElement rather than Schema because we
     * do not insist that a suitable XSD schema deserializer is registered.
     * PopulatedExtensionRegistry registers SchemaDeserializer by default, but 
     * if the user chooses not to register a suitable deserializer then the
     * UnknownDeserializer will be used, returning an UnknownExtensibilityElement. 
     */
     
    SchemaPtr schema;
    try
    {

      QNamePtr elementType = DOMUtils::newQName(el);
      
      ExtensionDeserializerPtr exDS = 
          extReg->queryDeserializer(parentType, elementType);
      
      //Now unmarshall the DOM element.
      ExtensibilityElementPtr ee =  
          exDS->unmarshall(parentType, elementType, el, def, extReg);
          
      return ee;
      
//      if ( (SchemaConstants::XSD_QNAME_LIST)->find(ee->getElementType()) 
//            != (SchemaConstants::XSD_QNAME_LIST)->end() )
//      {
//           schema = ee.downcastTo<Schema>();
//      }
//      else
//      {
//        //Unknown extensibility element, so don't do any more schema parsing on it.
//          return ee;
//      }
//
//
//      //Keep track of parsed schemas to avoid duplicating Schema objects
//      //through duplicate or circular references (eg: A imports B imports A).
//      if (schema->getDocumentBaseURI() != null) 
//      {
//        this->allSchemas->insert(Schema::Map::value_type(schema->getDocumentBaseURI(), schema));
//      }
//          
//      //At this point, any SchemaReference objects held by the schema will not 
//      //yet point to their referenced schemas, so we must now retrieve these 
//      //schemas and set the schema references.
//          
//      //First, combine the schema references for imports, includes and redefines 
//      //into a single list
//      
//      SchemaReference::ListPtr allSchemaRefs(new SchemaReference::List());
//    
//      SchemaImport::ListMap::iterator it = schema->getImports()->begin();
//      
//      SchemaReference::List::iterator lit, lie;
//      
//      for(SchemaImport::ListMap::iterator mit = schema->getImports()->begin(),
//        mie = schema->getImports()->end(); mit != mie; mit++)
//      {
//          for (lit = mit->second->begin(), lie = mit->second->end();
//              lit != lie; lit++ )
//          {
//              allSchemaRefs->push_back(*lit);
//          }
//      }
//    
//      for (lit = schema->getIncludes()->begin(), 
//          lie = schema->getIncludes()->end();
//          lit != lie; lit++ )
//      {
//          allSchemaRefs->push_back(*lit);
//      }
//    
//      for (lit = schema->getRedefines()->begin(), 
//          lie = schema->getRedefines()->end();
//          lit != lie; lit++ )
//      {
//          allSchemaRefs->push_back(*lit);
//      }
//          
//      //Then, retrieve the schema referred to by each schema reference. If the 
//      //schema has been read in previously, use the existing schema object. 
//      //Otherwise unmarshall the DOM element into a new schema object.
//          
//      for (lit = allSchemaRefs->begin(), 
//          lie = allSchemaRefs->end();
//          lit != lie; lit++ )
//      {
//        try
//        {
//          schemaRef = *lit;
//              
//          if (schemaRef->getSchemaLocationURI() == null)
//          {
//            //cannot get the referenced schema, so ignore this schema reference
//            continue;
//          }
//          
//          if (verbose)
//          {
//            cout << "Retrieving schema at '" << 
//                               schemaRef->getSchemaLocationURI().toLocal();
//              if (schema->getDocumentBaseURI() == null)
//              {
//                cout << "'.";
//              }
//              else
//              {
//                  cout << "', relative to '" << 
//                               schema->getDocumentBaseURI().toLocal() << "'." << endl;
//              }
//          }
//
//              
//          InputStream inputStream = null;
//          InputSource inputSource = null;
//              
//          //This is the child schema referred to by the schemaReference
//          Schema referencedSchema = null;
//              
//          //This is the child schema's location obtained from the WSDLLocator or the URL
//          String location = null;
//
//          if (loc != null)
//          {
//            //Try to get the referenced schema using the wsdl locator
//            inputSource = loc.getImportInputSource(
//              schema->getDocumentBaseURI(), schemaRef->getSchemaLocationURI());
//        
//            if (inputSource == null)
//            {
//              throw new WSDLException(WSDLException.OTHER_ERROR,
//                        "Unable to locate with a locator "
//                        + "the schema referenced at '"
//                        + schemaRef->getSchemaLocationURI() 
//                        + "' relative to document base '"
//                        + schema->getDocumentBaseURI() + "'");
//            }
//            location = loc.getLatestImportURI();
//                
//            //if a schema from this location has been read previously, use it.
//            referencedSchema = (Schema) this.allSchemas.get(location);
//          }
//          else
//          {
//            // We don't have a wsdl locator, so try to retrieve the schema by its URL
//            String contextURI = schema->getDocumentBaseURI();
//            URL contextURL = (contextURI != null) ? StringUtils.getURL(null, contextURI) : null;
//            URL url = StringUtils.getURL(contextURL, schemaRef->getSchemaLocationURI());
//            location = url.toExternalForm();
//                    
//            //if a schema from this location has been retrieved previously, use it.
//            referencedSchema = (Schema) this.allSchemas.get(location);
//
//            if (referencedSchema == null)
//            {
//              // We haven't read this schema in before so do it now
//              inputStream = StringUtils.getContentAsInputStream(url);
//
//              if (inputStream != null)
//              {
//                inputSource = new InputSource(inputStream);
//              }
//            
//              if (inputSource == null)
//              {
//                throw new WSDLException(WSDLException.OTHER_ERROR,
//                          "Unable to locate with a url "
//                          + "the document referenced at '"
//                          + schemaRef->getSchemaLocationURI()
//                          + "'"
//                          + (contextURI == null ? "." : ", relative to '"
//                          + contextURI + "'."));
//              }
//            }  
//        
//          } //end if loc
//              
//          // If we have not previously read the schema, get its DOM element now.
//          if (referencedSchema == null)
//          {
//            inputSource.setSystemId(location);
//            Document doc = getDocument(inputSource, location);
//
//            if (inputStream != null)
//            {
//              inputStream.close();
//            }
//
//            Element documentElement = doc.getDocumentElement();
//
//            // If it's a schema doc process it, otherwise the schema reference remains null
//
//            QNamePtr docElementQName = DOMUtils::newQName(documentElement);
//
//            if (SchemaConstants.XSD_QNAME_LIST.contains(docElementQName))
//            {
//              //We now need to call parseSchema recursively to parse the referenced
//              //schema. The document base URI of the referenced schema will be set to 
//              //the document base URI of the current schema plus the schemaLocation in 
//              //the schemaRef. We cannot explicitly pass in a new document base URI
//              //to the schema deserializer, so instead we will create a dummy 
//              //Definition and set its documentBaseURI to the new document base URI. 
//              //We can leave the other definition fields empty because we know
//              //that the SchemaDeserializer.unmarshall method uses the definition 
//              //parameter only to get its documentBaseURI. If the unmarshall method
//              //implementation changes (ie: its use of definition changes) we may need 
//              //to rethink this approach.
//              
//              WSDLFactory factory = getWSDLFactory();
//              Definition dummyDef = factory.newDefinition();
//            
//              dummyDef.setDocumentBaseURI(location);
//
//              //By this point, we know we have a SchemaDeserializer registered
//              //so we can safely cast the ExtensibilityElement to a Schema.
//              referencedSchema = (Schema) parseSchema( parentType, 
//                                                       documentElement, 
//                                                       dummyDef,
//                                                       extReg);
//            }
//        
//          } //end if referencedSchema
//
//          schemaRef->setReferencedSchema(referencedSchema);      
//        }
//        catch (const WSDLException& e)
//        {
//          throw e;
//        }
//        catch (Throwable t)
//        {
//          throw new WSDLException(WSDLException.OTHER_ERROR,
//                    "An error occurred trying to resolve schema referenced at '" 
//                    + schemaRef->getSchemaLocationURI() 
//                    + "'"
//                    + (schema->getDocumentBaseURI() == null ? "." : ", relative to '"
//                    + schema->getDocumentBaseURI() + "'."),
//                    t);
//        }
//        
//      } //end while loop

      return schema;

    }
    catch (const WSDLException& e)
    {
//      if (e.getLocation() == null)
//      {
//        e.setLocation(XPathUtils.getXPathExprFromNode(el));
//      }
//      else
//      {
//        //If this method has been called recursively for nested schemas
//        //the exception location must be built up recursively too so
//        //prepend this element's xpath to exception location.
//        String loc = XPathUtils.getXPathExprFromNode(el) + e.getLocation();
//        e.setLocation(loc);
//      }

      throw e; 
    }
    
}


MessagePtr WsdlReader::parseMessage(DOMElement* msgEl, DefinitionsPtr def)
   throw(WSDLException)
{
    DOMUtils::AttrPtrListPtr remainingAttrs = DOMUtils::getAttributes(msgEl);
    
    XMLChString name = DOMUtils::getAttribute(msgEl, 
	    							Constants::ATTR_NAME, remainingAttrs);
    
    //This element cannot contain extension attributes, so check for
    //unexpected remaining attributes.
    if (!remainingAttrs->empty()) {
        DOMUtils::throwWSDLException(msgEl, remainingAttrs);
    }
	    
    MessagePtr msg;
    if (name != null)
    {
        QNamePtr messageName(new WSDL_NAMESPACE::QName(def->getTargetNamespace(), name));

        msg = def->getMessage(messageName);

        if (!msg)
        {
            msg = def->createMessage();
            msg->setQName(messageName);
        }
    }
    else
    {
        msg = def->createMessage();
    }
    

    // Whether it was retrieved or created, the definition has been found.
    msg->setUndefined(false);

    DOMElement* tempEl = DOMUtils::getFirstChildElement(msgEl);

    while (tempEl)
    {
        if (DOMUtils::matches(Constants::Q_ELEM_DOCUMENTATION, tempEl))
        {
	        msg->setDocumentationElement(tempEl);
        }
        else if (DOMUtils::matches(Constants::Q_ELEM_PART, tempEl))
        {
	        msg->addPart(parsePart(tempEl, def));
        }
//        else  
//        {
//	        msg->addExtensibilityElement(
//	          parseExtensibilityElement(Message.class, tempEl, def));
//        }
//
        tempEl = DOMUtils::getNextSiblingElement(tempEl);
    }

    return msg;
}

PartPtr WsdlReader::parsePart(DOMElement* partEl, DefinitionsPtr def)
    throw(WSDLException)
{
    PartPtr part = def->createPart();
    XMLChString name = DOMUtils::getAttribute(partEl, Constants::ATTR_NAME);

    QNamePtr elementName = getQualifiedAttributeValue(partEl,
                                                   Constants::ATTR_ELEMENT,
                                                   Constants::ELEM_MESSAGE,
                                                   def);
    QNamePtr typeName = getQualifiedAttributeValue(partEl,
                                                Constants::ATTR_TYPE,
                                                Constants::ELEM_MESSAGE,
                                                def);

    if (name != null)
    {
        part->setName(name);
    }

    if (elementName)
    {
        part->setElementName(elementName);
    }

    if (typeName)
    {
        part->setTypeName(typeName);
    }

    DOMElement* tempEl = DOMUtils::getFirstChildElement(partEl);

    while (tempEl)
    {
        if (DOMUtils::matches(Constants::Q_ELEM_DOCUMENTATION, tempEl))
        {
        	part->setDocumentationElement(tempEl);
        }
        else
        {
        	DOMUtils::throwWSDLException(tempEl);
        }

        tempEl = DOMUtils::getNextSiblingElement(tempEl);
    }

    parseExtensibilityAttributes(partEl, Constants::Q_ELEM_PART, part, def);//@rev09

    return part;
}

QNamePtr WsdlReader::getQualifiedAttributeValue(DOMElement* el,
                                  const XMLCh* attrName,
                                  const XMLCh* elDesc,
                                  DefinitionsPtr def)
                                    throw(WSDLException)
{
    try
    {
      return DOMUtils::getQualifiedAttributeValue(el,
                                                 attrName,
                                                 elDesc,
                                                 false,
                                                 def);
    }
    catch (const WSDLException& e)
    {
        if (e.getFaultCode() == WSDLException::NO_PREFIX_SPECIFIED )
        {
        	XMLChString attrValue = DOMUtils::getAttribute(el, attrName);

        	return (QNamePtr)new WSDL_NAMESPACE::QName(attrValue);
        }
        	else
        {
        	throw e;
        }
    }
}
  
PortTypePtr WsdlReader::parsePortType(DOMElement* portTypeEl, DefinitionsPtr def)
	 throw(WSDLException)
{
	PortTypePtr portType;
    
    XMLChString name = DOMUtils::getAttribute(portTypeEl, Constants::ATTR_NAME);
    if ( name != null )
    {

        QNamePtr portTypeName(new WSDL_NAMESPACE::QName(def->getTargetNamespace(), name));

        portType = def->getPortType(portTypeName);

      	if (!portType)
        {
            portType = def->createPortType();
            portType->setQName(portTypeName);
        }
    }
    else
    {
        portType = def->createPortType();
    }

    // Whether it was retrieved or created, the definition has been found.
    portType->setUndefined(false);

    DOMElement* tempEl = DOMUtils::getFirstChildElement(portTypeEl);

    while (tempEl)
    {
        if (DOMUtils::matches(Constants::Q_ELEM_DOCUMENTATION, tempEl))
        {
        	portType->setDocumentationElement(tempEl);
        }
        else if (DOMUtils::matches(Constants::Q_ELEM_OPERATION, tempEl))
        {
	        OperationPtr op = parseOperation(tempEl, portType, def);
	
	        if (op)
	        {
	          portType->addOperation(op);
	        }
        }
        else
        {
        	DOMUtils::throwWSDLException(tempEl);
        }

        tempEl = DOMUtils::getNextSiblingElement(tempEl);
    }

    parseExtensibilityAttributes(portTypeEl, Constants::Q_ELEM_PORT_TYPE, portType, def); //@rev09

    return portType;
}

OperationPtr WsdlReader::parseOperation(DOMElement* opEl,
                         PortTypePtr portType,
                         DefinitionsPtr def)
     throw (WSDLException)
{
    OperationPtr op;
    
    DOMUtils::AttrPtrListPtr remainingAttrs = DOMUtils::getAttributes(opEl);

    XMLChString name = DOMUtils::getAttribute(opEl, 
    						Constants::ATTR_NAME, remainingAttrs);
	
    XMLChString parameterOrderStr = DOMUtils::getAttribute(opEl,
             Constants::ATTR_PARAMETER_ORDER, remainingAttrs);
    
    //This element cannot contain extension attributes, so check for
    //unexpected remaining attributes.
    if (!remainingAttrs->empty()) {
        DOMUtils::throwWSDLException(opEl, remainingAttrs);;
    }
    
    DOMElement* tempEl = DOMUtils::getFirstChildElement(opEl);
    vector<XMLChString> messageOrder;
    DOMElement* docEl = 0;
    InputPtr input;
    OutputPtr output;
    vector<FaultPtr> faults;
//    List extElements = new Vector();
    bool retrieved = true;

    while (tempEl)
    {
      if (DOMUtils::matches(Constants::Q_ELEM_DOCUMENTATION, tempEl))
      {
        docEl = tempEl;
      }
      else if (DOMUtils::matches(Constants::Q_ELEM_INPUT, tempEl))
      {
        input = parseInput(tempEl, def);
        messageOrder.push_back(Constants::ELEM_INPUT);
      }
      else if (DOMUtils::matches(Constants::Q_ELEM_OUTPUT, tempEl))
      {
        output = parseOutput(tempEl, def);
        messageOrder.push_back(Constants::ELEM_OUTPUT);
      }
      else if (DOMUtils::matches(Constants::Q_ELEM_FAULT, tempEl))
      {
        faults.push_back(parseFault(tempEl, def));
      }
      else 
      {
        // TODO extElements.add(
        //    parseExtensibilityElement(Operation.class, tempEl, def));
      }

      tempEl = DOMUtils::getNextSiblingElement(tempEl);
    }

    if (name != null)
    {
        XMLChString inputName = (input ? input->getName() : null);
        XMLChString outputName = (output ? output->getName() : null);

      op = portType->getOperation(name, inputName, outputName);

      if ( op && !op->isUndefined())
      {
          op = (OperationPtr)0;
      }

      if (op)
      {
        if (inputName == null)
        {
          InputPtr tempIn = op->getInput();

          if (tempIn)
          {
            if (tempIn->getName() != null)
            {
              op = (OperationPtr)0;
            }
          }
        }
      }

      if (op)
      {
        if (outputName == null)
        {
          OutputPtr tempOut = op->getOutput();

          if (tempOut)
          {
            if (tempOut->getName() != null)
            {
              op = (OperationPtr)0;
            }
          }
        }
      }

      if (!op)
      {
          op = def->createOperation();
          op->setName(name);
          retrieved = false;
      }
    }
    else
    {
        op = def->createOperation();
        retrieved = false;
    }

    // Whether it was retrieved or created, the definition has been found.
    op->setUndefined(false);

    if (parameterOrderStr != null)
    {
        op->setParameterOrdering(StringUtils::parseNMTokens(parameterOrderStr));
    }

    if (docEl)
    {
        op->setDocumentationElement(docEl);
    }

    if (input)
    {
      op->setInput(input);
    }

    if (output)
    {
      op->setOutput(output);
    }

    if (faults.size() > 0)
    {
        for (size_t i=0, l=faults.size(); i<l; i++)
        {
           op->addFault(faults[i]);
        }
    }

//    if (extElements.size() > 0)
//    {
//      Iterator eeIterator = extElements.iterator();
//      
//      while (eeIterator.hasNext())
//      {
//        op->addExtensibilityElement(
//            (ExtensibilityElement) eeIterator.next() );
//      }
//    }
//    
    OperationTypePtr style;

    if (messageOrder == Constants::STYLE_ONE_WAY)
    {
        style = OperationType::ONE_WAY;
    }
    else if (messageOrder == Constants::STYLE_REQUEST_RESPONSE)
    {
      style = OperationType::REQUEST_RESPONSE;
    }
    else if (messageOrder == Constants::STYLE_SOLICIT_RESPONSE)
    {
      style = OperationType::SOLICIT_RESPONSE;
    }
    else if (messageOrder == Constants::STYLE_NOTIFICATION)
    {
      style = OperationType::NOTIFICATION;
    }

    if (style)
    {
        op->setStyle(style);
    }

    if (retrieved)
    {
        op = (OperationPtr)0;
    }

    return op;
}

InputPtr WsdlReader::parseInput(DOMElement* inputEl, DefinitionsPtr def)
    throw (WSDLException)
  {
    InputPtr input = def->createInput();
    
    XMLChString name = DOMUtils::getAttribute(inputEl, Constants::ATTR_NAME);
    
    QNamePtr messageName = getQualifiedAttributeValue(inputEl,
                                                   Constants::ATTR_MESSAGE,
                                                   Constants::ELEM_INPUT,
                                                   def);

    if (name != null)
    {
      input->setName(name);
    }

    if (messageName)
    {
      MessagePtr message = def->getMessage(messageName);

      if (!message)
      {
        message = def->createMessage();
        message->setQName(messageName);
        def->addMessage(message);
      }

      input->setMessage(message);
    }

    DOMElement* tempEl = DOMUtils::getFirstChildElement(inputEl);

    while (tempEl)
    {
      if (DOMUtils::matches(Constants::Q_ELEM_DOCUMENTATION, tempEl))
      {
        input->setDocumentationElement(tempEl);
      }
      else
      {
        DOMUtils::throwWSDLException(tempEl);
      }

      tempEl = DOMUtils::getNextSiblingElement(tempEl);
    }

    parseExtensibilityAttributes(inputEl, Constants::Q_ELEM_INPUT, input, def);//@rev09

    return input;
  }

OutputPtr WsdlReader::parseOutput(DOMElement* outputEl, DefinitionsPtr def)
    throw (WSDLException)
  {
    OutputPtr output = def->createOutput();

    XMLChString name = DOMUtils::getAttribute(outputEl, Constants::ATTR_NAME);
    
    QNamePtr messageName = getQualifiedAttributeValue(outputEl,
                                                   Constants::ATTR_MESSAGE,
                                                   Constants::ELEM_OUTPUT,
                                                   def);

    if (name != null)
    {
      output->setName(name);
    }

    if (messageName)
    {
      MessagePtr message = def->getMessage(messageName);

      if (!message)
      {
        message = def->createMessage();
        message->setQName(messageName);
        def->addMessage(message);
      }

      output->setMessage(message);
    }

    DOMElement* tempEl = DOMUtils::getFirstChildElement(outputEl);

    while (tempEl)
    {
      if (DOMUtils::matches(Constants::Q_ELEM_DOCUMENTATION, tempEl))
      {
        output->setDocumentationElement(tempEl);
      }
      else
      {
        DOMUtils::throwWSDLException(tempEl);
      }

      tempEl = DOMUtils::getNextSiblingElement(tempEl);
    }

    parseExtensibilityAttributes(outputEl, Constants::Q_ELEM_OUTPUT, output, def);//@rev09

    return output;
  }

FaultPtr WsdlReader::parseFault(DOMElement* faultEl, DefinitionsPtr def)
    throw (WSDLException)
{
    FaultPtr fault = def->createFault();

    XMLChString name = DOMUtils::getAttribute(faultEl, Constants::ATTR_NAME);

    QNamePtr messageName = getQualifiedAttributeValue(faultEl,
                                                   Constants::ATTR_MESSAGE,
                                                   Constants::ELEM_FAULT,
                                                   def);

    if (name != null)
    {
      fault->setName(name);
    }

    if (messageName)
    {
      MessagePtr message = def->getMessage(messageName);

      if (!message)
      {
        message = def->createMessage();
        message->setQName(messageName);
        def->addMessage(message);
      }

      fault->setMessage(message);
    }

    DOMElement* tempEl = DOMUtils::getFirstChildElement(faultEl);

    while (tempEl)
    {
      if (DOMUtils::matches(Constants::Q_ELEM_DOCUMENTATION, tempEl))
      {
        fault->setDocumentationElement(tempEl);
      }
      else
      {
        DOMUtils::throwWSDLException(tempEl);
      }

      tempEl = DOMUtils::getNextSiblingElement(tempEl);
    }

    parseExtensibilityAttributes(faultEl, Constants::Q_ELEM_FAULT, fault, def);//@rev09

    return fault;
}

BindingPtr WsdlReader::parseBinding(DOMElement* bindingEl, DefinitionsPtr def)
	 throw(WSDLException)
{
    BindingPtr binding;
    
    DOMUtils::AttrPtrListPtr remainingAttrs = DOMUtils::getAttributes(bindingEl);

    XMLChString name = DOMUtils::getAttribute(
	    	bindingEl, Constants::ATTR_NAME, remainingAttrs);
    
    QNamePtr portTypeName = getQualifiedAttributeValue(bindingEl,
                                                    Constants::ATTR_TYPE,
                                                    Constants::ELEM_BINDING,
                                                    def,
                                                    remainingAttrs);
    
    //This element cannot contain extension attributes, so check for
    //unexpected remaining attributes.
    if (!remainingAttrs->empty()) {
        DOMUtils::throwWSDLException(bindingEl, remainingAttrs);;
    }
    
    if ( name != null )
    {
        QNamePtr bindingName(new WSDL_NAMESPACE::QName(def->getTargetNamespace(), name));

        binding = def->getBinding(bindingName);

        if (!binding)
        {
	        binding = def->createBinding();
	        binding->setQName(bindingName);
        }
    }
    else
    {
        binding = def->createBinding();
    }

//    // Whether it was retrieved or created, the definition has been found.
    binding->setUndefined(false);

    PortTypePtr portType;

    if ( portTypeName )
    {
        portType = def->getPortType(portTypeName);

        if (!portType)
        {
	        portType = def->createPortType();
	        portType->setQName(portTypeName);
	        def->addPortType(portType);
        }

        binding->setPortType(portType);
    }

    DOMElement* tempEl = DOMUtils::getFirstChildElement(bindingEl);

    while (tempEl)
    {
      if (DOMUtils::matches(Constants::Q_ELEM_DOCUMENTATION, tempEl))
      {
        binding->setDocumentationElement(tempEl);
      }
      else if (DOMUtils::matches(Constants::Q_ELEM_OPERATION, tempEl))
      {
        binding->addBindingOperation(parseBindingOperation(tempEl,
                                                          portType,
                                                          def));
      }
      else
      {
          binding->addExtensibilityElement(parseExtensibilityElement(
            Constants::Q_ELEM_BINDING, tempEl, def));
      }

      tempEl = DOMUtils::getNextSiblingElement(tempEl);
    }

    return binding;
}

BindingOperationPtr WsdlReader::parseBindingOperation(
    DOMElement* bindingOperationEl,
    PortTypePtr portType,
    DefinitionsPtr def)
      throw (WSDLException)
  {
    BindingOperationPtr bindingOperation = def->createBindingOperation();
    
    DOMUtils::AttrPtrListPtr remainingAttrs = DOMUtils::getAttributes(bindingOperationEl);
    XMLChString name= DOMUtils::getAttribute(bindingOperationEl,
                                        Constants::ATTR_NAME,
                                        remainingAttrs);
    
    //This element cannot contain extension attributes, so check for
    //unexpected remaining attributes.
    if (!remainingAttrs->empty()) {
        DOMUtils::throwWSDLException(bindingOperationEl, remainingAttrs);;
    }

    if (name != null)
    {
      bindingOperation->setName(name);
    }

    DOMElement* tempEl = DOMUtils::getFirstChildElement(bindingOperationEl);

    while (tempEl)
    {
      if (DOMUtils::matches(Constants::Q_ELEM_DOCUMENTATION, tempEl))
      {
        bindingOperation->setDocumentationElement(tempEl);
      }
      else if (DOMUtils::matches(Constants::Q_ELEM_INPUT, tempEl))
      {
        bindingOperation->setBindingInput(parseBindingInput(tempEl, def));
      }
      else if (DOMUtils::matches(Constants::Q_ELEM_OUTPUT, tempEl))
      {
        bindingOperation->setBindingOutput(parseBindingOutput(tempEl, def));
      }
      else if (DOMUtils::matches(Constants::Q_ELEM_FAULT, tempEl))
      {
        bindingOperation->addBindingFault(parseBindingFault(tempEl, def));
      }
      else
      {
          bindingOperation->addExtensibilityElement(
            parseExtensibilityElement(Constants::Q_ELEM_OPERATION, tempEl, def));
      }

      tempEl = DOMUtils::getNextSiblingElement(tempEl);
    }

    if (portType)
    {
      BindingInputPtr bindingInput = bindingOperation->getBindingInput();
      BindingOutputPtr bindingOutput = bindingOperation->getBindingOutput();
      XMLChString inputName =
        (bindingInput ? bindingInput->getName() : null);                /* @c25514 */
      XMLChString outputName =
        (bindingOutput ? bindingOutput->getName() : null);              /* @c25514 */
      OperationPtr op = portType->getOperation(name, inputName, outputName);

      if (!op)
      {
        InputPtr input = def->createInput();
        OutputPtr output = def->createOutput();

        op = def->createOperation();
        op->setName(name);
        input->setName(inputName);
        output->setName(outputName);
        op->setInput(input);
        op->setOutput(output);
        portType->addOperation(op);
      }

      bindingOperation->setOperation(op);
    }

    return bindingOperation;
  }

BindingInputPtr WsdlReader::parseBindingInput(DOMElement* bindingInputEl,
                                           DefinitionsPtr def)
                                             throw (WSDLException)
{
    BindingInputPtr bindingInput = def->createBindingInput();
    
    DOMUtils::AttrPtrListPtr remainingAttrs = DOMUtils::getAttributes(bindingInputEl);

    XMLChString name = DOMUtils::getAttribute(bindingInputEl,
                                        Constants::ATTR_NAME,
                                        remainingAttrs);
    
    //This element cannot contain extension attributes, so check for
    //unexpected remaining attributes.
    if (!remainingAttrs->empty()) {
        DOMUtils::throwWSDLException(bindingInputEl, remainingAttrs);;
    }

    if (name != null)
    {
      bindingInput->setName(name);
    }

    DOMElement* tempEl = DOMUtils::getFirstChildElement(bindingInputEl);

    while (tempEl)
    {
      if (DOMUtils::matches(Constants::Q_ELEM_DOCUMENTATION, tempEl))
      {
        bindingInput->setDocumentationElement(tempEl);
      }
      else
      {
          bindingInput->addExtensibilityElement(
            parseExtensibilityElement(Constants::Q_ELEM_INPUT, tempEl, def));
      }

      tempEl = DOMUtils::getNextSiblingElement(tempEl);
    }

    return bindingInput;
  }

BindingOutputPtr WsdlReader::parseBindingOutput(DOMElement* bindingOutputEl,
                                             DefinitionsPtr def)
                                               throw (WSDLException)
  {
    BindingOutputPtr bindingOutput = def->createBindingOutput();
    
    DOMUtils::AttrPtrListPtr remainingAttrs = DOMUtils::getAttributes(bindingOutputEl);
    XMLChString name = DOMUtils::getAttribute(bindingOutputEl,
                                        Constants::ATTR_NAME,
                                        remainingAttrs);
    
    //This element cannot contain extension attributes, so check for
    //unexpected remaining attributes.
    if (!remainingAttrs->empty()) {
        DOMUtils::throwWSDLException(bindingOutputEl, remainingAttrs);;
    }

    if (name != null)
    {
      bindingOutput->setName(name);
    }

    DOMElement* tempEl = DOMUtils::getFirstChildElement(bindingOutputEl);

    while (tempEl)
    {
      if (DOMUtils::matches(Constants::Q_ELEM_DOCUMENTATION, tempEl))
      {
        bindingOutput->setDocumentationElement(tempEl);
      }
      else
      {
          bindingOutput->addExtensibilityElement(
            parseExtensibilityElement(Constants::Q_ELEM_OUTPUT, tempEl, def));
      }

      tempEl = DOMUtils::getNextSiblingElement(tempEl);
    }

    return bindingOutput;
  }

BindingFaultPtr WsdlReader::parseBindingFault(DOMElement* bindingFaultEl,
                                           DefinitionsPtr def)
                                             throw (WSDLException)
{
    BindingFaultPtr bindingFault = def->createBindingFault();
    
    DOMUtils::AttrPtrListPtr remainingAttrs = DOMUtils::getAttributes(bindingFaultEl);
    XMLChString name = DOMUtils::getAttribute(bindingFaultEl,
                                        Constants::ATTR_NAME,
                                        remainingAttrs);

    //This element cannot contain extension attributes, so check for
    //unexpected remaining attributes.
    if (!remainingAttrs->empty()) {
        DOMUtils::throwWSDLException(bindingFaultEl, remainingAttrs);;
    }
    
    if (name != null)
    {
      bindingFault->setName(name);
    }

    DOMElement* tempEl = DOMUtils::getFirstChildElement(bindingFaultEl);

    while (tempEl)
    {
      if (DOMUtils::matches(Constants::Q_ELEM_DOCUMENTATION, tempEl))
      {
        bindingFault->setDocumentationElement(tempEl);
      }
      else
      {
        bindingFault->addExtensibilityElement(
          parseExtensibilityElement(Constants::Q_ELEM_FAULT, tempEl, def));
      }

      tempEl = DOMUtils::getNextSiblingElement(tempEl);
    }

    return bindingFault;
}

ServicePtr WsdlReader::parseService(DOMElement* serviceEl, DefinitionsPtr def)
	 throw(WSDLException)
{
    ServicePtr theService;
    
    DOMUtils::AttrPtrListPtr remainingAttrs = DOMUtils::getAttributes(serviceEl);
    
    XMLChString name = DOMUtils::getAttribute(serviceEl, 
	    			Constants::ATTR_NAME, remainingAttrs);
    
    //This element cannot contain extension attributes, so check for
    //unexpected remaining attributes.
    if (!remainingAttrs->empty()) {
        DOMUtils::throwWSDLException(serviceEl, remainingAttrs);;
    }

    if ( name != null )
    {
        QNamePtr serviceName(new WSDL_NAMESPACE::QName(def->getTargetNamespace(), name));

        theService = def->getService(serviceName);

        if (!theService)
        {
	        theService = def->createService();
	        theService->setQName(serviceName);
        }
    }
    else
    {
        theService = def->createService();
    }

    DOMElement* tempEl = DOMUtils::getFirstChildElement(serviceEl);

    while (tempEl)
    {
      if (DOMUtils::matches(Constants::Q_ELEM_DOCUMENTATION, tempEl))
      {
        theService->setDocumentationElement(tempEl);
      }
      else if (DOMUtils::matches(Constants::Q_ELEM_PORT, tempEl))
      {
        theService->addPort(parsePort(tempEl, def));
      }
      else
      {
          theService->addExtensibilityElement(
            parseExtensibilityElement(theService->getQName(), tempEl, def));
      }

      tempEl = DOMUtils::getNextSiblingElement(tempEl);
    }

    return theService;
}

PortPtr WsdlReader::parsePort(DOMElement* portEl, DefinitionsPtr def)
    throw (WSDLException)
{
    PortPtr port = def->createPort();
    DOMUtils::AttrPtrListPtr remainingAttrs = DOMUtils::getAttributes(portEl);
    
    XMLChString name = DOMUtils::getAttribute(portEl, 
                    Constants::ATTR_NAME, remainingAttrs);
    QNamePtr bindingStr = getQualifiedAttributeValue(portEl,
                                                  Constants::ATTR_BINDING,
                                                  Constants::ELEM_PORT,
                                                  def,
                                                  remainingAttrs);
    
    //This element cannot contain extension attributes, so check for
    //unexpected remaining attributes.
    if (!remainingAttrs->empty()) {
        DOMUtils::throwWSDLException(portEl, remainingAttrs);;
    }

    if (name != null)
    {
      port->setName(name);
    }

    if ( bindingStr )
    {
      BindingPtr binding = def->getBinding(bindingStr);

      if (!binding)
      {
        binding = def->createBinding();
        binding->setQName(bindingStr);
        def->addBinding(binding);
      }

      port->setBinding(binding);
    }

    DOMElement* tempEl = DOMUtils::getFirstChildElement(portEl);

    while (tempEl)
    {
      if (DOMUtils::matches(Constants::Q_ELEM_DOCUMENTATION, tempEl))
      {
        port->setDocumentationElement(tempEl);
      }
      else
      {
        port->addExtensibilityElement(parseExtensibilityElement(
           Constants::Q_ELEM_PORT,
           tempEl,
           def));
      }

      tempEl = DOMUtils::getNextSiblingElement(tempEl);
    }

    return port;
  }

ExtensibilityElementPtr WsdlReader::parseExtensibilityElement(
    QNamePtr parentType,
    DOMElement* el,
    DefinitionsPtr def)
      throw (WSDLException)
  {
    QNamePtr elementType = DOMUtils::newQName(el);
    
    XMLChString namespaceURI(el->getNamespaceURI());
    
    try
    {
      if (namespaceURI == null || namespaceURI == (XMLChString)Constants::NS_URI_WSDL )
      {
        throw WSDLException(WSDLException::INVALID_WSDL,
                  string("Encountered illegal extension element '")
                  .append(toLocal(elementType->toString()))
                  .append("' in the context of a '")
                  .append(toLocal(parentType->toString()))
                  .append("'. Extension elements must be in ")
                  .append("a namespace other than WSDL's."));
      }
      
      ExtensionRegistryPtr extReg = def->getExtensionRegistry();

      if (!extReg)
      {
        
        throw WSDLException(WSDLException::CONFIGURATION_ERROR,
               string("No ExtensionRegistry set for this ")
               .append("Definition, so unable to deserialize a '")
               .append(toLocal(elementType->toString()))
               .append("' element in the context of a '")
               .append(toLocal(parentType->toString()))
               .append("'."));
      }

      ExtensionDeserializerPtr extDS = extReg->queryDeserializer(
                parentType, elementType);

      return extDS->unmarshall(parentType, elementType, el, def, extReg);
    }
    catch (const WSDLException& e)
    {
//      if (e.getLocation() == null)
//      {
//        TODO: e.setLocation(XPathUtils.getXPathExprFromNode(el));
//      }

      throw e;
    }
}

//@rev09
void WsdlReader::parseExtensibilityAttributes(DOMElement* el,
                                              QNamePtr parentType,
                                              AttributeExtensiblePtr attrExt,
                                              DefinitionsPtr def)
                                                throw (WSDLException)
{
    XMLChString::SetPtr nativeAttributeNames = attrExt->getNativeAttributeNames();
    
    DOMNamedNodeMap * nodeMap = el->getAttributes();
    int length = nodeMap->getLength();

    for (int i = 0; i < length; i++)
    {
      DOMAttr* attribute = (DOMAttr*)nodeMap->item(i);
      XMLChString localName = attribute->getLocalName();
      XMLChString namespaceURI = attribute->getNamespaceURI();
      XMLChString prefix = attribute->getPrefix();
      QNamePtr qname = (QNamePtr)new wsdl::QName(namespaceURI, localName);

      if (namespaceURI != null 
      		&& namespaceURI != (XMLChString)Constants::NS_URI_WSDL)
      {
        if (namespaceURI != (XMLChString)Constants::NS_URI_XMLNS)
        {
          DOMUtils::registerUniquePrefix(prefix, namespaceURI, def);

          XMLChString strValue = attribute->getValue();
          int attrType = ExtensibilityAttribute::NO_DECLARED_TYPE;
          ExtensionRegistryPtr extReg = def->getExtensionRegistry();

          if ( !extReg )
          {
            attrType = extReg->queryExtensionAttributeType(parentType, qname);
          }

          ExtensibilityAttributePtr val = parseExtensibilityAttribute(el, attrType, strValue, def);

          attrExt->setExtensionAttribute(qname, val);
        }
      }
      else if ( nativeAttributeNames->find(localName) == nativeAttributeNames->end() )
      {
          throw WSDLException(WSDLException::INVALID_WSDL,
                                                  string("Encountered illegal ")
                                                  .append("extension attribute '")
                                                  .append(toLocal(qname->toString()))
                                                  .append("'. Extension ")
                                                  .append("attributes must be in ")
                                                  .append("a namespace other than ")
                                                  .append("WSDL's."));

        //wsdlExc.setLocation(XPathUtils.getXPathExprFromNode(el));
      }
    }
}

ExtensibilityAttributePtr WsdlReader::parseExtensibilityAttribute(
	  DOMElement* el,
	  int attrType,
	  XMLChString attrValue,
	  DefinitionsPtr def)
         throw (WSDLException)
{
	ExtensibilityAttributePtr value(new ExtensibilityAttribute());
	value->setType(attrType);
	
    if (attrType == ExtensibilityAttribute::QNAME_TYPE)
    {
    	value->setQName(DOMUtils::getQName(attrValue, el, def));
    }
    else if (attrType == ExtensibilityAttribute::LIST_OF_STRINGS_TYPE)
    {
        value->setStringList(StringUtils::parseNMTokens(attrValue));
    }
    else if (attrType == ExtensibilityAttribute::LIST_OF_QNAMES_TYPE)
    {
        XMLChString::ListPtr oldList = StringUtils::parseNMTokens(attrValue);
        QName::ListPtr newList(new QName::List());

	    for(XMLChString::List::iterator i = oldList->begin(), l = oldList->end();
	        i != l; i++)
	    {
	        QNamePtr qValue = DOMUtils::getQName(*i, el, def);

	        newList->push_back(qValue);
	    }
    
        value->setQNameList(newList);
    }
    else if (attrType == ExtensibilityAttribute::STRING_TYPE)
    {
        value->setString(attrValue);
    }
    else
    {
        QNamePtr qValue;

        try
        {
            qValue = DOMUtils::getQName(attrValue, el, def);
        }
        catch (WSDLException e)
        {
            qValue = (QNamePtr)new QName(attrValue);
        }

        value->setQName(qValue);
    }
    
    return value;
}

QNamePtr WsdlReader::getQualifiedAttributeValue(
	DOMElement* el,
    const XMLCh* attrName,
    const XMLCh* elDesc,
    DefinitionsPtr def,
    DOMUtils::AttrPtrListPtr remainingAttrs)
    throw(WSDLException)
{
    try
    {
      return DOMUtils::getQualifiedAttributeValue(el,
                                                 attrName,
                                                 elDesc,
                                                 false,
                                                 def,
                                                 remainingAttrs);
    }
    catch (const WSDLException& e)
    {
        if (e.getFaultCode() == WSDLException::NO_PREFIX_SPECIFIED )
        {
        	XMLChString attrValue = DOMUtils::getAttribute(
        								el, attrName, remainingAttrs);

        	return (QNamePtr)new WSDL_NAMESPACE::QName(attrValue);
        }
        	else
        {
        	throw e;
        }
    }
}

void WsdlReader::checkElementName(DOMNode* node, const XMLCh* localName, 
	const XMLCh* namespaceURI) 
{
	if ( !match(node, localName, namespaceURI) )
	{
		throw WSDLException(WSDLException::INVALID_WSDL, 
			"checkElementName");
	}
}

bool WsdlReader::match(DOMNode* node, 
	const XMLCh* localName, const XMLCh* namespaceURI) 
{
	return ( XMLString::equals(node->getNamespaceURI(), namespaceURI)
		&& XMLString::equals(node->getLocalName(), localName) );
}

