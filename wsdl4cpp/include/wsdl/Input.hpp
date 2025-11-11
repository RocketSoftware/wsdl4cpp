/*
 * %fv:Input.hpp-4 % 
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
 * 01-02                       9.SOAP   mzu  Migrated from WSDL4J
 * 03        070109  t85163    9.SOAP   mzu  Implementation for attribute extension
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 */
#ifndef INPUT_HPP_
#define INPUT_HPP_
#include "wsdl/wsdlbas.hpp"
#include "wsdl/Message.hpp"
#include "wsdl/Param.hpp"

WSDL_NAMESPACE_BEGIN

class Input;

DEFINE_PTR(Input);

class WSDL_EXPORT Input : public Param
{
public:
	Input();
	virtual ~Input();
	
    /**
     * @since revision @04
     */
    virtual XMLChString::SetPtr getNativeAttributeNames() const 
    	{ return Constants::INPUT_ATTR_NAMES_SET; };
    	
private:

    // NamedElement::
    virtual XMLChString getTagName();
	
};

WSDL_NAMESPACE_END

#endif /*INPUT_HPP_*/
