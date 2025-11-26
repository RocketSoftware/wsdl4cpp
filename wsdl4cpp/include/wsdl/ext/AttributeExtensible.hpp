/*
 * %fv:AttributeExtensible.hpp-2 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
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
 * 01        070109  t85163    9.SOAP   mzu  Migrated from WSDL4J
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 */
#ifndef ATTRIBUTEEXTENSIBLE_HPP_
#define ATTRIBUTEEXTENSIBLE_HPP_
#include <list>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/ext/ExtensibilityAttribute.hpp"

WSDL_NAMESPACE_BEGIN

class AttributeExtensible;

DEFINE_PTR(AttributeExtensible);

class WSDL_EXPORT AttributeExtensible {
	
public:

    AttributeExtensible() : extensionAttributes(new ExtensibilityAttribute::Map()){};
    virtual ~AttributeExtensible(){};
    
  /**
   * Set an extension attribute on this element. Pass in a null value to remove
   * an extension attribute.
   *
   * @param name the extension attribute name
   * @param value the extension attribute value. Can be a String, a QName, a
   * List of Strings, or a List of QNames.
   *
   * @see #getExtensionAttribute
   * @see #getExtensionAttributes
   * @see ExtensionRegistry#registerExtensionAttributeType
   * @see ExtensionRegistry#queryExtensionAttributeType
   */
  virtual void setExtensionAttribute(QNamePtr name, ExtensibilityAttributePtr value)
  {
    if (!value)
    {
        extensionAttributes->insert(ExtensibilityAttribute::Map::value_type(
            name, value));
    }
    else
    {
		extensionAttributes->erase(name);
    }
  }

  /**
   * Retrieve an extension attribute from this element. If the extension
   * attribute is not defined, null is returned.
   *
   * @param name the extension attribute name
   *
   * @return the value of the extension attribute, or null if
   * it is not defined. Can be a String, a QName, a List of Strings, or a List
   * of QNames.
   *
   * @see #setExtensionAttribute
   * @see #getExtensionAttributes
   * @see ExtensionRegistry#registerExtensionAttributeType
   * @see ExtensionRegistry#queryExtensionAttributeType
   */
  virtual ExtensibilityAttributePtr getExtensionAttribute(QNamePtr name)
  {
		ExtensibilityAttribute::Map::iterator i = extensionAttributes->find(name);
		return (i == extensionAttributes->end()) ? 
            (ExtensibilityAttributePtr)0 : i->second; 
  }

  /**
   * Get the map containing all the extension attributes defined
   * on this element. The keys are the qnames of the attributes.
   *
   * @return a map containing all the extension attributes defined
   * on this element
   *
   * @see #setExtensionAttribute
   * @see #getExtensionAttribute
   */
  virtual ExtensibilityAttribute::MapPtr getExtensionAttributes()
  {
       return extensionAttributes;
  }

  /**
   * Get the list of local attribute names defined for this element in
   * the WSDL specification.
   *
   * @return a List of Strings, one for each local attribute name
   */
  virtual XMLChString::SetPtr getNativeAttributeNames() const = 0;

    virtual XMLChString toString();
    
protected:
    ExtensibilityAttribute::MapPtr extensionAttributes;
};

WSDL_NAMESPACE_END

#endif /*ATTRIBUTEEXTENSIBLE_HPP_*/
