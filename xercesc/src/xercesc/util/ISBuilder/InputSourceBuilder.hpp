/*
 * Created by Ming Zhu, 2007-01
 * 
 */

#ifndef INPUTSOURCEBUILDER_HPP
#define INPUTSOURCEBUILDER_HPP

#include <xercesc/util/PlatformUtils.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class InputSource;


/**
  * A builder of input source for an XML entity.
  *
  * <p>This class encapsulates information about an input source builder in a
  * single object, which may include the general information about input source,
  * such as proxy server, authentication.
  * </p>
  *
  * <p>InputSourceBuilder specifies the interface of an input source builder
  * implementation, and is never used directly.</p>
  *
  */
class XMLUTIL_EXPORT InputSourceBuilder : public XMemory
{
public:
    // -----------------------------------------------------------------------
    //  All constructors are hidden, just the destructor is available
    // -----------------------------------------------------------------------
    /** @name Destructor */
    //@{
  /**
    * Destructor
    *
    */
    virtual ~InputSourceBuilder();
    //@}


    // -----------------------------------------------------------------------
    /** @name Virtual input source interface */
    //@{
    /** Constructor an input source.
      * @param baseURL The base URL.
	  * @return the counstructed input source.
      */
    virtual InputSource* createInputSource(const XMLCh* const url) const = 0;

    /** Constructor an input source.
      * @param baseURL The base URL.
      * @param relativeURL The relative URL.
 	  * @return the counstructed input source.
     */
    virtual InputSource* createInputSource
    (
        const   XMLCh* const   baseURL
        , const XMLCh* const   relativeURL) const = 0;

    /** Constructor an input source.
      * @param baseURL The base URL.
      * @param relativeURL The relative URL.
 	  * @return the counstructed input source.
     */
    virtual InputSource* createInputSource
    (
        const   XMLCh* const baseURL
        , const char* const relativeURL) const = 0;

	//@}


    // -----------------------------------------------------------------------
    /** @name Getter methods */
    //@{
  /**
    * Get the flag that indicates if the parser should issue fatal error if this input source
    * is not found.
    *
    * @return True if the parser should issue fatal error if this input source is not found.
    *         False if the parser issue warning message instead.
    * @see #setIssueFatalErrorIfNotFound
    */
    virtual bool getIssueFatalErrorIfNotFound() const;

    MemoryManager* getMemoryManager() const;

    //@}


    // -----------------------------------------------------------------------
    /** @name Setter methods */
    //@{

  /**
    * Indicates if the parser should issue fatal error if this input source
    * is not found.  If set to false, the parser issue warning message instead.
    *
    * @param  flag True if the parser should issue fatal error if this input source is not found.
    *               If set to false, the parser issue warning message instead.  (Default: true)
    *
    * @see #getIssueFatalErrorIfNotFound
    */
    virtual void setIssueFatalErrorIfNotFound(const bool flag);

    //@}


protected :
    // -----------------------------------------------------------------------
    //  Hidden constructors
    // -----------------------------------------------------------------------
    /** @name Constructors and Destructor */
    //@{
    /** Default constructor */
    InputSourceBuilder(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

    //@}





private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    InputSourceBuilder(const InputSourceBuilder&);
    InputSourceBuilder& operator=(const InputSourceBuilder&);


    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fProxyAddress
    //      This is the proxy address to use, can be null.
    //
    //  fProxyUserId
    //      This is the optional public id for the input source, can be null.
    //
    //  fProxyPassword
    //      This is the system id for the input source, can be null.
    //
    //  fFatalErrorIfNotFound
    // -----------------------------------------------------------------------
    MemoryManager* const fMemoryManager;
    bool           fFatalErrorIfNotFound;
};


// ---------------------------------------------------------------------------
//  InputSourceBuilder: Getter methods
// ---------------------------------------------------------------------------
inline bool InputSourceBuilder::getIssueFatalErrorIfNotFound() const
{
    return fFatalErrorIfNotFound;
}

inline MemoryManager* InputSourceBuilder::getMemoryManager() const
{
    return fMemoryManager;
}

// ---------------------------------------------------------------------------
//  InputSourceBuilder: Setter methods
// ---------------------------------------------------------------------------
inline void InputSourceBuilder::setIssueFatalErrorIfNotFound(const bool flag)
{
    fFatalErrorIfNotFound = flag;
}

XERCES_CPP_NAMESPACE_END

#endif
