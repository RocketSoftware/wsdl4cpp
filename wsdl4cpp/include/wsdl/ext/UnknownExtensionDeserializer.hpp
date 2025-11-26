/*
 * %fv:UnknownExtensionDeserializer.hpp-4 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
 */
#ifndef UNKNOWNEXTENSIONDESERIALIZER_HPP_
#define UNKNOWNEXTENSIONDESERIALIZER_HPP_
#include <xercesc/dom/DOMElement.hpp>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/ext/ExtensionDeserializer.hpp"
#include "wsdl/ext/ExtensionRegistry.hpp"
#include "wsdl/Definitions.hpp"
#include "wsdl/QName.hpp"

WSDL_NAMESPACE_BEGIN

class UnknownExtensionDeserializer;

DEFINE_PTR(UnknownExtensionDeserializer);

class WSDL_EXPORT UnknownExtensionDeserializer : public ExtensionDeserializer
{
public:
	UnknownExtensionDeserializer();
	virtual ~UnknownExtensionDeserializer();
    
    virtual ExtensibilityElementPtr unmarshall(
        QNamePtr parentType, QNamePtr elementType, 
        XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el, 
        DefinitionsPtr def, 
        ExtensionRegistryPtr extReg) throw (WSDLException);
	
protected:
};

WSDL_NAMESPACE_END

#endif /*UNKNOWNEXTENSIONDESERIALIZER_HPP_*/
