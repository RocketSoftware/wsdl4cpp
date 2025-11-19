/*
 * %fv:OperationType.hpp-3 % 
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
 * (c) 2025 Rocket Software, Inc. or its affiliates
 */
/*******************************************************************************
date   refnum    version who description
120101 c29155    E103    ahn Determine operation type, oneway, requestresponse, etc correctly on RSD
date   refnum    version who description
*******************************************************************************/

#ifndef OPERATIONTYPE_HPP_
#define OPERATIONTYPE_HPP_
#include "wsdl/wsdlbas.hpp"
#include "wsdl/wsdlxerces.hpp"

WSDL_NAMESPACE_BEGIN

class OperationType;

DEFINE_PTR(OperationType);


class WSDL_EXPORT OperationType
{
public:
    // @c29155 these can no longer be const
    static OperationTypePtr ONE_WAY;
    static OperationTypePtr REQUEST_RESPONSE;
    static OperationTypePtr SOLICIT_RESPONSE;
    static OperationTypePtr NOTIFICATION;

    OperationType(XMLChString id);
	virtual ~OperationType();
	
	//virtual XMLChString toString();
    virtual XMLChString getId() { return id; }
    virtual void setId(XMLChString id) { this->id = id; }

    //@c29155 initialise and release static members explicitly
	static void init();
	static void release();

private:
    XMLChString id;

};

WSDL_NAMESPACE_END

#endif /*OPERATIONTYPE_HPP_*/
