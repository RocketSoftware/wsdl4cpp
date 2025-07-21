/*
 * %fv:wsdlbas.hpp-6 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 */
#ifndef WSDLBAS_HPP_
#define WSDLBAS_HPP_

#if defined(_MSC_VER)
#pragma warning( disable : 4290 4251 )
#if _MSC_VER==1200
#define MEMBER_TEMPLATES_VC6
#endif
#define WSDL_IM_EX_PORT
#endif

#ifdef WSDL_IM_EX_PORT
  #define PLATFORM_EXPORT     __declspec(dllexport)
  #define PLATFORM_IMPORT     __declspec(dllimport)
#else
  #define PLATFORM_EXPORT
  #define PLATFORM_IMPORT
#endif

#if defined(PROJ_WSDL_DLL)
#define WSDL_EXPORT PLATFORM_EXPORT
#else
#define WSDL_EXPORT PLATFORM_IMPORT
#endif

// ---------------------------------------------------------------------------
// Define namespace symbols if the compiler supports it.
// ---------------------------------------------------------------------------
#define WSDL_NAMESPACE wsdl
#if defined(WSDL_NAMESPACE)
    #define WSDL_NAMESPACE_BEGIN namespace WSDL_NAMESPACE {
    #define WSDL_NAMESPACE_END  }
    #define USING_WSDL_NAMESPACE using namespace WSDL_NAMESPACE;
    #define WSDL_NAMESPACE_QUALIFIER WSDL_NAMESPACE::

#else
    #define WSDL_NAMESPACE_BEGIN
    #define WSDL_NAMESPACE_END
    #define USING_WSDL_NAMESPACE
    #define WSDL_NAMESPACE_QUALIFIER
#endif

#define USING_STD using namespace std;

WSDL_NAMESPACE_BEGIN

#define DEFINE_PTR(__class__) typedef counted_ptr<__class__> __class__##Ptr

/* For ANSI-challenged compilers, you may want to #define
 * NO_MEMBER_TEMPLATES or explicit */

template <class Y> struct counter {
    counter(Y* p = 0, unsigned c = 1) : ptr(p), count(c) {}
    Y*          ptr;
    unsigned    count;
};
    
template <typename X> inline void checkSubClass(const X* c){}

