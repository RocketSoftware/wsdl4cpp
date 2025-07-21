/*
 * Created by Ming Zhu, 2007-01
 * 
 */

/*
 * $Id:$
 */


#ifndef INPUTSOURCEENV_HPP
#define INPUTSOURCEENV_HPP

#include <string>
#include <xercesc/util/PlatformUtils.hpp>

#include "wsdl/wsdlbas.hpp"

XERCES_CPP_NAMESPACE_USE

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
	InputSourceEnv() : authenticated(false){};

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
    * @see Locator#getProxyUserId
    * @see SAXParseException#getProxyUserId
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
    * @see Locator#getProxyPassword
    * @see SAXParseException#getProxyPassword
    */
    virtual void setProxyPassword(std::string const proxyPassword)
	{
		fProxyPassword = proxyPassword;
		setAuthenticated(true);
	}

	/**
	 */
	virtual bool isAuthenticated()
	{
		return authenticated;
	}

	virtual void setAuthenticated(bool b)
	{
		authenticated = b;
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
};



WSDL_NAMESPACE_END

#endif
