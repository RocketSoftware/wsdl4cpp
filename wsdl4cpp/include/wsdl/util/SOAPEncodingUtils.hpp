/*
 * %fv:SOAPEncodingUtils.hpp-4 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
 */

#ifndef SOAPENCODINGUTILS_HPP_
#define SOAPENCODINGUTILS_HPP_
#include <xercesc/util/XercesDefs.hpp>
//#include <xercesc/dom/DOMBuilder.hpp>
#include <xercesc/dom/DOMElement.hpp>

#include "wsdl/wsdlbas.hpp"
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/QName.hpp"
#include "wsdl/WSDLException.hpp"
#include "wsdl/schema/SchemaXercesc.hpp"

WSDL_NAMESPACE_BEGIN

/**
 * This utility class provides several helper methods for accessing
 * SOAP encoding array type.
 */
class WSDL_EXPORT SOAPEncodingUtils
{
	
public:
    static const XMLCh NS_URI_ENCODING[];
    static const XMLCh DEFAULT_ENCODING_LOCATION[];
    static const XMLCh TYPE_ARRAY[];
    static const XMLCh ARRAY_SURFIX[];

	SOAPEncodingUtils(){};
	virtual ~SOAPEncodingUtils(){};
	
    /**
     * Add the import element for soap-encoding to the specified schema element.
     * @param schemaElement the schema DOM element;
     * @param def the definitions of WSDL document.
     */
    static void addImport(XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* schemaElement, DefinitionsPtr def);
        
    /**
     * Returns the wsdl:arrayType attribute if specified type is a SOAP-encoding array type;
     *     or returns a nil pointer if not; or throws WSDLException if there is syntax error in the 
     *     description of the specified type.
     * @param typeQName the qualified name of the type;
     * @param def the definitions of WSDL document.
     * @return the wsdl:arrayType attribute if specified type is a SOAP-encoding array type;
     *     or a nil pointer if not.
     * @exception WSDLException if there is syntax error in the description of the specified type. 
     */
    static QNamePtr getArrayTypeAttribute(QNamePtr typeQName, DefinitionsPtr def) throw (WSDLException);

    /**
     * Returns true if and only if specified type is a SOAP-encoding array type;
     *     or throws WSDLException if there is syntax error in the 
     *     description of the specified type.
     * @param typeQName the qualified name of the type;
     * @param def the definitions of WSDL document.
     * @return true if and only if specified type is a SOAP-encoding array type.
     * @exception WSDLException if there is syntax error in the description of the specified type. 
     */
    static bool isArrayType(
        QNamePtr typeQName,
        DefinitionsPtr def)
        throw (WSDLException);
    
    /**
     * Returns the default array type of the specified wsdl:arrayType attribute.
     * 
     * @param arrayTypeAttribute the specified wsdl:arrayType attribute;
     * @return the default array type.
     */
    static QNamePtr getArrayType(QNamePtr arrayTypeAttribute);
    
    /**
     * Returns the rank of the specified wsdl:arrayType attribute.
     * 
     * @param arrayTypeAttribute the specified wsdl:arrayType attribute;
     * @return the rank.
     */
    static XMLChString getRank(QNamePtr arrayTypeAttribute);
    
private:
    static QNamePtr getArrayTypeAttr(const XMLCh* annotationString, 
        XERCES_CPP_NAMESPACE_QUALIFIER MemoryManager* memManager, DefinitionsPtr def)
        throw (WSDLException);
        
};

WSDL_NAMESPACE_END

#endif /*SOAPENCODINGUTILS_HPP_*/
