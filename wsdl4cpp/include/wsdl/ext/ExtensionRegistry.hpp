/*
 * %fv:ExtensionRegistry.hpp-6 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
/*
 * From release 1.0.0, WSDL4CPP is under the Eclipse Public License - v 2.0 (EPL 2.0)
 * 
 * History:
 * 
 * revision  date    refnum    version  who  description
 * -----------------------------------------------------------------------
 * 01-03                       9.SOAP   mzu  Migrated from WSDL4J
 * 04        070109  t85163    9.SOAP   mzu  Implementation for attribute extension
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 */
#ifndef EXTENSIONREGISTRY_HPP_
#define EXTENSIONREGISTRY_HPP_
#include <map>
#include <string>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/ext/ExtensionDeserializer.hpp"
#include "wsdl/QName.hpp"
#include "wsdl/WSDLException.hpp"

WSDL_NAMESPACE_BEGIN

class WSDL_EXPORT ExtensionRegistry
{
protected:
    enum EXTENSION_TYPE {
        ETYPE_NONE = 0,
        ETYPE_ADDRESS,
        ETYPE_BINDING,
        ETYPE_BODY,
        ETYPE_FAULT,
        ETYPE_HEADER,
        ETYPE_HEADER_FAULT,
        ETYPE_OPERATION,
        ETYPE_SCHEMA
    };

    typedef std::map<QNamePtr, int, lessQNamePtr> ExtTypeInnerMap;
    DEFINE_PTR(ExtTypeInnerMap);
    typedef std::map<QNamePtr, ExtTypeInnerMapPtr, lessQNamePtr> ExtTypeMap;
    DEFINE_PTR(ExtTypeMap);
    
public:
	ExtensionRegistry();
	virtual ~ExtensionRegistry();
    
    virtual void mapExtensionTypes(QNamePtr parentType,
                                QNamePtr elementType,
                                EXTENSION_TYPE extensionType);
    virtual ExtensibilityElementPtr createExtension(
            QNamePtr parentType, QNamePtr elementType) throw(WSDLException);

    virtual void registerDeserializer(
        QNamePtr parentType, QNamePtr elementType,
        ExtensionDeserializerPtr ed);

    virtual ExtensionDeserializerPtr queryDeserializer(
        QNamePtr parentType, QNamePtr elementType) throw (WSDLException);
	
  /**
   * Look up the type of the extensibility attribute with the qname attrName,
   * which was defined on an element represented by the specified parentType.
   *
   * @param parentType a class object indicating where in the WSDL
   * document this extensibility attribute was encountered. For
   * example, javax.wsdl.Binding.class would be used to indicate
   * this attribute was defined on a &lt;wsdl:binding> element.
   * @param attrName the qname of the extensibility attribute
   *
   * @return one of the constants defined on the AttributeExtensible class
   *
   * @see #registerExtensionAttributeType(QNamePtr, QNamePtr, int)
   * @see AttributeExtensible
   * @since revision @04
   */
  virtual int queryExtensionAttributeType(QNamePtr parentType, QNamePtr attrName);
  
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
   * @see #queryExtensionAttributeType(QNamePtr, QNamePtr)
   * @see AttributeExtensible
   */
  virtual void registerExtensionAttributeType(QNamePtr parentType,
                                             QNamePtr attrName,
                                             int attrType);
                                             
	virtual ExtensionDeserializerPtr getDefaultDeserializer() { return defaultDeser; }
	virtual void setDefaultDeserializer(ExtensionDeserializerPtr ed) { defaultDeser = ed; }

protected:
    ExtensionDeserializer::MapValueMapPtr deserializerReg;
    ExtTypeMapPtr extensionTypeReg;
    ExtTypeMapPtr extensionAttributeTypeReg;
    
    ExtensionDeserializerPtr defaultDeser;

};

WSDL_NAMESPACE_END

#endif /*EXTENSIONREGISTRY_HPP_*/
