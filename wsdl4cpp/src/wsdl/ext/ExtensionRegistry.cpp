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
 * -----------------------------------------------------------------------
 * 01-04     060509            9.SOAP   mzu  Migrated from WSDL4J
 * 05        070109  t85163    9.SOAP   mzu  Add constants for attribute extentions
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 */

#include "wsdl/wsdlxerces.hpp"
#include "wsdl/ext/ExtensionRegistry.hpp"

#include <iostream>
#include <xercesc/util/XMLUniDefs.hpp>
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/Constants.hpp"
#include "wsdl/ext/AttributeExtensible.hpp"
#include "wsdl/ext/UnknownExtensionDeserializer.hpp"
#include "wsdl/soap/SOAPAddress.hpp"
#include "wsdl/soap/SOAPAddressSerializer.hpp"
#include "wsdl/soap/SOAPBinding.hpp"
#include "wsdl/soap/SOAPBindingSerializer.hpp"
#include "wsdl/soap/SOAPBody.hpp"
#include "wsdl/soap/SOAPBodySerializer.hpp"
#include "wsdl/soap/SOAPFault.hpp"
#include "wsdl/soap/SOAPFaultSerializer.hpp"
#include "wsdl/soap/SOAPHeader.hpp"
#include "wsdl/soap/SOAPHeaderFault.hpp"
#include "wsdl/soap/SOAPHeaderSerializer.hpp"
#include "wsdl/soap/SOAPOperation.hpp"
#include "wsdl/soap/SOAPOperationSerializer.hpp"
#include "wsdl/soap/SOAPConstants.hpp"
#include "wsdl/schema/Schema.hpp"
#include "wsdl/schema/SchemaConstants.hpp"
#include "wsdl/schema/SchemaDeserializer.hpp"

USING_STD

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

