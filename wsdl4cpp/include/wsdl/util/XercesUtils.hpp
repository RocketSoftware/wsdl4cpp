/*
 * %fv:XercesUtils.hpp-8 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * 
 * History:
 * 
 * revision  date    refnum    version  who  description
 * --------------------------------------------------------------------------
 * 01        060713            9.SOAP   mzu  First draft
 * 02        060713  t85128    9.SOAP   mzu  Change for xml schema cross-reference
 * 03        070223  c25551    9.2.01   mzu  Adding InputSourceEnv for integrating 
 *                                           with libcurl
 * --------------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 */
#ifndef XERCESUTILS_HPP_
#define XERCESUTILS_HPP_
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/DOMBuilder.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/framework/XMLValidator.hpp>
#include <xercesc/framework/XMLGrammarPool.hpp>
#include <xercesc/framework/psvi/XSModel.hpp>
#include <xercesc/internal/SGXMLScanner.hpp>
#include <xercesc/validators/schema/TraverseSchema.hpp>
#include <xercesc/sax/InputSource.hpp>

#include "wsdl/wsdlbas.hpp"
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/InputSourceEnv.hpp"
#include "wsdl/ext/ExtensibilityElement.hpp"

//class XERCES_CPP_NAMESPACE_QUALIFIER InputSource;

WSDL_NAMESPACE_BEGIN

/**
 * This utility class provides some helper methods for accessing
 * the Xerces-C API.
 */
class WSDL_EXPORT XercesUtils
{
	
public:
	XercesUtils(){};
	virtual ~XercesUtils(){};
	
	static XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* getFirstChildElement (
            XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* elem);
    
    static XERCES_CPP_NAMESPACE_QUALIFIER DOMBuilder* 
        createDOMBuilder (XERCES_CPP_NAMESPACE_QUALIFIER XMLGrammarPool* const gramPool);
    
    // @rev03
    static XERCES_CPP_NAMESPACE_QUALIFIER InputSource* createInputSource(
    		const XMLCh* const        sysId
            , XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* const manager
            , const InputSourceEnvPtr ise = (InputSourceEnvPtr)0
            , const bool standardUriConformant = false);
            
};

/**
 * An extension of SGXMLScanner for direct scan of DOM tree.
 */
class WSDL_EXPORT WsdlXMLScanner : public XERCES_CPP_NAMESPACE_QUALIFIER SGXMLScanner
{
public :
    WsdlXMLScanner(XERCES_CPP_NAMESPACE_QUALIFIER XMLValidator* const valToAdopt
                          , XERCES_CPP_NAMESPACE_QUALIFIER GrammarResolver* const grammarResolver
                          , XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* const manager);
                          
    ~WsdlXMLScanner(); //@rev02
    
    void scanExtElementList(ExtensibilityElement::ListPtr extElements);
          
    //@rev02 begin
    XERCES_CPP_NAMESPACE_QUALIFIER TraverseSchema* getTraverseSchema();
    XERCES_CPP_NAMESPACE_QUALIFIER TraverseSchema* traverseSchema;
    //@rev02 end

    /**
     * Returns the input source environment.
     * @return the input source environment.
     */
	InputSourceEnvPtr getInputSourceEnv() const { return isePtr; }

    /**
     * Set the input source environment.
     * @param ptr the input source environment.
     */
	void setInputSourceEnv(const InputSourceEnvPtr ptr) { isePtr = ptr;}

    /**
     * Returns true if and only if the implementation use libcurl.
     * @return true if and only if the implementation use libcurl.
     */
	bool getUsingCURL() const { return usingCURL; }

    /**
     * Set true for libcurl using, and set false for default xerces implementation.
     * @param b the bool value specified.
     */
	void setUsingCURL(bool b) { usingCURL = b; }

protected:
	InputSourceEnvPtr isePtr;
	bool usingCURL;

    XERCES_CPP_NAMESPACE_QUALIFIER Grammar* loadGrammar(
        const XMLCh* systemId, 
        XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* schemaElement, 
        bool toCache);
        
    XERCES_CPP_NAMESPACE_QUALIFIER Grammar*  afterLoadGrammar(
        XERCES_CPP_NAMESPACE_QUALIFIER  Grammar* grammar, bool toCache);
    
    void traverseExtElementList(ExtensibilityElement::ListPtr extElements);
};

WSDL_NAMESPACE_END

#endif /*XERCESUTILS_HPP_*/
