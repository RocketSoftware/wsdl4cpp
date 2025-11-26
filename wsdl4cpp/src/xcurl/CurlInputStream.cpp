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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _WIN32_WCE
#include <errno.h>
//#include <unistd.h>
#include <sys/types.h>
//#include <sys/time.h>
#endif

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XMLNetAccessor.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLExceptMsgs.hpp>
#include <xercesc/util/Janitor.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/util/TranscodingException.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include "wsdl/wsdlxerces.hpp"
#include "xcurl/CurlInputStream.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

static bool performMultiCURL(CURLM* fMulti, int &runningHandles, CURLcode &curlResult);
static void multiWait(CURLM* fMulti);

CurlInputStream::CurlInputStream(const XMLURL& urlSource
								 , const XMLNetHTTPInfo* httpInfo/*=0*/
								 , const InputSourceEnvPtr isePtr/*=0*/)
      : fMulti(0)
      , fEasy(0)
      , fMemoryManager(urlSource.getMemoryManager())
      , fURLSource(urlSource)
      , fURL(0)
      , fTotalBytesRead(0)
      , fWritePtr(0)
      , fBytesRead(0)
      , fBytesToRead(0)
      , fDataAvailable(false)
      , fBufferHeadPtr(fBuffer)
      , fBufferTailPtr(fBuffer)
{
    //@b30944
    fErrorBuf = new char[CURL_ERROR_SIZE];
	fErrorBuf[0] = 0;

	// Allocate the curl multi handle
	fMulti = curl_multi_init();
	
	// Allocate the curl easy handle
	fEasy = curl_easy_init();
	
	// Get the text of the URL we're going to use
	fURL.reset(XMLString::transcode(fURLSource.getURLText(), fMemoryManager), fMemoryManager);

	//printf("Curl trying to fetch %s\n", fURL.get());

	// Set URL option
	curl_easy_setopt(fEasy, CURLOPT_URL, fURL.get());
	if ( !isePtr.isNull() ) {
		curl_easy_setopt(fEasy, CURLOPT_PROXY, isePtr->getProxyAddress());
	    curl_easy_setopt(fEasy, CURLOPT_PROXYPORT, isePtr->getProxyPort());
		if ( isePtr->isAuthenticated() )
		{
			fUserPasswordBuffer
				.append(isePtr->getProxyUserId())
				.append(":")
				.append(isePtr->getProxyPassword());
			curl_easy_setopt(fEasy, CURLOPT_PROXYUSERPWD, fUserPasswordBuffer.c_str());
			//curl_easy_setopt(fEasy, CURLOPT_PROXY, fUserPasswordBuffer.c_str());
		}

		if ( isePtr->getConnectTimeout() )
		{
			curl_easy_setopt(fEasy, CURLOPT_CONNECTTIMEOUT_MS, isePtr->getConnectTimeout());
		}
		if ( isePtr->getTransactionTimeout() )
		{
			curl_easy_setopt(fEasy, CURLOPT_TIMEOUT_MS, isePtr->getTransactionTimeout());
		}
	}

	curl_easy_setopt(fEasy, CURLOPT_SSL_VERIFYPEER, 0); // @b31150
	
//	curl_easy_setopt(fEasy, CURLOPT_READDATA, this);
//	curl_easy_setopt(fEasy, CURLOPT_READFUNCTION, staticReadCallback);

	curl_easy_setopt(fEasy, CURLOPT_WRITEDATA, this);						// Pass this pointer to write function
	curl_easy_setopt(fEasy, CURLOPT_WRITEFUNCTION, staticWriteCallback);	// Our static write function
	curl_easy_setopt(fEasy, CURLOPT_ERRORBUFFER, fErrorBuf);
	
	// @28519 Error happen for response code greater than 400;
	curl_easy_setopt(fEasy, CURLOPT_FAILONERROR, 1);

	// Add easy handle to the multi stack
	curl_multi_add_handle(fMulti, fEasy);

#if 0
	if (!fMulti)
	{
		//execute the request
		CURLcode status = curl_easy_perform(fEasy);

		if (status != CURLE_OK) //&& status != CURLE_GOT_NOTHING)
			throwException(status);
	}
#endif

#if 0
	if (m_bUseMulti)
	{
		// Add easy handle to the multi stack
		curl_multi_add_handle(fMulti, fEasy);

		int runningHandles = 1;
		while ( m_sizeInputOffset < m_strInputBuffer.length() && runningHandles != 0 )
		{
			// Ask the curl to do some work
			runningHandles = 0;

			//bool tryAgain =
			performCURL(&runningHandles);
		}
	}
#endif
}


CurlInputStream::~CurlInputStream()
{
	// Remove the easy handle from the multi stack
	if (fMulti)
		curl_multi_remove_handle(fMulti, fEasy);
	
	// Cleanup the easy handle
	curl_easy_cleanup(fEasy);
	
	// Cleanup the multi handle
	if (fMulti)
		curl_multi_cleanup(fMulti);

    if (fErrorBuf)  //@b30944
        delete[] fErrorBuf;
    fErrorBuf = 0;
}


