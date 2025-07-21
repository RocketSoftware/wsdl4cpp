/*
 * %fv:XercesUtils.cpp-8 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * History:
 * 
 * revision  date    refnum    version  who  description
 * --------------------------------------------------------------------------
 * 01        060713            9.SOAP   mzu  Migrated from WSDL4J
 * 02        060713  t85128    9.SOAP   mzu  Change for xml schema cross-reference
 * 03        070213  cr25551   9.SOAP   mzu  Integrate libcurl
 * --------------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 * 
 */
#include "wsdl/wsdlxerces.hpp"

#include <iostream>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLURL.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMInputSource.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/internal/XMLGrammarPoolImpl.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/parsers/SAX2XMLReaderImpl.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLException.hpp>
//#include <xercesc/validators/common/Grammar.hpp>
#include <xercesc/validators/schema/SchemaGrammar.hpp>
#include <xercesc/validators/schema/TraverseSchema.hpp>

#include "wsdl/wsdlxerces.hpp"
#include "wsdl/schema/Schema.hpp"
#include "wsdl/schema/SchemaConstants.hpp"
#include "wsdl/util/XercesUtils.hpp"

#ifdef WSDL_USE_CURL
#include "xcurl/CurlInputSource.hpp"
#include "xcurl/CurlInputSourceBuilder.hpp"
#else
#include <xercesc/framework/URLInputSource.hpp>
#endif

USING_STD

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

XMLChString normalizeURL(XMLChString uri, MemoryManager* const manager)
{
//    //Normalize sysId 
//    XMLBuffer normalizedSysId(1023, fMemoryManager);
//    XMLString::removeChar(uri.c_str(), 0xFFFF, normalizedSysId);
//    const XMLCh* normalizedURI = normalizedSysId.getRawBuffer();
//
//    // Create a buffer for expanding the system id
//    XMLBuffer expSysId(1023, fMemoryManager);
//
//    XMLURL urlTmp(manager);
//    if ((!urlTmp.setURL(lastInfo.systemId, expSysId.getRawBuffer(), urlTmp)) ||
//        (urlTmp.isRelative()))
//    {
	XMLCh* cd = XMLPlatformUtils::getCurrentDirectory(manager);
	XMLChString cds(cd);
    XMLString::release(&cd);
    return cds;
}

InputSource* XercesUtils::createInputSource(const XMLCh* const        sysId
                                    , MemoryManager* const manager
                                    , const InputSourceEnvPtr ise
                                    , const bool standardUriConformant)
{
    InputSource* srcToFill = 0;
    XMLURL urlTmp(manager);
    if ( (!urlTmp.parse(sysId, urlTmp)) || (urlTmp.isRelative()) )
    {
        if (!standardUriConformant)
        {
            srcToFill = new (manager) LocalFileInputSource( sysId, manager );
        }
        else
            ThrowXMLwithMemMgr(MalformedURLException, XMLExcepts::URL_MalformedURL, manager);            
    }
    else
    {
        if (standardUriConformant && urlTmp.hasInvalidChar())
            ThrowXMLwithMemMgr(MalformedURLException, XMLExcepts::URL_MalformedURL, manager);
#ifdef WSDL_USE_CURL
		srcToFill = new CurlInputSource(urlTmp, manager);
        ((CurlInputSource*)srcToFill)->setInputSourceEnv(ise);
#else
		srcToFill = new URLInputSource(urlTmp, manager);
#endif
		//isb->createInputSource(
			//baseuri, normalizedURI);
				
    }
    return srcToFill;

}

DOMElement* XercesUtils::getFirstChildElement (DOMElement* elem)
{
    for (DOMNode* n = elem->getFirstChild (); n; n = n->getNextSibling ()) {
        if (n->getNodeType () == DOMNode::ELEMENT_NODE) {
        	return (DOMElement*)n;
        }
    }
    return 0;
}

DOMBuilder* XercesUtils::createDOMBuilder (XMLGrammarPool* const gramPool)
{
    AbstractDOMParser::ValSchemes valScheme = AbstractDOMParser::Val_Auto;
    bool                 doNamespaces       = true;
    bool                 doSchema           = false;
    bool                 schemaFullChecking = false;

    // Instantiate the DOM parser.
    static const XMLCh gLS[] = { chLatin_L, chLatin_S, chNull };
    
    DOMImplementation* impl = DOMImplementationRegistry::getDOMImplementation(gLS);
    DOMBuilder* parser =
            ((DOMImplementationLS*)impl)->createDOMBuilder(
                    DOMImplementationLS::MODE_SYNCHRONOUS, 0, XMLPlatformUtils::fgMemoryManager, gramPool)
        ;
    
//    try {
//    } catch (std::exception& e) {
//      std::cerr << e.what();
//      return 1;
//  }

    parser->setFeature(XMLUni::fgDOMNamespaces, doNamespaces);
    parser->setFeature(XMLUni::fgXercesSchema, doSchema);
    parser->setFeature(XMLUni::fgXercesSchemaFullChecking, schemaFullChecking);

    if (valScheme == AbstractDOMParser::Val_Auto)
    {
        parser->setFeature(XMLUni::fgDOMValidateIfSchema, true);
    }
    else if (valScheme == AbstractDOMParser::Val_Never)
    {
        parser->setFeature(XMLUni::fgDOMValidation, false);
    }
    else if (valScheme == AbstractDOMParser::Val_Always)
    {
        parser->setFeature(XMLUni::fgDOMValidation, true);
    }

    // enable datatype normalization - default is off
    parser->setFeature(XMLUni::fgDOMDatatypeNormalization, true);

    return parser;
}

