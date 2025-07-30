/*
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
 */
#ifndef SOAPHEADERSERIALIZER_HPP_
#define SOAPHEADERSERIALIZER_HPP_
#include <xercesc/dom/DOMElement.hpp>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/ext/ExtensibilityElement.hpp"
#include "wsdl/ext/ExtensionRegistry.hpp"
#include "wsdl/Definitions.hpp"
#include "wsdl/QName.hpp"

WSDL_NAMESPACE_BEGIN

class SOAPHeaderSerializer;

DEFINE_PTR(SOAPHeaderSerializer);

class WSDL_EXPORT SOAPHeaderSerializer : public ExtensionDeserializer
{
public:
	SOAPHeaderSerializer();
	virtual ~SOAPHeaderSerializer();
    
    virtual ExtensibilityElementPtr unmarshall(
        QNamePtr parentType, QNamePtr elementType, 
        XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el, 
        DefinitionsPtr def, 
        ExtensionRegistryPtr extReg) throw (WSDLException);
        
protected:
    virtual SOAPHeaderFaultPtr parseSoapHeaderFault(
        QNamePtr parentType,
        QNamePtr elementType,
        XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el, 
        ExtensionRegistryPtr extReg, 
        DefinitionsPtr def)
        throw (WSDLException);
    
};

WSDL_NAMESPACE_END

#endif /*SOAPHEADERSERIALIZER_HPP_*/
