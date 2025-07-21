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
    static const OperationTypePtr ONE_WAY;
    static const OperationTypePtr REQUEST_RESPONSE;
    static const OperationTypePtr SOLICIT_RESPONSE;
    static const OperationTypePtr NOTIFICATION;

    OperationType(XMLChString id);
	virtual ~OperationType();
	
	//virtual XMLChString toString();
    virtual XMLChString getId() { return id; }
    virtual void setId(XMLChString id) { this->id = id; }

private:
    XMLChString id;

};

WSDL_NAMESPACE_END

#endif /*OPERATIONTYPE_HPP_*/