#if 0
size_t CurlInputStream::staticReadCallback(char *buffer,
                                      size_t size,
                                      size_t nitems,
                                      void *instream)
{
	return ((CurlInputStream*)instream)->readCallback(buffer, size, nitems);
}
#endif

#if 0
size_t
CurlInputStream::readCallback(char *buffer,
                                      size_t size,
                                      size_t nitems)
{
	size_t bufferSize = size * nitems;
	size_t count = m_strInputBuffer.length() - m_sizeInputOffset;

	std::string::size_type sizeOfInputBuffer = m_strInputBuffer.length();
	if ( bufferSize < count )
	{
		count = bufferSize;
	}

	if ( count )
	{
		//count = m_strInputBuffer._Copy_s(buffer, bufferSize,
			//count, m_sizeInputOffset);
		count = m_strInputBuffer.copy(buffer, count, m_sizeInputOffset);
		m_sizeInputOffset += count;

		return count;
	}

	m_strInputBuffer = "";
	m_sizeInputOffset = 0;
	return (size_t)(-1);
}
#endif

size_t
CurlInputStream::staticWriteCallback(char *buffer,
                                      size_t size,
                                      size_t nitems,
                                      void *outstream)
{
	return ((CurlInputStream*)outstream)->writeCallback(buffer, size, nitems);
}



size_t
CurlInputStream::writeCallback(char *buffer,
                                      size_t size,
                                      size_t nitems)
{
	XMLSize_t cnt = (XMLSize_t)(size * nitems);
	XMLSize_t totalConsumed = 0;
		
	// Consume as many bytes as possible immediately into the buffer
	XMLSize_t consume = (cnt > fBytesToRead) ? fBytesToRead : cnt;
	memcpy(fWritePtr, buffer, consume);
	fWritePtr		+= consume;
	fBytesRead		+= consume;
	fTotalBytesRead	+= consume;
	fBytesToRead	-= consume;

	//printf("write callback consuming %d bytes\n", consume);

	// If bytes remain, rebuffer as many as possible into our holding buffer
	buffer			+= consume;
	totalConsumed	+= consume;
	cnt				-= consume;
	if (cnt > 0)
	{
		XMLSize_t bufAvail = (XMLSize_t)(sizeof(fBuffer) - (fBufferHeadPtr - fBuffer));
		consume = (cnt > bufAvail) ? bufAvail : cnt;
		memcpy(fBufferHeadPtr, buffer, consume);
		fBufferHeadPtr	+= consume;
		buffer			+= consume;
		totalConsumed	+= consume;
		//printf("write callback rebuffering %d bytes\n", consume);
		curl_easy_pause(fEasy, CURLPAUSE_RECV);
	}
	
	// Return the total amount we've consumed. If we don't consume all the bytes
	// then an error will be generated. Since our buffer size is equal to the
	// maximum size that curl will write, this should never happen unless there
	// is a logic error somewhere here.
	return totalConsumed;
}