template <class X> class counted_ptr
{
public:
    typedef X element_type;

    explicit counted_ptr(X* p = 0) // allocate a new counter
        : itsCounter(0) {if (p) itsCounter = new counter<X>(p);}
    ~counted_ptr()
        {release();}


//#define NO_MEMBER_TEMPLATES
#ifdef NO_MEMBER_TEMPLATES
    //TODO: use the same compiler macro in xerces
    friend class counted_ptr;

    counted_ptr(const counted_ptr& r) throw()
        {acquire(r.itsCounter);}
    counted_ptr& operator=(const counted_ptr& r)
    {
        if (this != &r) {
            release();
            acquire(r.itsCounter);
        }
        return *this;
    }

    bool inline operator==(const counted_ptr& r)
    {
    	return ( this == &r || itsCounter == r.itsCounter);
    }
    
    void acquire(counter<X>* c) throw()
    { // increment the count
        itsCounter = (counter<X>*)c;
        if (c) ++c->count;
    }

#elif defined(MEMBER_TEMPLATES_VC6)

    friend class counted_ptr;
    
    template<> counted_ptr(const counted_ptr& r) throw()
        {acquire(r.itsCounter);}

    template<> counted_ptr& operator=(const counted_ptr& r)
    {
        if (this != &r) {
            release();
            acquire(r.itsCounter);
        }
        return *this;
    }
    
    template <> bool inline operator==(const counted_ptr& r)
    {
    	return ( this == &r || itsCounter == r.itsCounter);
    }
    
    template <class Y> void acquire(counter<Y>* c) throw()
    { // increment the count
        itsCounter = (counter<X>*)c;
        if (c) ++c->count;
    }

#elif defined(MEMBER_TEMPLATES_VC6XXX)

    friend class counted_ptr;
    
    template<> counted_ptr(const counted_ptr& r) throw()
        {acquire(r.itsCounter);}

    template<> counted_ptr& operator=(const counted_ptr& r)
    {
        if (this != &r) {
            release();
            acquire(r.itsCounter);
        }
        return *this;
    }
    
    template <> bool inline operator==(const counted_ptr& r)
    {
    	return ( this == &r || itsCounter == r.itsCounter);
    }
    
    template <class Y> void acquire(counter<Y>* c) throw()
    { // increment the count
        itsCounter = (counter<X>*)c;
        if (c) ++c->count;
    }

#else

    template <class Y> friend class counted_ptr;
    
    counted_ptr(const counted_ptr& r) throw()
        {acquire(r.itsCounter);}
    counted_ptr& operator=(const counted_ptr& r)
    {
        if (this != &r) {
            release();
            acquire(r.itsCounter);
        }
        return *this;
    }

    bool inline operator==(const counted_ptr& r)
    {
        return ( this == &r || itsCounter == r.itsCounter);
    }
    
    operator bool ()
    {
        return (!isNull());
    }
    
    void acquire(counter<X>* c) throw()
    { // increment the count
        itsCounter = (counter<X>*)c;
        if (c) ++c->count;
    }

    template <class Y> counted_ptr(const counted_ptr<Y>& r) throw()
        {acquire(r.itsCounter);}
        
    template <class Y> counted_ptr& operator=(const counted_ptr<Y>& r)
    {
        if ((counted_ptr<Y>*)this != &r) {
            release();
            acquire(r.itsCounter);
        }
        return *this;
    }
    
    template <class Y> bool inline operator==(const counted_ptr<Y>& r)
    {
    	return ( (counted_ptr<Y>*)this == &r || (counter<Y>*)itsCounter == r.itsCounter);
    }
    
    template <class Y> void acquire(counter<Y>* c) throw()
    { // increment the count
        checkSubClass<X>((Y*)0);
        itsCounter = (counter<X>*)c;
        if (c) ++c->count;
    }
    
    template <class Y> void acquireDown(counter<Y>* c) throw()
    { // increment the count
        checkSubClass<Y>((X*)0);
        itsCounter = (counter<X>*)c;
        if (c) ++c->count;
    }
    
    template <typename Y> counted_ptr<Y> downcastTo()
    {
        counted_ptr<Y> r;
        if ((counted_ptr<Y>*)this != &r) {
            r.release();
            r.acquireDown(itsCounter);
        }
        return r;
    }

#endif // NO_MEMBER_TEMPLATES

//    counted_ptr& operator=(X* p)
//	{
//        release();
//        if (p) itsCounter = new counter(p);
//        return *this;
//	}
//	
    X& operator*()  const throw()   {return *itsCounter->ptr;}
    X* operator->() const throw()   {
    	return itsCounter->ptr;
    }
    X* get()        const throw()   {return itsCounter ? itsCounter->ptr : 0;}
    bool unique()   const throw()
        {return (itsCounter ? itsCounter->count == 1 : true);}
        
    bool isNull() const { return !itsCounter; }

    counter<X>* itsCounter;


//    void acquire(counter<X>* c) throw()
//    { // increment the count
//        itsCounter = c;
//        if (c) ++c->count;
//    }

    void release()
    { // decrement the count, delete if it is 0
        if (itsCounter) {
            if (--itsCounter->count == 0) {
                delete itsCounter->ptr;
                delete itsCounter;
            }
            itsCounter = 0;
        }
    }
protected:
};

