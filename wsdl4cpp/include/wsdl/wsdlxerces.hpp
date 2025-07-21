/*
 * %fv:wsdlxerces.hpp-8 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * History:
 * 
 * revision  date    refnum    version  who  description
 * -----------------------------------------------------------------------
 * 01-02                       9.SOAP   mzu  Migrated from WSDL4J
 * 03        070109  t85163    9.SOAP   mzu  Implementation for attribute extension
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 * 
 */
#ifndef WSDLXERCES_HPP_
#define WSDLXERCES_HPP_

#if defined(_MSC_VER)
#pragma warning( disable : 4996 )
#endif

#include <functional>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XMLString.hpp>
#include "wsdl/wsdlbas.hpp"

//XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

#define XMLCHPTR(s) (XERCES_CPP_NAMESPACE_QUALIFIER XMLString::transcode(s))
#define TO_LOCAL(s) (XERCES_CPP_NAMESPACE_QUALIFIER XMLString::transcode(s))
#define XMLBOOL(s) (XERCES_CPP_NAMESPACE_QUALIFIER XMLString::compareIString(Constants::XMLSTR_TRUE, s) == 0)

struct lessXMLCh;

#ifndef USE_DEFAULT_USHORT_TRAIT
class XMLChTraits
{
public:
	typedef XMLCh 	char_type;
	
	typedef unsigned long  	int_type;
	
	static void assign(char_type& c1, const char_type& c2) { c1 = c2; }
	
	static bool eq(const char_type& c1, const char_type& c2)
	{ return c1 == c2; }
	
	static bool lt(const char_type& c1, const char_type& c2)
	{ return c1 < c2; }
	
	static int compare(const char_type* s1, const char_type* s2, size_t count)
	{ 
		for (size_t i = 0; i < count; ++i)
		{
		  if (!eq(s1[i], s2[i]))
		    return lt(s1[i], s2[i]) ? -1 : 1;
		}
		return 0; 
	}
	
	static size_t length(const char_type* s)
	{ 
		const char_type* p = s; 
		while (*p) ++p; 
		return (p - s); 
	}
	
	static const char_type* find(const char_type* s, size_t count, const char_type& c)
	{ 
		for (const char_type* p = s; size_t(p - s) < count; ++p)
		{
		  if (*p == c) 
		  	return p;
		}
		return 0;
	}
	
	static char_type* move(char_type* s1, const char_type* s2, size_t count)
	{ return (char_type*) memmove(s1, s2, count * sizeof(char_type)); }
	
	static char_type* copy(char_type* s1, const char_type* s2, size_t count)
	{ return (char_type*) memcpy(s1, s2, count * sizeof(char_type)); }
	
	static char_type* assign(char_type* s, size_t count, char_type c)
	{ 
		for (char_type* p = s; p < s + count; ++p) 
		  assign(*p, c);
		return s; 
	}
	
	static char_type to_char_type(const int_type& i)
	{ return char_type(); }
	
	static int_type to_int_type(const char_type& c) { return int_type(); }
	
	static bool eq_int_type(const int_type& c1, const int_type& c2)
	{ return c1 == c2; }
	
	static int_type eof() { return static_cast<int_type>(-1); }
	
	static int_type not_eof(const int_type& i)
	{ return eq_int_type(i, eof()) ? int_type(0) : i; }
};

typedef std::allocator<XMLCh> XMLChAllocator;

class XMLChString : public std::basic_string<XMLCh, XMLChTraits, XMLChAllocator> {
    typedef std::basic_string<XMLCh, XMLChTraits, XMLChAllocator> _BaseType;

#else //USE_DEFAULT_USHORT_TRAIT

class XMLChString : public std::basic_string<XMLCh> {
    typedef std::basic_string<XMLCh> _BaseType;

#endif //USE_DEFAULT_USHORT_TRAIT

public:

    typedef std::list<XMLChString> List;
    DEFINE_PTR(List);
    typedef std::vector<XMLChString> Vector;
    
    typedef std::set<XMLChString> Set; //@03
    DEFINE_PTR(Set);                   //@03
    
    typedef std::map<XMLChString, XMLChString, lessXMLCh> XMLStrMap;
    DEFINE_PTR(XMLStrMap);

	static const WSDL_EXPORT XMLCh EMPTY_STRING[];

	static ListPtr createList(const XMLChString* ss); //@03

	static SetPtr createSet(const XMLChString* ss);   //@03

	XMLChString():_BaseType(),_null(true){}
    
	XMLChString(const XMLChString& xs):_BaseType(xs.isNull() ? EMPTY_STRING : xs.c_str()),_null(xs.isNull()){}
    XMLChString(const _BaseType& xs):_BaseType(xs),_null(false){}
	XMLChString(const XMLCh* p):_BaseType(p==0 ? EMPTY_STRING :p),_null(p==0){}

	XMLChString(const std::string& s)
	{
		XMLCh* p = XMLCHPTR(s.c_str());
        new (this)XMLChString(p);
		XERCES_CPP_NAMESPACE_QUALIFIER XMLString::release(&p);
	}

	std::string toLocal()
	{
		char* p = TO_LOCAL(c_str());
		std::string s = p;
		XERCES_CPP_NAMESPACE_QUALIFIER XMLString::release(&p);
		return s; 
	}

	bool isNull() const {return _null;}
	const XMLCh * c_str() const
		{	
			//if ( isNull() ) throw NullException("XMLChString");
			return isNull() ? 0 : _BaseType::c_str();
		}
        
    int compare(const XMLChString& __str) const
    {
        if ( isNull() ) return !__str.isNull();
        if ( __str.isNull() ) return -1;
        return _BaseType::compare(__str);
    }

    static void init();
    static void release();
    static WSDL_EXPORT XMLChString getNull() { return __NULL; };
    
private:
    bool _null;
    
    static WSDL_EXPORT XMLChString __NULL;
    
};

#define null XMLChString::getNull()
//static const XMLChString null;

bool inline operator==(
        const XMLChString& _Left,
        const XMLChString& _Right)
    {
        return ( _Left.compare(_Right) == 0);
    }
bool inline operator==(
        const XMLChString& _Left,
        const XMLCh* _Right)
    {
        return ( _Left.compare(_Right) == 0);
    }
bool inline operator!=(
		const XMLChString& _Left,
		const XMLChString& _Right)
	{
		return ( !(_Left==_Right));
	}

inline XMLChString toXmlStr(std::string s)
{
    XMLCh* p = XMLCHPTR(s.c_str());
    XMLChString xs = p;
    XERCES_CPP_NAMESPACE_QUALIFIER XMLString::release(&p);
    return xs; 
}

inline std::string toLocal(XMLChString xstr)
{
    char* p = TO_LOCAL(xstr.c_str());
    std::string s = p;
    XERCES_CPP_NAMESPACE_QUALIFIER XMLString::release(&p);
    return s; 
}

struct lessXMLCh : public std::binary_function<XMLChString, XMLChString, bool>
{
    bool
    operator()(const XMLChString& __x, const XMLChString& __y) const
    { return __x.compare(__y) < 0; }
};

WSDL_NAMESPACE_END

#endif /*WSDLXERCES_HPP_*/
