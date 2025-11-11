/*
 * %fv:Service.hpp-4 % 
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
#ifndef SERVICE_HPP_
#define SERVICE_HPP_
#include "wsdl/wsdlbas.hpp"
#include "wsdl/ext/ExtensibilityElement.hpp"
#include "wsdl/NamedElement.hpp"
#include "wsdl/Port.hpp"

WSDL_NAMESPACE_BEGIN

class Service;

DEFINE_PTR(Service);

class WSDL_EXPORT Service : 
    public NamedElement, 
    public ElementExtensible
{
public:
    typedef std::map<QNamePtr, ServicePtr, lessQNamePtr> Map;
    typedef std::list<ServicePtr> List;
    DEFINE_PTR(Map);
    DEFINE_PTR(List);

	Service();
	virtual ~Service();

    virtual void addPort(PortPtr aPort)
    { 
        mPortMap->insert(Port::Map::value_type(
            aPort->getName(), aPort));
    }
    virtual PortPtr getPort(XMLChString name) 
    {
        Port::Map::iterator i = mPortMap->find(name);
        if (i == mPortMap->end()) return (PortPtr)0;
        return i->second; 
    }
    virtual Port::MapPtr getPorts() { return mPortMap; }
    
    // NamedElement:: 
    virtual XMLChString toString();
private:
    Port::MapPtr mPortMap;
    
	virtual XMLChString getTagName();
};

WSDL_NAMESPACE_END

#endif /*SERVICE_HPP_*/
