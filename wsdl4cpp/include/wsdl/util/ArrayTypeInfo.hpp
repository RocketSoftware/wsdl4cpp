/*
 * %fv:ArrayTypeInfo.hpp-2 % 
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