ExtensionRegistry::ExtensionRegistry()
    : deserializerReg(new ExtensionDeserializer::MapValueMap())
    , extensionTypeReg(new ExtTypeMap())
    , extensionAttributeTypeReg(new ExtTypeMap()) // rev05
    , defaultDeser(new UnknownExtensionDeserializer())
{
    ExtensionDeserializerPtr soapAddressSer(new SOAPAddressSerializer());
    //SOAPAddressSerializerPtr soapAddressSer(new SOAPAddressSerializer());

//    registerSerializer(Constants::Q_ELEM_PORT,
//                       SOAPConstants::Q_ELEM_SOAP_ADDRESS,
//                       soapAddressSer);
    registerDeserializer(Constants::Q_ELEM_PORT,
                         SOAPConstants::Q_ELEM_SOAP_ADDRESS,
                         soapAddressSer);
    mapExtensionTypes(Constants::Q_ELEM_PORT,
                      SOAPConstants::Q_ELEM_SOAP_ADDRESS,
                      ETYPE_ADDRESS);

    ExtensionDeserializerPtr soapBindingSer(new SOAPBindingSerializer());
    //SOAPBindingSerializer soapBindingSer = new SOAPBindingSerializer();

//    registerSerializer(Binding.class,
//                       SOAPConstants::Q_ELEM_SOAP_BINDING,
//                       soapBindingSer);
    registerDeserializer(Constants::Q_ELEM_BINDING,
                         SOAPConstants::Q_ELEM_SOAP_BINDING,
                         soapBindingSer);
    mapExtensionTypes(Constants::Q_ELEM_BINDING,
                      SOAPConstants::Q_ELEM_SOAP_BINDING,
                      ETYPE_BINDING);

    ExtensionDeserializerPtr soapHeaderSer(new SOAPHeaderSerializer());

//    registerSerializer(Constants::Q_ELEM_INPUT,
//                       SOAPConstants.Q_ELEM_SOAP_HEADER,
//                       soapHeaderSer);
    registerDeserializer(Constants::Q_ELEM_INPUT,
                         SOAPConstants::Q_ELEM_SOAP_HEADER,
                         soapHeaderSer);
    mapExtensionTypes(Constants::Q_ELEM_INPUT,
                      SOAPConstants::Q_ELEM_SOAP_HEADER,
                      ETYPE_HEADER);
                      
//    registerSerializer(Constants::Q_ELEM_OUTPUT,
//                       SOAPConstants::Q_ELEM_SOAP_HEADER,
//                       soapHeaderSer);
    registerDeserializer(Constants::Q_ELEM_OUTPUT,
                         SOAPConstants::Q_ELEM_SOAP_HEADER,
                         soapHeaderSer);
    mapExtensionTypes(Constants::Q_ELEM_OUTPUT,
                      SOAPConstants::Q_ELEM_SOAP_HEADER,
                      ETYPE_HEADER);
    mapExtensionTypes(SOAPConstants::Q_ELEM_SOAP_HEADER,
                      SOAPConstants::Q_ELEM_SOAP_HEADER_FAULT,
                      ETYPE_HEADER_FAULT);

    ExtensionDeserializerPtr soapBodySer(new SOAPBodySerializer());
    //SOAPBodySerializer soapBodySer = new SOAPBodySerializer();

//    registerSerializer(Constants::Q_ELEM_INPUT,
//                       SOAPConstants::Q_ELEM_SOAP_BODY,
//                       soapBodySer);
    registerDeserializer(Constants::Q_ELEM_INPUT,
                         SOAPConstants::Q_ELEM_SOAP_BODY,
                         soapBodySer);
    mapExtensionTypes(Constants::Q_ELEM_INPUT,
                      SOAPConstants::Q_ELEM_SOAP_BODY,
                      ETYPE_BODY);
                      
//    registerSerializer(Constants::Q_ELEM_OUTPUT,
//                       SOAPConstants::Q_ELEM_SOAP_BODY,
//                       soapBodySer);
    registerDeserializer(Constants::Q_ELEM_OUTPUT,
                         SOAPConstants::Q_ELEM_SOAP_BODY,
                         soapBodySer);
    mapExtensionTypes(Constants::Q_ELEM_OUTPUT,
                      SOAPConstants::Q_ELEM_SOAP_BODY,
                      ETYPE_BODY);
                      
    ExtensionDeserializerPtr soapFaultSer(new SOAPFaultSerializer());

//    registerSerializer(Constants::Q_ELEM_FAULT,
//                       SOAPConstants::Q_ELEM_SOAP_FAULT,
//                       soapFaultSer);
    registerDeserializer(Constants::Q_ELEM_FAULT,
                         SOAPConstants::Q_ELEM_SOAP_FAULT,
                         soapFaultSer);
    mapExtensionTypes(Constants::Q_ELEM_FAULT,
                      SOAPConstants::Q_ELEM_SOAP_FAULT,
                      ETYPE_FAULT);

//    registerSerializer(MIMEPart.class,
//                       SOAPConstants::Q_ELEM_SOAP_BODY,
//                       soapBodySer);
//    registerDeserializer(MIMEPart.class,
//                         SOAPConstants::Q_ELEM_SOAP_BODY,
//                         soapBodySer);
//    mapExtensionTypes(MIMEPart.class,
//                      SOAPConstants::Q_ELEM_SOAP_BODY,
//                      ETYPE_BODY);

    ExtensionDeserializerPtr soapOperationSer(new SOAPOperationSerializer());
    //SOAPOperationSerializer soapOperationSer = new SOAPOperationSerializer();

//    registerSerializer(BindingOperation.class,
//                       SOAPConstants::Q_ELEM_SOAP_OPERATION,
//                       soapOperationSer);
    registerDeserializer(Constants::Q_ELEM_OPERATION,
                         SOAPConstants::Q_ELEM_SOAP_OPERATION,
                         soapOperationSer);
    mapExtensionTypes(Constants::Q_ELEM_OPERATION,
                      SOAPConstants::Q_ELEM_SOAP_OPERATION,
                      ETYPE_OPERATION);

    //Register the schema parser
    
    ExtensionDeserializerPtr schemaDeser(new SchemaDeserializer());
    //ExtensionDeserializerPtr schemaSer(new SchemaSerializer());
    
    mapExtensionTypes(Constants::Q_ELEM_TYPES, SchemaConstants::Q_ELEM_XSD_1999,
        ETYPE_SCHEMA);
    registerDeserializer(Constants::Q_ELEM_TYPES, SchemaConstants::Q_ELEM_XSD_1999,
        schemaDeser);
//    registerSerializer(Constants::Q_ELEM_TYPES, SchemaConstants::Q_ELEM_XSD_1999,
//        schemaSer);

    mapExtensionTypes(Constants::Q_ELEM_TYPES, SchemaConstants::Q_ELEM_XSD_2000,
        ETYPE_SCHEMA);
    registerDeserializer(Constants::Q_ELEM_TYPES, SchemaConstants::Q_ELEM_XSD_2000,
        schemaDeser);
//    registerSerializer(Constants::Q_ELEM_TYPES, SchemaConstants::Q_ELEM_XSD_2000,
//        schemaSer);

    mapExtensionTypes(Constants::Q_ELEM_TYPES, SchemaConstants::Q_ELEM_XSD_2001,
        ETYPE_SCHEMA);
    registerDeserializer(Constants::Q_ELEM_TYPES, SchemaConstants::Q_ELEM_XSD_2001,
        schemaDeser);
//    registerSerializer(Constants::Q_ELEM_TYPES, SchemaConstants::Q_ELEM_XSD_2001,
//        schemaSer);

}

