/*
 * %fv:Fault.hpp-4 % 
 * 
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
 * 01-02                       9.SOAP   mzu  Migrated from WSDL4J
 * 03        070109  t85163    9.SOAP   mzu  Implementation for attribute extension
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 */
#ifndef FAULT_HPP_
#define FAULT_HPP_
#include "wsdl/wsdlbas.hpp"
#include "wsdl/Message.hpp"
#include "wsdl/Param.hpp"

WSDL_NAMESPACE_BEGIN

class Fault;

DEFINE_PTR(Fault);

class WSDL_EXPORT Fault : public Param
{
public:
    typedef std::map<XMLChString, FaultPtr, lessXMLCh> Map;
    DEFINE_PTR(Map);

	Fault();
	virtual ~Fault();
	
    /**
     * @since revision @03
     */
    virtual XMLChString::SetPtr getNativeAttributeNames() const 
    	{ return Constants::FAULT_ATTR_NAMES_SET; };

private:

    // NamedElement::
    virtual XMLChString getTagName();
	
};

WSDL_NAMESPACE_END

#endif /*FAULT_HPP_*/
