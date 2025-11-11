/*
 * %fv:Message.hpp-3 % 
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
#ifndef MESSAGE_HPP_
#define MESSAGE_HPP_
#include <map>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/NamedElement.hpp"
#include "wsdl/Part.hpp"


WSDL_NAMESPACE_BEGIN

class Message;

DEFINE_PTR(Message);

class WSDL_EXPORT Message : public NamedElement
{
public:
    typedef std::map<QNamePtr, MessagePtr, lessQNamePtr> Map;
    DEFINE_PTR(Map);

	Message();
	virtual ~Message();

	virtual void addPart(PartPtr aPart)
    {
        XMLChString partName = aPart->getName();
        mPartMap->insert(Part::Map::value_type(partName, aPart));
        additionOrderOfParts->push_back(partName);
    }
	virtual PartPtr getPart(XMLChString name) 
	{
		Part::Map::iterator i = mPartMap->find(name);
		if (i == mPartMap->end()) return (PartPtr)0;
		return i->second; 
	}
	
    virtual Part::MapPtr getParts() { return mPartMap; }
    
    virtual Part::ListPtr getOrderedParts(XMLChString::ListPtr partOrder = (XMLChString::ListPtr)0);
    
	virtual bool isUndefined() { return undefined; }
	virtual void setUndefined(bool b) { undefined = b; }
	
	// NamedElement:: 
	virtual XMLChString toString();
private:
	bool undefined;
    XMLChString::ListPtr additionOrderOfParts;
	Part::MapPtr mPartMap;
	
	virtual XMLChString getTagName();
};

WSDL_NAMESPACE_END

#endif /*MESSAGE_HPP_*/
