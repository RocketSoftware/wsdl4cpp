/*
 * %fv:PortType.hpp-5 % 
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
 * 01-03                       9.SOAP   mzu  Migrated from WSDL4J
 * 04        070109  t85163    9.SOAP   mzu  Implementation for attribute extension
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 */
#ifndef PORTTYPE_HPP_
#define PORTTYPE_HPP_
#include <list>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/Constants.hpp"
#include "wsdl/NamedElement.hpp"
#include "wsdl/Operation.hpp"
#include "wsdl/WSDLException.hpp"
#include "wsdl/ext/AttributeExtensible.hpp"

WSDL_NAMESPACE_BEGIN

class PortType;

DEFINE_PTR(PortType);

class WSDL_EXPORT PortType : public AttributeExtensible, public NamedElement
{
public:
    typedef std::map<QNamePtr, PortTypePtr, lessQNamePtr> Map;
    DEFINE_PTR(Map);

	PortType();
	virtual ~PortType();

    /**
     * Add an operation to this port type.
     *
     * @param operation the operation to be added
     */
	virtual void addOperation(OperationPtr aOperation){ mOperationList->push_back(aOperation);}

  /**
   * Get the specified operation. Note that operation names can
   * be overloaded within a PortType. In case of overloading, the
   * names of the input and output messages can be used to further
   * refine the search.
   *
   * @param name the name of the desired operation.
   * @param inputName the name of the input message; if this is null
   * it will be ignored.
   * @param outputName the name of the output message; if this is null
   * it will be ignored.
   * @return the corresponding operation, or null if there wasn't
   * any matching operation
   */
  virtual OperationPtr getOperation(XMLChString name,
        XMLChString inputName, XMLChString outputName) throw (WSDLException);
        
    /**
     * Get all the operations defined here.
     */
    virtual Operation::ListPtr getOperations()
    {
        return mOperationList;
    }
	
    /**
     * @return undefined
     */
	virtual bool isUndefined() { return undefined; }

    /**
     * @param b
     */
	virtual void setUndefined(bool b) { undefined = b; }
	
    /**
     * @since revision @04
     */
    virtual XMLChString::SetPtr getNativeAttributeNames() const 
    	{ return Constants::PORTTYPE_ATTR_NAMES_SET; };

    /**
     * toString
     */
	virtual XMLChString toString();
	
private:
	bool undefined;
	Operation::ListPtr mOperationList;
	
	virtual XMLChString getTagName();
};

WSDL_NAMESPACE_END

#endif /*PORTTYPE_HPP_*/
