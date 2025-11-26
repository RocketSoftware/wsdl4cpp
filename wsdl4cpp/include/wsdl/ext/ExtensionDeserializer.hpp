/*
 * %fv:ExtensionDeserializer.hpp-4 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
 */
#ifndef EXTENSIONDESERIALIZER_HPP_
#define EXTENSIONDESERIALIZER_HPP_
#include <map>
#include <xercesc/dom/DOMElement.hpp>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/ext/ExtensibilityElement.hpp"
#include "wsdl/ext/ExtensionRegistry.hpp"
#include "wsdl/Definitions.hpp"
#include "wsdl/QName.hpp"

WSDL_NAMESPACE_BEGIN

class WSDL_EXPORT ExtensionDeserializer
{
public:
    typedef std::map<QNamePtr, ExtensionDeserializerPtr, lessQNamePtr> Map;
    DEFINE_PTR(Map);
    typedef std::map<QNamePtr, MapPtr, lessQNamePtr> MapValueMap;
    DEFINE_PTR(MapValueMap);
    
    virtual ExtensibilityElementPtr unmarshall(
        QNamePtr parentType, QNamePtr elementType, 
        XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* el, 
        DefinitionsPtr def, 
        ExtensionRegistryPtr extReg) throw (WSDLException) = 0;
	
};

WSDL_NAMESPACE_END

#endif /*EXTENSIONDESERIALIZER_HPP_*/
