/*
 * %fv:ElementExtensible.hpp-7 % 
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
#ifndef ELEMENTEXTENSIBLE_HPP_
#define ELEMENTEXTENSIBLE_HPP_
#include <list>
#include "wsdl/wsdlbas.hpp"
#include "wsdl/NamedElement.hpp"
#include "wsdl/ext/ExtensibilityElement.hpp"

WSDL_NAMESPACE_BEGIN

class ElementExtensible;

DEFINE_PTR(ElementExtensible);

#define NO_METHOD_TEMPLATES
class WSDL_EXPORT ElementExtensible {
public:
    ElementExtensible() : extElements(new ExtensibilityElement::List()){};
    virtual ~ElementExtensible(){};
    
    virtual void addExtensibilityElement(ExtensibilityElementPtr extElement)
        {extElements->push_back(extElement);}
    virtual ExtensibilityElement::ListPtr getExtensibilityElements() { return extElements; }
    
#ifdef NO_METHOD_TEMPLATES
    ExtensibilityElementPtr getFirstExtensibilityElement(QNamePtr elementType);
#else
    template <typename T> counted_ptr<T> getFirstExtensibilityElement(
        QNamePtr elementType);
    
    template <typename T> counted_ptr<T> getFirstExtensibilityElement();
#endif    
    virtual XMLChString toString();
    
protected:
    ExtensibilityElement::ListPtr extElements;
};

#ifndef NO_METHOD_TEMPLATES
#if !(defined __GNUC__) || (__GNUC__ > 3)
template <typename T> inline counted_ptr<T> ElementExtensible::getFirstExtensibilityElement()
{
	return getFirstExtensibilityElement<T>(T::DEFAULT_ELEM_TYPE);
}

template <typename T> inline counted_ptr<T> ElementExtensible::getFirstExtensibilityElement(QNamePtr elementType)
{
    for(ExtensibilityElement::List::iterator i = extElements->begin(), l = extElements->end();
        i != l; i++)
    {
        if ( i->get()->getElementType()->compare(elementType) == 0 
            //&& T::typeId == i->get()->typeId
            )
        {
            return i->downcastTo<T>();
        }
    }
    return (counted_ptr<T>)0;
}
#endif
#endif

class NamedExtensible;

DEFINE_PTR(NamedExtensible);

class WSDL_EXPORT NamedExtensible
    : public NamedElement
    , public ElementExtensible
{
public:
    virtual XMLChString toString()
    {
        XMLChString s = NamedElement::toString();
        s.append(ElementExtensible::toString());
        return s;
    }
};

WSDL_NAMESPACE_END

#endif /*ELEMENTEXTENSIBLE_HPP_*/
