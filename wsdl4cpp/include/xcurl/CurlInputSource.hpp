/*
 * $Id: CurlInputSource.hpp $
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * Written by Ming Zhu, Jan 2007
 * 
 */

#if !defined(CURLINPUTSOURCE_HPP)
#define CURLINPUTSOURCE_HPP

#include <xercesc/util/XMLURL.hpp>
#include <xercesc/sax/InputSource.hpp>
#include <xercesc/util/BinInputStream.hpp>

#include "wsdl/wsdlbas.hpp"
#include "wsdl/InputSourceEnv.hpp"

XERCES_CPP_NAMESPACE_USE

//class XERCES_CPP_NAMESPACE_QUALIFIER BinInputStream;

WSDL_NAMESPACE_BEGIN

/**
 *  This class is a derivative of the standard InputSource class. It provides
 *  for the parser access to data which is referenced via a URL, as apposed to
 *  a local file name. The URL can be provided via an XMLURL class, as a fully
 *  qualified system id, or a base system id and a system id which may be
 *  fully qualified or may be relative to the base.
 *
 *  As with all InputSource derivatives. The primary objective of an input
 *  source is to create an input stream via which the parser can spool in
 *  data from the referenced source.
 *
 *  Note that the parse system does not necessarily support URL based XML
 *  entities out of the box. Support for socket based access is optional and
 *  controlled by the per-platform support.
 */
class WSDL_EXPORT CurlInputSource : public InputSource
{
public :
    // -----------------------------------------------------------------------
    //  Constructors and Destructor
    // -----------------------------------------------------------------------

    /** @name Constructors */
    //@{

    /**
      * This constructor accepts an already built URL. It is assumed that
      * it is correct and it will be used as is. In this case, no public id
      * accepted, but it can still be set via the parent class' setPublicId()
      * method.
      *
      * @param  urlId   The URL which holds the system id of the entity
      *                 to parse.
      * @param  manager Pointer to the memory manager to be used to
      *                 allocate objects.
      */
    CurlInputSource
    (
        const XMLURL& urlId
        , MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager
    );


    /**
     *  This constructor takes a base system id URL and a possibly relative
     *  system id. The relative part is parsed and, if it is indeed relative,
     *  it will be made relative to the passed base id. Otherwise, it will be
     *  taken as is.
     *
     *  @param  baseId      The base system id URL which provides the base
     *                      for any relative id part.
     *
     *  @param  systemId    The possibly relative system id URL. If its relative
     *                      its based on baseId, else its taken as is.
     *  @param  manager     Pointer to the memory manager to be used to
     *                      allocate objects.
     */
    CurlInputSource
    (
        const   XMLCh* const    baseId
        , const XMLCh* const    systemId
        , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
    );

    /**
     *  This constructor is indentical to the previous one, except that it also
     *  allows you to set a public id if you want to.
     *
     *  @param  baseId      The base system id URL which provides the base
     *                      for any relative id part.
     *
     *  @param  systemId    The possibly relative system id URL. If its relative
     *                      its based on baseId, else its taken as is.
     *
     *  @param  publicId    The optional public id to set. This is just passed
     *                      on to the parent class for storage.
     *
     * @param  manager      Pointer to the memory manager to be used to
     *                      allocate objects.
     */
    CurlInputSource
    (
        const   XMLCh* const    baseId
        , const XMLCh* const    systemId
        , const XMLCh* const    publicId
        , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
    );


    /**
     *  This constructor is identical to the second constructor above, except that
     *  it accepts the relative system id part as a local code page string and
     *  just transcodes it internally, as a convenience.
     *
     *  @param  baseId      The base system id URL which provides the base
     *                      for any relative id part.
     *
     *  @param  systemId    The possibly relative system id URL. If its relative
     *                      its based on baseId, else its taken as is.
     *
     *  @param  manager     Pointer to the memory manager to be used to
     *                      allocate objects.
     */
    CurlInputSource
    (
        const   XMLCh* const    baseId
        , const char* const     systemId
        , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
    );

    /**
     *  This constructor is identical to the third constructor above, except that
     *  it accepts the relative and public ids as local code page strings and just
     *  transcodes them internally, as a convenience.
     *
     *  @param  baseId      The base system id URL which provides the base
     *                      for any relative id part.
     *
     *  @param  systemId    The possibly relative system id URL. If its relative
     *                      its based on baseId, else its taken as is.
     *
     *  @param  publicId    The optional public id to set. This is just passed
     *                      on to the parent class for storage.
     *                      on to the parent class for storage.
     *
     *  @param  manager     Pointer to the memory manager to be used to
     *                      allocate objects.
     */
    CurlInputSource
    (
        const   XMLCh* const    baseId
        , const char* const     systemId
        , const char* const     publicId
        , MemoryManager* const  manager = XMLPlatformUtils::fgMemoryManager
    );

    //@}

    /** @name Destructor */
    //@{
    ~CurlInputSource();
    //@}


    // -----------------------------------------------------------------------
    //  Virtual input source interface
    // -----------------------------------------------------------------------

    /** @name Virtual methods */
    //@{

    /**
     * This method will return a binary input stream derivative that will
     * parse from the source refered to by the URL system id.
     */
    BinInputStream* makeStream() const;

    //@}


    // -----------------------------------------------------------------------
    //  Getter methods
    // -----------------------------------------------------------------------

    /** @name Getter methods */
    //@{

    /**
      * This method will return a const reference to the URL member which
      * contains the system id in pre-parsed URL form. If you just want the
      * string format, call getSystemId() on the parent class.
      *
      * @return A const reference to a URL object that contains the current
      *         system id set for this input source.
      */
    const XMLURL& urlSrc() const;

    //@}

    // -----------------------------------------------------------------------
    //  getters and setters
    // -----------------------------------------------------------------------
    /** @name getters and setters */
    //@{
    /**
     * Returns the input source environment.
     * @return the input source environment.
     */
	InputSourceEnvPtr getInputSourceEnv() const { return fInputSourceEnv; }

    /**
     * Returns the input source environment.
     * @return the input source environment.
     */
	void setInputSourceEnv(const InputSourceEnvPtr ptr) { fInputSourceEnv = ptr;}

    //@}


private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------    
    CurlInputSource(const CurlInputSource&);
    CurlInputSource& operator=(const CurlInputSource&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fURL
    //      This is the URL created from the passed ids.
    // -----------------------------------------------------------------------
    XMLURL fURL;
    
	InputSourceEnvPtr fInputSourceEnv;
};


inline const XMLURL& CurlInputSource::urlSrc() const
{
    return fURL;
}

WSDL_NAMESPACE_END

#endif
