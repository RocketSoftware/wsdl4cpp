/*
 * $Id: CurlInputSourceBuilder.hpp $
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * Written by Ming Zhu, Jan 2007
 * 
 */

#ifndef CURLINPUTSOURCEBUILDER_HPP
#define CURLINPUTSOURCEBUILDER_HPP

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/ISBuilder/InputSourceBuilder.hpp>

#include "wsdl/wsdlbas.hpp"
#include "wsdl/InputSourceEnv.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

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
class WSDL_EXPORT CurlInputSourceBuilder : public InputSourceBuilder
{

public:
    // -----------------------------------------------------------------------
    //  constructors
    // -----------------------------------------------------------------------
    /** @name Constructors and Destructor */
    //@{
    /** Default constructor */
    CurlInputSourceBuilder(MemoryManager* const manager = XMLPlatformUtils::fgMemoryManager);

    //@}

    // -----------------------------------------------------------------------
    //  destructors
    // -----------------------------------------------------------------------
    /** @name Destructor */
    //@{
  /**
    * Destructor
    *
    */
    virtual ~CurlInputSourceBuilder();
    //@}


    // -----------------------------------------------------------------------
    /** @name Virtual input source interface */
    //@{
    /** Constructor an input source.
      * @param baseURL The base URL.
	  * @return the counstructed input source.
      */
    virtual InputSource* createInputSource(const XMLCh* const url) const;

    /** Constructor an input source.
      * @param baseURL The base URL.
      * @param relativeURL The relative URL.
 	  * @return the counstructed input source.
     */
    virtual InputSource* createInputSource
    (
        const   XMLCh* const   baseURL
        , const XMLCh* const   relativeURL) const;

    /** Constructor an input source.
      * @param baseURL The base URL.
      * @param relativeURL The relative URL.
 	  * @return the counstructed input source.
     */
    virtual InputSource* createInputSource
    (
        const   XMLCh* const baseURL
        , const char* const relativeURL) const;

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



private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    CurlInputSourceBuilder(const CurlInputSourceBuilder&);
    CurlInputSourceBuilder& operator=(const CurlInputSourceBuilder&);

	InputSourceEnvPtr fInputSourceEnv;

};

WSDL_NAMESPACE_END

#endif