ExtensionRegistry::~ExtensionRegistry()
{
}

void ExtensionRegistry::mapExtensionTypes(QNamePtr parentType,
                                QNamePtr elementType,
                                EXTENSION_TYPE extensionType)
{
    ExtTypeMap::iterator innerExtensionTypeReg = extensionTypeReg->find(parentType);

    ExtTypeInnerMapPtr innerMap;
    if (innerExtensionTypeReg == extensionTypeReg->end() )
    {
        innerMap = (ExtTypeInnerMapPtr)new ExtTypeInnerMap();

        extensionTypeReg->insert(ExtTypeMap::value_type(parentType, innerMap));
    }
    else
    {
        innerMap = innerExtensionTypeReg->second;
    }

    innerMap->insert(ExtTypeInnerMap::value_type(elementType, extensionType));
         
}

ExtensibilityElementPtr ExtensionRegistry::createExtension(
    QNamePtr parentType, QNamePtr elementType) throw(WSDLException)
{
    ExtTypeMap::iterator innerExtensionTypeReg = extensionTypeReg->find(parentType);
    int extensionType = ETYPE_NONE; //rev05

    if (innerExtensionTypeReg != extensionTypeReg->end() )
    {
        ExtTypeInnerMapPtr pInnerMap = innerExtensionTypeReg->second;
        ExtTypeInnerMap::iterator edIt = pInnerMap->find(elementType);
        if (edIt != pInnerMap->end())
        {
            extensionType = edIt->second;
        }
    }

    if (extensionType == ETYPE_NONE)
    {
      throw WSDLException(WSDLException::CONFIGURATION_ERROR,
                              string("No Java extensionType found to represent a '")
                              .append(toLocal(elementType->toString()))
                              .append("' element in the context of a '")
                              .append(toLocal(parentType->toString()))
                              .append("'."));
    }
//    else if (!(ExtensibilityElement.class.isAssignableFrom(extensionType)))
//    {
//      throw new WSDLException(WSDLException.CONFIGURATION_ERROR,
//                              "The Java extensionType '" +
//                              extensionType.getName() + "' does " +
//                              "not implement the ExtensibilityElement " +
//                              "interface.");
//    }

    ExtensibilityElementPtr ee;
    switch (extensionType) {
    case ETYPE_ADDRESS:
        ee = (ExtensibilityElementPtr)new SOAPAddress();
        break;
    case ETYPE_BINDING:
        ee = (ExtensibilityElementPtr)new SOAPBinding();
        break;
    case ETYPE_BODY:
        ee = (ExtensibilityElementPtr)new SOAPBody();
        break;
    case ETYPE_FAULT:
        ee = (ExtensibilityElementPtr)new SOAPFault();
        break;
    case ETYPE_HEADER:
        ee = (ExtensibilityElementPtr)new SOAPHeader();
        break;
    case ETYPE_HEADER_FAULT:
        ee = (ExtensibilityElementPtr)new SOAPHeaderFault();
        break;
    case ETYPE_OPERATION:
        ee = (ExtensibilityElementPtr)new SOAPOperation();
        break;
    case ETYPE_SCHEMA:
        ee = (ExtensibilityElementPtr)new Schema();
        break;
    default: 
        throw WSDLException(WSDLException::CONFIGURATION_ERROR,
                  string("The Java extensionType '")
                  .append(toLocal(elementType->toString()))
                  .append("' does not implement the ExtensibilityElement interface."));
    }
    
    if ( !(ee->getElementType()) )
    {
        ee->setElementType(elementType);
    }
  
    return ee;
}

