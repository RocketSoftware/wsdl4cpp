/*
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
070202 c25507    9.SOAP  ahn direct import of soapencoding.xsd
120907 b29663    E110    ahn better error reporting
date   refnum    version who description
*******************************************************************************/
#include "wsdl/wsdlxerces.hpp"

#include <iostream>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/framework/psvi/XSAnnotation.hpp>
#include <xercesc/framework/psvi/XSAttributeDeclaration.hpp>
#include <xercesc/framework/psvi/XSAttributeUse.hpp>
#include <xercesc/framework/psvi/XSComplexTypeDefinition.hpp>
#include <xercesc/framework/psvi/XSParticle.hpp>
#include <xercesc/framework/psvi/XSModelGroup.hpp>
#include <xercesc/framework/psvi/XSElementDeclaration.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>

#include "wsdl/Constants.hpp"
#include "wsdl/schema/SchemaConstants.hpp"
#include "wsdl/util/ArrayTypeInfo.hpp"
#include "wsdl/util/DOMUtils.hpp"
#include "wsdl/util/SOAPEncodingUtils.hpp"

USING_STD

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

//"http://schemas.xmlsoap.org/soap/encoding/"
const XMLCh SOAPEncodingUtils::NS_URI_ENCODING[] = { 
    chLatin_h, chLatin_t, chLatin_t, chLatin_p, 
    chColon, chForwardSlash, chForwardSlash, 
    chLatin_s, chLatin_c, chLatin_h, chLatin_e, chLatin_m, chLatin_a, chLatin_s, 
    chPeriod, chLatin_x, chLatin_m, chLatin_l, chLatin_s, chLatin_o, chLatin_a, chLatin_p, 
    chPeriod, chLatin_o, chLatin_r, chLatin_g, chForwardSlash, 
    chLatin_s, chLatin_o, chLatin_a, chLatin_p, chForwardSlash, 
    chLatin_e, chLatin_n, chLatin_c, chLatin_o, chLatin_d, chLatin_i, chLatin_n, chLatin_g, chForwardSlash, 
    chNull };

const XMLCh SOAPEncodingUtils::TYPE_ARRAY[] = { 
    //"Array"
    chLatin_A, chLatin_r, chLatin_r, chLatin_a, chLatin_y, chNull };

// soapencoding.xsd
const XMLCh SOAPEncodingUtils::DEFAULT_ENCODING_LOCATION[] = { 
    chLatin_s, chLatin_o, chLatin_a, chLatin_p, 
    chLatin_e, chLatin_n, chLatin_c, chLatin_o, chLatin_d, chLatin_i, chLatin_n, chLatin_g, 
    chPeriod, chLatin_x, chLatin_s, chLatin_d, 
    chNull };

const XMLCh SOAPEncodingUtils::ARRAY_SURFIX[] = { 
    //"[]"
    chOpenSquare, chCloseSquare, chNull };

