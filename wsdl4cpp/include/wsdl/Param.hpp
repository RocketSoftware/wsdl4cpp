/*
 * %fv:Param.hpp-5 % 
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
#ifndef PARAM_HPP_
#define PARAM_HPP_
#include "wsdl/wsdlbas.hpp"
#include "wsdl/Constants.hpp"
#include "wsdl/Message.hpp"
#include "wsdl/NamedElement.hpp"
#include "wsdl/ext/ElementExtensible.hpp"

WSDL_NAMESPACE_BEGIN

class Param;

DEFINE_PTR(Param);

class WSDL_EXPORT Param : public AttributeExtensible, public NamedElement
{
public:
	Param();
	virtual ~Param();
	
	virtual MessagePtr getMessage() { return mMessage; }
	virtual void setMessage(MessagePtr msg) { mMessage = msg; }

	// NamedElement:: 
	virtual XMLChString toString();
    
protected:
    MessagePtr mMessage;

private:
    virtual XMLChString getTagName() = 0;
	
};

WSDL_NAMESPACE_END

#endif /*PARAM_HPP_*/
