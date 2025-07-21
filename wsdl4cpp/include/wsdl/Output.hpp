/*
 * %fv:Output.hpp-4 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
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
#ifndef OUTPUT_HPP_
#define OUTPUT_HPP_
#include "wsdl/wsdlbas.hpp"
#include "wsdl/Message.hpp"
#include "wsdl/Param.hpp"

WSDL_NAMESPACE_BEGIN

class Output;

DEFINE_PTR(Output);

class WSDL_EXPORT Output : public Param
{
public:
	Output();
	virtual ~Output();
	
    /**
     * @since revision @03
     */
    virtual XMLChString::SetPtr getNativeAttributeNames() const 
    	{ return Constants::OUTPUT_ATTR_NAMES_SET; };

private:

    // NamedElement::
    virtual XMLChString getTagName();
	
};

WSDL_NAMESPACE_END

#endif /*OUTPUT_HPP_*/
