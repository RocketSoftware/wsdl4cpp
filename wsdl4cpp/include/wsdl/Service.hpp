/*
 * %fv:Service.hpp-4 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
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
