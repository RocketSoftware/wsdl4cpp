/*
 * %fv:ExtensibilityAttribute.cpp-2 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
#include <xercesc/util/XMLUniDefs.hpp>
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/ext/ExtensibilityAttribute.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

const int ExtensibilityAttribute::NO_DECLARED_TYPE = -1;
const int ExtensibilityAttribute::STRING_TYPE = 0;
const int ExtensibilityAttribute::QNAME_TYPE = 1;
const int ExtensibilityAttribute::LIST_OF_STRINGS_TYPE = 2;
const int ExtensibilityAttribute::LIST_OF_QNAMES_TYPE = 3;

XMLChString ExtensibilityAttribute::toString()
{
    XMLChString strBuf("");

//    strBuf.append(getTagName())
//    	.append(toXmlStr(": elementType="));
//    	
    if ( type == STRING_TYPE )
    	strBuf.append(getString());
    else if ( type == QNAME_TYPE )
    	strBuf.append(getQName()->toString());
    else if ( type == LIST_OF_STRINGS_TYPE )
    {
	    for(XMLChString::List::iterator i = getStringList()->begin(), 
	    	k = getStringList()->begin(), l = getStringList()->end();
	        i != l; i++)
	    {
	    	if ( i != k )
    	        strBuf.append(1, chSpace);
    	    strBuf.append(*i);
	    }
    }
    else if ( type == LIST_OF_QNAMES_TYPE )
    {
	    for(QName::List::iterator i = getQNameList()->begin(), 
	    	k = getQNameList()->begin(), l = getQNameList()->end();
	        i != l; i++)
	    {
	    	if ( i != k )
    	        strBuf.append(1, chSpace);
    	    strBuf.append((*i)->getLocalPart());
	    }
    }

    return strBuf;
}

template <typename T> T* newinstance()
{
    return new T();
}

WSDL_NAMESPACE_END

