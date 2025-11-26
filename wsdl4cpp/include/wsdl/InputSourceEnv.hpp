/*
 * Created by Ming Zhu, 2007-01
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
 */
/*
 * $Id:$
 *
 * %fv: % %dc: %
 */


#ifndef INPUTSOURCEENV_HPP
#define INPUTSOURCEENV_HPP

#include <string>
#include <xercesc/util/PlatformUtils.hpp>

#include "wsdl/wsdlbas.hpp"

WSDL_NAMESPACE_BEGIN

class InputSourceEnv;

DEFINE_PTR(InputSourceEnv);

/**
  * An environment of input source.
  *
  * <p>This class encapsulates information about input sources in a
  * single object, which may include the general information about input source,
  * such as proxy server, authentication.
  * </p>
  *
  */
class InputSourceEnv
{
public:

    // -----------------------------------------------------------------------
    //  constructors
    // -----------------------------------------------------------------------
    /** @name Constructors and Destructor */
    //@{
    /** Default constructor */
	InputSourceEnv() : authenticated(false)
        , fConnectTimeout(0)
        , fTransactionTimeout(0)
    {};

  /**
    * Destructor
    *
    */
	virtual ~InputSourceEnv(){};
    //@}

    // -----------------------------------------------------------------------
    /** @name Getter methods */
    //@{
  /**
    * An input source can be set to force the parser to assume a particular
    * proxy address for the data that input source reprsents, via the setProxyAddress()
    * method. This method returns name of the proxy address that is to be forced.
    * If the proxy address has never been forced, it returns a null pointer.
    *
    * @return The forced proxy address, or null if none was supplied.
    * @see #setProxyAddress
    */
	virtual const char* getProxyAddress() const { return fProxyAddress.c_str(); }

  /**
    * Return the proxy port.
    *
    * @return The forced proxy port.
    * @see #setProxyAddress
    */
    virtual int getProxyPort() const { return fProxyPort; }


  /**
    * Get the proxy user id for this input source.
    *
    * @return The proxy user id, or null if none was supplied.
    * @see #setProxyUserId
    */
    virtual const char* getProxyUserId() const { return fProxyUserId.c_str(); }


  /**
    * Get the proxypassword for this input source.
    *
    * <p>If the system ID is a URL, it will be fully resolved.</p>
    *
    * @return The proxypassword.
    * @see #setProxyPassword
    */
    virtual const char* getProxyPassword() const { return fProxyPassword.c_str(); }

  /**
    * Get the authenticated.
    *
    * @return The boolean value.
    * @see #setAuthenticated
    */
	virtual bool isAuthenticated()
	{
		return authenticated;
	}

  /**
    * Get the connect timeout.
    *
    * @return the timeout duration in milliseconds.
    * @see #setConnectTimeout
    */
    virtual long getConnectTimeout() const { return fConnectTimeout; }

  /**
    * Set the transaction timeout.
    *
    * @return the timeout duration in milliseconds.
    * @see #setTransactionTimeout
    */
    virtual long getTransactionTimeout() const { return fTransactionTimeout; }

    //@}


    // -----------------------------------------------------------------------
    /** @name Setter methods */
    //@{

  /**
    * Set the proxy address.
    *
    * @param proxyAddressStr The proxy address to force.
    */
    virtual void setProxyAddress(std::string const proxyAddressStr)
	{
		fProxyAddress = proxyAddressStr;
	}

  /**
    * Set the proxy port.
    *
    * @param proxyPort The proxy port to force.
    */
    virtual void setProxyPort(int proxyPort)
	{
		fProxyPort = proxyPort;
	}


  /**
    * Set the proxy user id.
    *
    * @param proxyUserId The proxy user id as a string.
    * @see #getProxyUserId
    */
    virtual void setProxyUserId(std::string const proxyUserId)
	{
		fProxyUserId = proxyUserId;
		setAuthenticated(true);
	}

  /**
    * Set the proxypassword.
    *
    * @param proxyPassword The proxy password as a string.
    * @see #getProxyPassword
    */
    virtual void setProxyPassword(std::string const proxyPassword)
	{
		fProxyPassword = proxyPassword;
		setAuthenticated(true);
	}

  /**
    * Set the authenticated.
    *
    * @param b The boolean value.
    * @see #isAuthenticated
    */
	virtual void setAuthenticated(bool b)
	{
		authenticated = b;
	}

  /**
    * Set the connect timeout.
    *
    * @param timeout the timeout duration in milliseconds.
    * @see #getConnectTimeout
    */
    virtual void setConnectTimeout(long timeout)
	{
		fConnectTimeout = timeout;
	}

  /**
    * Set the transaction timeout.
    *
    * @param timeout the timeout duration in milliseconds.
    * @see #getTransactionTimeout
    */
    virtual void setTransactionTimeout(long timeout)
	{
		fTransactionTimeout = timeout;
	}

    //@}

private:

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
    std::string    fProxyAddress;
	int            fProxyPort;
    std::string    fProxyUserId;
    std::string    fProxyPassword;
	bool authenticated;

    long fConnectTimeout;           /// Connection timeout in ms
    long fTransactionTimeout;       /// Transaction timeout in ms
};



WSDL_NAMESPACE_END

#endif
