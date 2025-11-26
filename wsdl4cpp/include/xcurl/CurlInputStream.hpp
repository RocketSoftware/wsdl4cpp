/*
 * Copyright 1999-2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 * $Id: CurlInputStream.cpp 179465 2005-06-01 23:54:46Z jberry $
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * Written by Ming Zhu, Jan 2007
 * 
 */
/*
 * (c) 2025 Rocket Software, Inc. or its affiliates
 */

#if !defined(CURLINPUTSTREAM_HPP)
#define CURLINPUTSTREAM_HPP

#ifndef  _MSC_VER
#undef WIN32
#undef _WIN32
#endif

#include <curl/curl.h>
#include <curl/multi.h>
#include <curl/easy.h>

#include <xercesc/util/XMLURL.hpp>
#include <xercesc/util/XMLExceptMsgs.hpp>
#include <xercesc/util/Janitor.hpp>
#include <xercesc/util/BinInputStream.hpp>
#include <xercesc/util/XMLNetAccessor.hpp>

#include "wsdl/wsdlbas.hpp"
#include "wsdl/InputSourceEnv.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN


//
// This class implements the BinInputStream interface specified by the XML
// parser.
//

class WSDL_EXPORT CurlInputStream : public XERCES_CPP_NAMESPACE_QUALIFIER BinInputStream
{
public :
    CurlInputStream(const XMLURL&  urlSource
		, const XMLNetHTTPInfo* httpInfo=0
		, const InputSourceEnvPtr isePtr = (InputSourceEnvPtr)0 );
    ~CurlInputStream();

    XMLFilePos curPos() const;
    XMLSize_t readBytes
    (
                XMLByte* const  toFill
        , const XMLSize_t    maxToRead
    );

	const XMLCh* getContentType() const;

private :
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    CurlInputStream(const CurlInputStream&);
    CurlInputStream& operator=(const CurlInputStream&);
    
    static size_t staticWriteCallback(char *buffer,
                                      size_t size,
                                      size_t nitems,
                                      void *outstream);
    size_t writeCallback(			  char *buffer,
                                      size_t size,
                                      size_t nitems);


    // -----------------------------------------------------------------------
    //  Private data members
    //
    //  fSocket
    //      The socket representing the connection to the remote file.
    //  fBytesProcessed
    //      Its a rolling count of the number of bytes processed off this
    //      input stream.
    //  fBuffer
    //      Holds the http header, plus the first part of the actual
    //      data.  Filled at the time the stream is opened, data goes
    //      out to user in response to readBytes().
    //  fBufferPos, fBufferEnd
    //      Pointers into fBuffer, showing start and end+1 of content
    //      that readBytes must return.
    // -----------------------------------------------------------------------
	
    CURLM*				fMulti;
    CURL*				fEasy;
    
    MemoryManager*      fMemoryManager;
    
    XMLURL				fURLSource;
    ArrayJanitor<char>	fURL;
    
    unsigned long       fTotalBytesRead;
    XMLByte*			fWritePtr;
    unsigned long		fBytesRead;
    unsigned long		fBytesToRead;
    bool				fDataAvailable;
    
    // Overflow buffer for when curl writes more data to us
    // than we've asked for.
    XMLByte				fBuffer[CURL_MAX_WRITE_SIZE];
    XMLByte*			fBufferHeadPtr;
    XMLByte*			fBufferTailPtr;
    
    char*			    fErrorBuf;

	std::string fUserPasswordBuffer;
    
}; // CurlInputStream


inline XMLFilePos
CurlInputStream::curPos() const
{
    return fTotalBytesRead;
}
inline const XMLCh*
CurlInputStream::getContentType() const 
{
	return 0;
}

WSDL_NAMESPACE_END

#endif // CURLINPUTSTREAM_HPP