void SOAPEncodingUtils::addImport(
        DOMElement* schemaElement, DefinitionsPtr def) 
{
    DOMDocument* doc = schemaElement->getOwnerDocument();
    
    // Add import for soap-encoding
    DOMNamedNodeMap* saMap = schemaElement->getAttributes();
    bool shouldImportSoapEncoding = false;
    for (int i=0, l=saMap->getLength(); i<l; i++) {
        DOMNode* node = saMap->item(i);
        if ( XMLString::compareString(NS_URI_ENCODING, node->getNodeValue()) == 0 ){
            shouldImportSoapEncoding = true;
            break;
        }
    }

    const XMLCh* nsURI = schemaElement->getNamespaceURI();
    if ( shouldImportSoapEncoding ) {
        DOMNodeList* importList = schemaElement->getElementsByTagNameNS(nsURI, Constants::ELEM_IMPORT);
        for (int i=0, l=importList->getLength(); i<l; i++)
        {
            DOMElement* import = (DOMElement*)importList->item(i);
            const XMLCh* ns = import->getAttribute(Constants::ATTR_NAMESPACE);
            //const XMLCh* loc = import->getAttribute(SchemaConstants::ATTR_SCHEMA_LOCATION);
            if ( XMLString::equals(ns, NS_URI_ENCODING) )
            {
                shouldImportSoapEncoding = false;
                break;
            }
        }
    }
    if ( shouldImportSoapEncoding ) {
        // @b29663 dummy import gets line = 0 and col = 0
        DOMElement* importElement = doc->createElementNS(nsURI, Constants::ELEM_IMPORT, 0, 0);
//          importElement.setAttributeNS(nsURI, "namespace", SOAP_ENCODING_URI);
//          importElement.setAttributeNS(nsURI, "schemaLocation", SOAP_ENCODING_URI);

//        importElement->setAttribute(Constants::ATTR_NAMESPACE, NS_URI_ENCODING);
          importElement->setAttributeNS((const XMLCh *)0, Constants::ATTR_NAMESPACE, NS_URI_ENCODING);

        //importElement->setAttribute(SchemaConstants::ATTR_SCHEMA_LOCATION, SOAPConstants::NS_URI_ENCODING);
        // @c25507 removed forward slash, dir spec should be complete
        XMLChString uri = def->getSOAPEncBaseURI() + DEFAULT_ENCODING_LOCATION;
//        importElement->setAttribute(
//            SchemaConstants::ATTR_SCHEMA_LOCATION, uri.c_str());
        importElement->setAttributeNS((const XMLCh *)0, SchemaConstants::ATTR_SCHEMA_LOCATION, uri.c_str());
  
        DOMNode* fChild = schemaElement->getFirstChild();
        schemaElement->insertBefore(importElement, fChild);
    }

}

QNamePtr SOAPEncodingUtils::getArrayTypeAttr(
    const XMLCh* annotationString, 
    MemoryManager* memManager, 
    DefinitionsPtr def)
    throw (WSDLException)
{
    QNamePtr qValue = wsdl::QName::Null;

    if ( !annotationString ) {
        return qValue;
    }
    
    XercesDOMParser *parser = new (memManager) XercesDOMParser(0, memManager);
    parser->setDoNamespaces(true);
    parser->setValidationScheme(XercesDOMParser::Val_Never);
    
    //DOMDocument* futureOwner = (targetType == W3C_DOM_ELEMENT) ?
    //    ((DOMElement*)node)->getOwnerDocument() :
    //    (DOMDocument*)node;

    MemBufInputSource* memBufIS = new (memManager) MemBufInputSource
    (
        (const XMLByte*)annotationString
        , XMLString::stringLen(annotationString)*sizeof(XMLCh)
        , ""
        , false
        , memManager
    );
    memBufIS->setEncoding(XMLUni::fgXMLChEncodingString);
    memBufIS->setCopyBufToStream(false);
    
    try
    {        
        parser->parse(*memBufIS);  // throw XMLException

        if ( !(parser->getDocument()) )
            throw 1;
        DOMElement* el = (parser->getDocument())->getDocumentElement();
        if ( !el )
            throw 2;
        XMLChString prefixedValue = DOMUtils::getAttributeNS(el, Constants::NS_URI_WSDL, Constants::ATTR_ARRAYTYPE);
        if ( prefixedValue == null )
            throw 3;
        qValue = DOMUtils::getQName(prefixedValue, el, def);
        if ( !qValue )
            throw 4;
    
        XMLChString localName = qValue->getLocalPart();
        
        if ( localName == null || localName.length() == 0 )
            throw 5;
        

    }
    //catch (const XMLException&){}
    catch (...)
    {
        qValue = wsdl::QName::Null;
    }

    delete parser;
    delete memBufIS;

    return qValue;
}

bool SOAPEncodingUtils::isArrayType(
    QNamePtr typeQName,
    DefinitionsPtr def)
    throw (WSDLException)
{
    return (bool)(getArrayTypeAttribute(typeQName, def));
}

