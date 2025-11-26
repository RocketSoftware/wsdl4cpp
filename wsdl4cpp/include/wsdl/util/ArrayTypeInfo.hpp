/*
 * %fv:ArrayTypeInfo.hpp-2 % 
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
 */
#ifndef ARRAYTYPEINFO_HPP_
#define ARRAYTYPEINFO_HPP_

#include "wsdl/wsdlbas.hpp"
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/QName.hpp"
#include "wsdl/WSDLException.hpp"

WSDL_NAMESPACE_BEGIN

class ArrayTypeInfo;
DEFINE_PTR(ArrayTypeInfo);
class WSDL_EXPORT ArrayTypeInfo
{
public:
    typedef std::map<QNamePtr, ArrayTypeInfoPtr, lessQNamePtr> Map;
    DEFINE_PTR(Map);

    ArrayTypeInfo(QNamePtr aType):type(aType){};
    virtual ~ArrayTypeInfo(){};

    virtual QNamePtr getType() { return type; }
    
    virtual QNamePtr getArrayTypeAttribute() { return arrayTypeAttribute; }
    virtual void setArrayTypeAttribute(QNamePtr ata)
    { 
        arrayTypeAttribute = ata;
    }
    
    virtual WSDLExceptionPtr getException() { return exception; }
    virtual void setException(WSDLExceptionPtr e)
    { 
        exception = e;
    }
    
private:
    QNamePtr type;
    QNamePtr arrayTypeAttribute;
    WSDLExceptionPtr exception;
};
    
WSDL_NAMESPACE_END

#endif /*ARRAYTYPEINFO_HPP_*/
