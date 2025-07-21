/*
 * %fv:UnknownExtensionDeserializer.hpp-4 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
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