WsdlXMLScanner::WsdlXMLScanner(XMLValidator* const valToAdopt
                      , GrammarResolver* const grammarResolver
                      , MemoryManager* const manager)
      : SGXMLScanner(valToAdopt, grammarResolver, manager)
      , traverseSchema(0)
	  , usingCURL(false)
{
}

// @rev02
WsdlXMLScanner::~WsdlXMLScanner() {
	if ( traverseSchema )
	    delete traverseSchema;
}

// @rev02
TraverseSchema* WsdlXMLScanner::getTraverseSchema() {
	return traverseSchema;
}
          
Grammar* WsdlXMLScanner::loadGrammar(const XMLCh* systemId, DOMElement* schemaElement, bool toCache) 
{
    try {
	
        SchemaGrammar* grammar = new (fGrammarPoolMemoryManager) SchemaGrammar(fGrammarPoolMemoryManager);
        XMLSchemaDescription* gramDesc = (XMLSchemaDescription*) grammar->getGrammarDescription();
        gramDesc->setContextType(XMLSchemaDescription::CONTEXT_PREPARSE);
        gramDesc->setLocationHints(systemId);

#ifdef WSDL_USE_CURL
		//@rev03 begin
		CurlInputSourceBuilder* cisBuilder = 0;
		if ( usingCURL )
		{
		    cisBuilder = new CurlInputSourceBuilder(fMemoryManager);
		}
		cisBuilder->setInputSourceEnv(getInputSourceEnv());
		//@rev03 end

        traverseSchema = new TraverseSchema //@rev02
        (
            schemaElement
            , fURIStringPool
            , (SchemaGrammar*) grammar
            , fGrammarResolver
            , this
            , systemId
            , fEntityHandler
            , fErrorReporter
            , fMemoryManager
            , (schemaElement == 0) //@rev02
			, cisBuilder //@rev03
        );
#else
        traverseSchema = new TraverseSchema
        (
            schemaElement
            , fURIStringPool
            , (SchemaGrammar*) grammar
            , fGrammarResolver
            , this
            , systemId
            , fEntityHandler
            , fErrorReporter
            , fMemoryManager
        );
#endif

        //@rev02
        if ( schemaElement ) {
	        if (fValidate) {
	            //  validate the Schema scan so far
	            fValidator->setGrammar(grammar);
	            fValidator->preContentValidation(false, true);
	        }
	
	        if (toCache) {
	            fGrammarResolver->cacheGrammars();
	        }
	
	        if(getPSVIHandler())
	            fModel = fGrammarResolver->getXSModel();
	            
        }

        return grammar;
	} catch (...) {
        return 0;
	}
}

Grammar*  WsdlXMLScanner::afterLoadGrammar(Grammar* grammar, bool toCache) 
{
    try {
	
        if (fValidate) {
            //  validate the Schema scan so far
            fValidator->setGrammar(grammar);
            fValidator->preContentValidation(false, true);
        }

        if (toCache) {
            fGrammarResolver->cacheGrammars();
        }

        if(getPSVIHandler())
            fModel = fGrammarResolver->getXSModel();

        return grammar;
	} catch (...) {
        return 0;
	}
}

//@rev02
void WsdlXMLScanner::traverseExtElementList(ExtensibilityElement::ListPtr extElements) 
{
#ifdef WSDL_USE_CURL
    wsdl::QName::PtrSet::iterator itEnd = (SchemaConstants::XSD_QNAME_LIST)->end();
    ExtensibilityElement::List::iterator i,l;
    for(i = extElements->begin(), l = extElements->end();
        i != l; i++)
    {
        if ( (SchemaConstants::XSD_QNAME_LIST)->find(i->get()->getElementType()) != itEnd )
        {
        	ExtensibilityElementPtr eePtr;
        	eePtr = *(i);
            SchemaPtr schema = eePtr.downcastTo<Schema>();
#ifdef _DEBUG
			XMLChString xs = schema->getDocumentBaseURI();
            cout << "WsdlXMLScanner::scanExtElementList(): " << xs.toLocal() << endl;
#endif
            getTraverseSchema()->preprocessOnlineSchema(schema->getElement(),
                schema->getDocumentBaseURI());
                
        }
    }
    
    for(i = extElements->begin(), l = extElements->end();
        i != l; i++)
    {
        if ( (SchemaConstants::XSD_QNAME_LIST)->find(i->get()->getElementType()) != itEnd )
        {
        	ExtensibilityElementPtr eePtr;
        	eePtr = *(i);
            SchemaPtr schema = eePtr.downcastTo<Schema>();
            getTraverseSchema()->traverseOnlineSchema(schema->getElement());
        }
    }
#endif
}

void WsdlXMLScanner::scanExtElementList(ExtensibilityElement::ListPtr extElements) 
{
	Grammar* grammar;
#ifdef WSDL_USE_CURL
    grammar = loadGrammar(0, 0, true);
    traverseExtElementList(extElements);
	afterLoadGrammar(grammar, true);
#else
	SchemaPtr schema = (SchemaPtr)0;
    wsdl::QName::PtrSet::iterator itEnd = (SchemaConstants::XSD_QNAME_LIST)->end();
    ExtensibilityElement::List::iterator i,l;
    for(i = extElements->begin(), l = extElements->end();
        i != l; i++)
    {
        if ( (SchemaConstants::XSD_QNAME_LIST)->find(i->get()->getElementType()) != itEnd )
        {
        	ExtensibilityElementPtr eePtr;
        	eePtr = *(i);
            schema = eePtr.downcastTo<Schema>();
			break;
        }
    }
	if ( schema )
	{
		grammar = loadGrammar(schema->getDocumentBaseURI(), schema->getElement(), true);
		afterLoadGrammar(grammar, true);
	}
#endif
}

WSDL_NAMESPACE_END
