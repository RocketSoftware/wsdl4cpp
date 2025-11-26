/*
 * %fv:StringUtils.hpp-3 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * (c) 2025 Rocket Software, Inc. or its affiliates
 * 
 * WSDL4CPP is under the Eclipse Public License version 2.0 (EPL2.0).
 * It is a C++ translation of WSDL4J (an open source toolkit, see
 * "http://sourceforge.net/projects/wsdl4j").
 */
#ifndef STRINGUTILS_HPP_
#define STRINGUTILS_HPP_

#include "wsdl/wsdlbas.hpp"
#include "wsdl/wsdlxerces.hpp"

WSDL_NAMESPACE_BEGIN

class WSDL_EXPORT StringUtils
{
public:
    static const XMLCh DEFAULT_INDENT[];
    
	StringUtils(){};
	virtual ~StringUtils(){};
	
    static XMLChString getURI(XMLChString baseURI, XMLChString relativeURI);

    static XMLChString::ListPtr parseNMTokens(XMLChString nmTokens);

    static XMLChString addIndent(XMLChString s, XMLChString indent = DEFAULT_INDENT);
};

WSDL_NAMESPACE_END

#endif /*STRINGUTILS_HPP_*/