ExtensionDeserializerPtr ExtensionRegistry::queryDeserializer(
        QNamePtr parentType, QNamePtr elementType)
    throw (WSDLException)
{
    ExtensionDeserializer::MapValueMap::iterator innerDeserializerReg = 
        deserializerReg->find(parentType);
        
    ExtensionDeserializerPtr ed;

    if (innerDeserializerReg != deserializerReg->end())
    {
        ExtensionDeserializer::MapPtr pInnerMap = innerDeserializerReg->second;
        ExtensionDeserializer::Map::iterator edIt = pInnerMap->find(elementType);
        if (edIt != pInnerMap->end())
        {
            ed = edIt->second;
        }
    }

    if (!ed)
    {
        ed = defaultDeser;
    }

    if (!ed)
    {
       throw WSDLException(WSDLException::CONFIGURATION_ERROR,
                string("No ExtensionDeserializer found to deserialize a '")
                    .append(toLocal(elementType->toString()))
                    .append("' element in the context of a '")
                    .append(toLocal(parentType->toString()))
                    .append("'."));
    }

    return ed;
}
        
void ExtensionRegistry::registerDeserializer(
        QNamePtr parentType, QNamePtr elementType,
        ExtensionDeserializerPtr ed)
{
    ExtensionDeserializer::MapValueMap::iterator innerDeserializerReg = 
        deserializerReg->find(parentType);

    ExtensionDeserializer::MapPtr innerMap;
    if (innerDeserializerReg == deserializerReg->end())
    {
        innerMap = (ExtensionDeserializer::MapPtr)new ExtensionDeserializer::Map();

        deserializerReg->insert(ExtensionDeserializer::MapValueMap::value_type(parentType, innerMap));
    }
    else
    {
        innerMap = innerDeserializerReg->second;
    }

    innerMap->insert(ExtensionDeserializer::Map::value_type(elementType, ed));
}

  /**
   * Declare that the type of the specified extension attribute, when it occurs
   * as an attribute of the specified parent type, should be assumed to be
   * attrType.
   *
   * @param parentType a class object indicating where in the WSDL
   * document this extensibility attribute was encountered. For
   * example, javax.wsdl.Binding.class would be used to indicate
   * this attribute was defined on a &lt;wsdl:binding> element.
   * @param attrName the qname of the extensibility attribute
   * @param attrType one of the constants defined on the AttributeExtensible
   * class
   *
   * @see #queryExtensionAttributeType(Class, QName)
   * @see AttributeExtensible
   * @since rev05
   */
void ExtensionRegistry::registerExtensionAttributeType(QNamePtr parentType,
                                             QNamePtr attrName,
                                             int attrType)
{
    ExtTypeMap::iterator innerExtensionAttributeTypeReg = extensionAttributeTypeReg->find(parentType);
    
    ExtTypeInnerMapPtr innerMap;
    if (innerExtensionAttributeTypeReg == extensionAttributeTypeReg->end() )
    {
        innerMap = (ExtTypeInnerMapPtr)new ExtTypeInnerMap();

        extensionAttributeTypeReg->insert(ExtTypeMap::value_type(parentType, innerMap));
    }
    else
    {
        innerMap = innerExtensionAttributeTypeReg->second;
    }

    innerMap->insert(ExtTypeInnerMap::value_type(attrName, attrType));

}

int ExtensionRegistry::queryExtensionAttributeType(QNamePtr parentType, QNamePtr attrName)
{
    ExtTypeMap::iterator innerExtensionAttributeTypeReg = extensionAttributeTypeReg->find(parentType);
    
    int attrType = ExtensibilityAttribute::NO_DECLARED_TYPE;

    if (innerExtensionAttributeTypeReg != extensionAttributeTypeReg->end())
    {
      //attrType = innerExtensionAttributeTypeReg->find(attrName);
        ExtTypeInnerMapPtr pInnerMap = innerExtensionAttributeTypeReg->second;
        ExtTypeInnerMap::iterator edIt = pInnerMap->find(attrName);
        if (edIt != pInnerMap->end())
        {
            attrType = edIt->second;
        }
    }
    
    return attrType;

}

WSDL_NAMESPACE_END