XMLSize_t
CurlInputStream::readBytes(XMLByte* const    toFill
                                     , const XMLSize_t maxToRead)
{
	CURLcode curlResult = CURLE_OK;

	fBytesRead = 0;
	fBytesToRead = (maxToRead <= CURL_MAX_WRITE_SIZE) ? maxToRead : CURL_MAX_WRITE_SIZE;
	fWritePtr = toFill;

	for (bool tryAgain = true; fBytesToRead > 0 && tryAgain; )
	{
		// First, any buffered data we have available
		XMLSize_t bufCnt = (XMLSize_t)(fBufferHeadPtr - fBufferTailPtr);
		bufCnt = (bufCnt > fBytesToRead) ? fBytesToRead : bufCnt;
		if (bufCnt > 0)
		{
			memcpy(fWritePtr, fBufferTailPtr, bufCnt);
			fWritePtr		+= bufCnt;
			fBytesRead		+= bufCnt;
			fTotalBytesRead	+= bufCnt;
			fBytesToRead	-= bufCnt;

			fBufferTailPtr	+= bufCnt;
			if (fBufferTailPtr == fBufferHeadPtr)
			{
				fBufferHeadPtr = fBufferTailPtr = fBuffer;
				curl_easy_pause(fEasy, CURLPAUSE_RECV_CONT);
			}

			//printf("consuming %d buffered bytes\n", bufCnt);

			continue;
		}

		int runningHandles;

		// Ask the curl to do some work
		tryAgain = performMultiCURL(fMulti, runningHandles, curlResult);

		// If nothing is running any longer, bail out
		if (runningHandles == 0)
			break;
		
		if (curlResult != CURLE_OK)
			break;  // some error occured

		// If there is no further data to read, and we haven't
		// read any yet on this invocation, call select to wait for data
		if (!tryAgain && fBytesRead == 0)
		{
			multiWait(fMulti);
			tryAgain = true;
		}
	}

	if (curlResult != CURLE_OK)
	{
        // @b30944
        const char* errString = ( strlen(fErrorBuf) ? fErrorBuf : curl_easy_strerror(curlResult) );
        XMLChString xsCurlMsg(errString ? errString : "__Unknown__");
        XMLChString xsMsg(fURLSource.getURLText());
        XMLChString xsComma("', curl:'");

		switch (curlResult)
		{
		case CURLE_UNSUPPORTED_PROTOCOL:
			ThrowXMLwithMemMgr(MalformedURLException, XMLExcepts::URL_UnsupportedProto, fMemoryManager);
			break;

		case CURLE_COULDNT_RESOLVE_HOST:
		case CURLE_COULDNT_RESOLVE_PROXY:
			ThrowXMLwithMemMgr1(NetAccessorException,  XMLExcepts::NetAcc_TargetResolution, fURLSource.getHost(), fMemoryManager);
			break;

		case CURLE_COULDNT_CONNECT:
			ThrowXMLwithMemMgr1(NetAccessorException, XMLExcepts::NetAcc_ConnSocket, fURLSource.getURLText(), fMemoryManager);

		case CURLE_RECV_ERROR:
			ThrowXMLwithMemMgr1(NetAccessorException, XMLExcepts::NetAcc_ReadSocket, fURLSource.getURLText(), fMemoryManager);
			break;

		case CURLE_HTTP_RETURNED_ERROR:  // @28519
			ThrowXMLwithMemMgr1(NetAccessorException, XMLExcepts::File_CouldNotOpenFile, fURLSource.getURLText(), fMemoryManager);
			break;

		case CURLE_OPERATION_TIMEDOUT:  // @b30944
            xsMsg = xsMsg + xsComma + xsCurlMsg;
            ThrowXMLwithMemMgr1(NetAccessorException, XMLExcepts::NetAcc_ReadSocket, xsMsg.c_str(), fMemoryManager);
			break;

		default:
			ThrowXMLwithMemMgr1(NetAccessorException, XMLExcepts::NetAcc_InternalError, fURLSource.getURLText(), fMemoryManager);
			break;
		}
	}

	return fBytesRead;
}




static bool performMultiCURL(CURLM* fMulti, int &runningHandles, CURLcode &curlResult)
{
	bool tryAgain;

	// Ask the curl to do some work
	runningHandles = 0;
	curlResult = CURLE_OK;

	CURLMcode curlMResult = curl_multi_perform(fMulti, &runningHandles);
	tryAgain = (curlMResult == CURLM_CALL_MULTI_PERFORM);

	// Process messages from curl
	int msgsInQueue = 0;
	for (CURLMsg* msg = NULL; (msg = curl_multi_info_read(fMulti, &msgsInQueue)) != NULL; )
	{
		//printf("msg %d, %d from curl\n", msg->msg, msg->data.result);

		if (msg->msg == CURLMSG_DONE)
		{
			curlResult = msg->data.result;
			// curlResult == CURLE_OK means completed
			// the runningHandles should be dropped to 0
			if (curlResult != CURLE_OK)
			{
			    break;
			}
		}
	}

	// If nothing is running any longer, bail out
	if (runningHandles == 0)
		tryAgain = false;

	return tryAgain;
}

static void multiWait(CURLM* fMulti)
{
	// If there is no further data to read, and we haven't
	// read any yet on this invocation, call select to wait for data
	CURLMcode        merr;
	fd_set readSet;
	fd_set writeSet;
	fd_set exceptSet;
	int fdcnt;

	FD_ZERO(&readSet);
	FD_ZERO(&writeSet);
	FD_ZERO(&exceptSet);

	// get file descriptors from the transfers
	// As curl for the file descriptors to wait on
	merr = curl_multi_fdset(fMulti, &readSet, &writeSet, &exceptSet, &fdcnt);
	//if (merr)
	//	FATAL("curl_multi_fdset", curl_multi_strerror(merr));

	if (fdcnt >= 0)
	{
		struct timeval  timeout;
		int             rc;
        long l_timeout_ms = -1;

        // Get timeout first
        curl_multi_timeout(fMulti, &l_timeout_ms);
        if ( l_timeout_ms < 0 )
            l_timeout_ms = 100;

        timeout.tv_sec = l_timeout_ms/1000;
        timeout.tv_usec = (l_timeout_ms - timeout.tv_sec*1000) * 1000;

		rc = select(fdcnt + 1, &readSet, &writeSet, &exceptSet, &timeout);
		/*
		if (rc < 0)
		{
			if (errno != EINTR)
			{
			nfatal
			(
				"%s: %d: select: %s",
				__FILE__,
				__LINE__,
				strerror(errno)
			);
			// NOTREACHED
			}
		}
		if (rc > 0)
		{
			//
			// Some sockets are ready.
			//
			call_multi_immediate = 1;
		}
		*/
	}
}


WSDL_NAMESPACE_END