template <typename X, typename Y> class counted_owned_ptr
    : public counted_ptr<Y>
{
public:
    typedef X element_type;
    typedef counted_ptr<Y> owner_type;

//    explicit counted_owned_ptr(X* p = 0, Y* o=0) // allocate a new counter
//        : owner_type(o)
//    {
//        if ( !owner_type::isNull() )
//        {
//            ptr = p;
//        }
//    }
    
    explicit counted_owned_ptr(X* p = 0, owner_type o = owner_type(0)) // allocate a new counter
        : owner_type(o)
    {
        if ( !owner_type::isNull() )
        {
            ptr = p;
        }
		else
		{
			ptr = 0;
		}
    }
    
    ~counted_owned_ptr(){}


//#define NO_MEMBER_TEMPLATES
#ifdef NO_MEMBER_TEMPLATES
    //TODO: use the same compiler macro in xerces
    friend class counted_owned_ptr;

    counted_owned_ptr(const counted_owned_ptr& r) throw()
    {
        acquire(r.ptr, r.itsCounter);
    }
    
    counted_owned_ptr& operator=(const counted_owned_ptr& r)
    {
        if (this != &r) {
            release();
            acquire(r.ptr, r.itsCounter);
        }
        return *this;
    }

    bool inline operator==(const counted_owned_ptr& r)
    {
        return ( this == &r || (ptr == r.ptr && itsCounter == r.itsCounter) );
    }
    
    void acquire(X* p, counter<Y>* c) throw()
    { // increment the count
        acquire(c);
        if (c)
        {
            ptr = p;
        }
    }

#else

    //template <typename X2> friend class counted_owned_ptr<X2,Y>;
    
    counted_owned_ptr(const counted_owned_ptr& r) throw()
    {
        acquire(r.ptr, r.itsCounter);
    }
        
    counted_owned_ptr& operator=(const counted_owned_ptr& r)
    {
        if (this != &r) {
            release();
            acquire(r.ptr, r.itsCounter);
        }
        return *this;
    }

    bool inline operator==(const counted_owned_ptr& r)
    {
        return ( this == &r || (ptr == r.ptr && counted_ptr<Y>::itsCounter == r.itsCounter));
    }
    
    operator bool ()
    {
        return (ptr != 0);
    }
    
    void acquire(X* p, counter<Y>* c) throw()
    { // increment the count
        owner_type::acquire(c);
        if (c)
        {
            ptr = p;
        }
		else
		{
			ptr = 0;
		}
    }

    template <typename X2> counted_owned_ptr(const counted_owned_ptr<X2, Y>& r) throw()
        {acquire(r.ptr, r.itsCounter);}
        
    template <typename X2> counted_owned_ptr& operator=(const counted_owned_ptr<X2, Y>& r)
    {
        if ((counted_owned_ptr<X2, Y>*)this != &r) {
            release();
            acquire(r.ptr, r.itsCounter);
        }
        return *this;
    }
    
    template <typename X2> bool inline operator==(const counted_owned_ptr<X2, Y>& r)
    {
        return ( (counted_owned_ptr<X2, Y>*)this == &r 
            || ( ptr == (X*)r.ptr && owner_type::itsCounter == r.itsCounter) );
    }
    
    template <typename X2> void acquire(X2* p, counter<Y>* c) throw()
    { // increment the count
        acquire(c);
        if (c)
        {
            ptr = (X*)p;
            ++c->count;
        }
    }
    
#endif // NO_MEMBER_TEMPLATES

//    counted_owned_ptr& operator=(X* p)
//  {
//        release();
//        if (p) itsCounter = new counter(p);
//        return *this;
//  }
//  
    X& operator*()  const throw()   {return *ptr;}
    
    X* operator->() const throw()   {
        return ptr;
    }
    
    X* getOwned() const throw()   {return ptr;}
    

//    void acquire(counter<X>* c) throw()
//    { // increment the count
//        itsCounter = c;
//        if (c) ++c->count;
//    }

protected:

    X* ptr;

    void release()
    { // decrement the count, delete if it is 0
        owner_type::release();
        ptr = 0;
    }
};

#define DEFINE_OWNED_PTR(__class__, __owner_class__) typedef counted_owned_ptr<__class__, __owner_class__> __class__##Ptr

class Definitions;

DEFINE_PTR(Definitions);

class ExtensionDeserializer;

DEFINE_PTR(ExtensionDeserializer);

class ExtensionRegistry;

DEFINE_PTR(ExtensionRegistry);

class Import;

DEFINE_PTR(Import);

WSDL_NAMESPACE_END

#endif /*WSDLBAS_HPP_*/