QNamePtr SOAPEncodingUtils::getArrayTypeAttribute(
    QNamePtr typeQName,
    DefinitionsPtr def)
    throw (WSDLException)
{
    ArrayTypeInfoPtr atInfo = def->getArrayTypeInfo(typeQName);
    if ( atInfo )
    {
        WSDLExceptionPtr ex = atInfo->getException();
        if ( ex )
        {
            throw WSDLException(ex->getFaultCode(), ex->getMessage());
        }
        else
        {
            return atInfo->getArrayTypeAttribute();
        }
    }
    
    atInfo = (ArrayTypeInfoPtr)new ArrayTypeInfo(typeQName);
    def->addArrayTypeInfo(atInfo);
    
    XSTypeDefinitionPtr typeDef = def->getType(typeQName);
    if ( !typeDef || typeDef->getTypeCategory() != XSTypeDefinition::COMPLEX_TYPE )
    {
        return atInfo->getArrayTypeAttribute();
    }
        
    XSComplexTypeDefinition* ctp = (XSComplexTypeDefinition*)(typeDef.getOwned());
    XSConstants::DERIVATION_TYPE dType = ctp->getDerivationMethod();
    XSTypeDefinition* baseType = ctp->getBaseType();
    QNamePtr baseTypeQName(new wsdl::QName(
        baseType->getNamespace(),
        baseType->getName()));

    if ( XMLString::compareString(NS_URI_ENCODING, baseType->getNamespace()) != 0 
        || XMLString::compareString(TYPE_ARRAY, baseType->getName()) != 0 
        || dType != XSConstants::DERIVATION_RESTRICTION )
    {
        return atInfo->getArrayTypeAttribute();
    }
    
    //cout << "\n  DriveMethod: " << dType << endl;

    try
    {
        XSAttributeUseList* list = ctp->getAttributeUses();
        for (int i=0, l= list->size(); i<l; i++)
        {
            XSAttributeUse* attrUse = list->elementAt(i);
            XSAttributeDeclaration *attrDecl = attrUse->getAttrDeclaration();
    
            XSAnnotation *annot = attrDecl->getAnnotation();
            if ( annot ) {
                QNamePtr arrayTypeQName = SOAPEncodingUtils::getArrayTypeAttr(annot->getAnnotationString(), XMLPlatformUtils::fgMemoryManager, def);
                //annot->writeAnnotation(handler);
                if ( arrayTypeQName )
                {
                    atInfo->setArrayTypeAttribute(arrayTypeQName);
                    break;
                }
            }
    
        }
    }
    catch (WSDLException& e)
    {
        atInfo->setException((WSDLExceptionPtr)new WSDLException(e.getFaultCode(), e.getMessage()));
    }

    return atInfo->getArrayTypeAttribute();
}

QNamePtr SOAPEncodingUtils::getArrayType(QNamePtr arrayTypeAttribute)
{
    QNamePtr arrayType;
    if ( !arrayTypeAttribute )
        return arrayType;
        
    XMLChString localPart = arrayTypeAttribute->getLocalPart();
    arrayType = (QNamePtr)new QName(arrayTypeAttribute->getNamespaceURI(), arrayTypeAttribute->getLocalPart());
    XMLChString::size_type i = localPart.find(chOpenSquare);
    
    if ( i != XMLChString::npos ) {
        arrayType->setLocalPart(localPart.substr(0, i));
    }
    
    return arrayType;
}

XMLChString SOAPEncodingUtils::getRank(QNamePtr arrayTypeAttribute)
{
    if ( !arrayTypeAttribute )
        return XMLChString::EMPTY_STRING;
        
    XMLChString localPart = arrayTypeAttribute->getLocalPart();
    XMLChString::size_type i = localPart.find(chOpenSquare);
    
    if ( i != XMLChString::npos ) {
        return localPart.substr(i, localPart.length() - i);
    }
    
    return XMLChString::EMPTY_STRING;
}

WSDL_NAMESPACE_END
