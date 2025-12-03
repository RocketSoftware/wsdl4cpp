/*
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
 * 
 * History:
 * 
 * revision  date    refnum    version  who  description
 * --------------------------------------------------------------------------
 * 01        060713            9.SOAP   mzu  Migrated from WSDL4J
 * 02        060713  t85128    9.SOAP   mzu  Change for xml schema cross-reference
 * --------------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 */
#ifndef SCHEMA_HPP_
#define SCHEMA_HPP_
#include <list>
#include <map>
#include <xercesc/dom/DOMElement.hpp>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/QName.hpp"
#include "wsdl/ext/ExtensibilityElement.hpp"
#include "wsdl/schema/SchemaConstants.hpp"
#include "wsdl/schema/SchemaModel.hpp"

WSDL_NAMESPACE_BEGIN

class Schema;

DEFINE_PTR(Schema);

class WSDL_EXPORT Schema 
    : public ExtensibilityElement
{
public:
    static QNamePtr DEFAULT_ELEM_TYPE;
    
    typedef std::map<XMLChString, SchemaPtr, lessXMLCh> Map;
    DEFINE_PTR(Map);
    
    static const XMLCh PREFIX[];
    static const XMLCh PREFIX_SEPARATOR[];
    
    Schema(QNamePtr elementType, bool b = false);
    
    Schema();
    
    virtual ~Schema();

    virtual const XMLCh * getDocumentBaseURI() const { return documentBaseURI.c_str(); }
    virtual void setDocumentBaseURI(XMLChString uri){documentBaseURI = uri;}
    
	virtual XMLChString toString();
    
  /**
   * Set the DOM Element that represents this schema element.
   *
   * @param element the DOM element representing this schema
   */
    virtual void setElement(XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* element){ this->element = element; }

  /**
   * Get the DOM Element that represents this schema element.
   *
   * @return the DOM element representing this schema
   */
    virtual XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* getElement(){ return element; }

protected:
   XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* element;
    
private:

    XMLChString documentBaseURI;

    virtual XMLChString getTagName() { return SchemaConstants::ELEM_SCHEMA; }
	
};

WSDL_NAMESPACE_END

#endif /*SCHEMA_HPP_*/
