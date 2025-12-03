/*
 * Written by Ming Zhu, March 2006
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
 */
/*******************************************************************************
date   refnum    version who description
070215 c25552    920101  ahn allow local absolute paths
date   refnum    version who description
*******************************************************************************/

#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/util/XMLURL.hpp>

#include "wsdl/wsdlxerces.hpp"
#include "wsdl/util/StringUtils.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

const XMLCh StringUtils::DEFAULT_INDENT[] = { chSpace, chSpace, chNull };

XMLChString StringUtils::getURI(XMLChString baseURI, XMLChString relativeURI)
{
    const XMLCh* bURI = (baseURI == null) ? 0 : baseURI.c_str();
    const XMLCh* rURI = (relativeURI == null) ? 0 : relativeURI.c_str();
    XMLURL urlTmp;
    if ( (!urlTmp.setURL(bURI, rURI, urlTmp)) ||
        (urlTmp.isRelative()) )
    {
        if (XMLPlatformUtils::isRelative(rURI))
        {
            XMLCh* tmpBuf = XMLPlatformUtils::weavePaths(bURI, rURI);
            XMLChString tempURI(tmpBuf);
            XMLString::release(&tmpBuf); //delete [] tmpBuf;
            return tempURI;
        }
        else            /* @c25552 */
            return relativeURI;
    }
    return urlTmp.getURLText();
}

XMLChString::ListPtr StringUtils::parseNMTokens(XMLChString nmTokens)
{
    XMLChString::ListPtr tokens(new XMLChString::List());
    
    XMLChString::size_type ib, ie;
    for (ib = 0 ; (ie = nmTokens.find(chSpace, ib)) != XMLChString::npos; 
        ib = ie+1 ) 
    {
        tokens->push_back(nmTokens.substr(ib, ie-ib));
    }
    
    tokens->push_back(nmTokens.substr(ib));

    return tokens;
}

XMLChString StringUtils::addIndent(XMLChString s, XMLChString indent)
{
    XMLChString strBuf("");
    XMLChString::size_type pos = 0;
    XMLChString::size_type nextPos;
    for (pos = 0; (nextPos = s.find(chLF, pos)) != XMLChString::npos; pos = nextPos + 1 )
    {
        strBuf.append(s, pos, nextPos + 1 - pos);
        strBuf.append(indent);
    }
    strBuf.append(s, pos, s.length() - pos);
    return strBuf;
}

WSDL_NAMESPACE_END
