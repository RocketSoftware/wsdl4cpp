/*
 * %fv:DOMUtils.cpp-5 % 
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
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>

#include "wsdl/wsdlxerces.hpp"
#include "wsdl/util/DOMUtils.hpp"

USING_STD

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

// "xmlns"
const XMLCh* DOMUtils::ATTR_XMLNS = XMLUni::fgXMLNSString;

// "http://www.w3.org/2000/xmlns/"
const XMLCh* DOMUtils::NS_URI_XMLNS = XMLUni::fgXMLNSURIName;
 
DOMUtils::DOMUtils()
{
}

DOMUtils::~DOMUtils()
{
}

bool DOMUtils::matches(QNamePtr qname, DOMNode* node)
{
    return (node && qname->compare(newQName(node)) == 0);
}

QNamePtr DOMUtils::newQName(DOMNode* node)
{
    if (node)
    {
        return (QNamePtr)new QName(node->getNamespaceURI(), node->getLocalName());
    }
    else
    {
        return (QNamePtr)0;
    }
}

DOMElement* DOMUtils::getFirstChildElement (DOMElement* elem)
{
    for (DOMNode* n = elem->getFirstChild (); n; n = n->getNextSibling ()) {
        if (n->getNodeType () == DOMNode::ELEMENT_NODE) {
        	return (DOMElement*)n;
        }
    }
    return 0;
}

DOMElement* DOMUtils::getNextSiblingElement (DOMElement* elem)
{
    for (DOMNode* n = elem->getNextSibling (); n; n = n->getNextSibling ()) {
        if (n->getNodeType () == DOMNode::ELEMENT_NODE) {
            return (DOMElement*) n;
        }
    }
    return 0;
}

XMLChString DOMUtils::getAttribute (DOMElement* el, const XMLCh* attrName)
	
{
    DOMAttr* attr = el->getAttributeNode(attrName);

    if (attr) {
        return attr->getValue();
    }
    
    return null;
}

XMLChString DOMUtils::getAttributeNS (DOMElement* el,
                                       const XMLCh* namespaceURI,
                                       const XMLCh* localPart) 
	
{
    DOMAttr* attr = el->getAttributeNodeNS (namespaceURI, localPart);

    if (attr) {
        return attr->getValue();
    }

    return null;
}

DOMUtils::AttrPtrListPtr DOMUtils::getAttributes (DOMElement* el) {
    AttrPtrListPtr attrs(new AttrPtrList());
    
    DOMNamedNodeMap* attrMap = el->getAttributes();
    
    for (XMLSize_t i = 0, size = attrMap->getLength(); i < size; i++)
    {
		DOMAttr* attr = (DOMAttr*)attrMap->item(i);
        const XMLCh* nodename = attr->getNodeName();
        const XMLCh* prefix = attr->getPrefix();
      
        if ( XMLString::equals(ATTR_XMLNS, nodename) 
      		|| XMLString::equals(ATTR_XMLNS, prefix))
        {
	        //ignore namespace declarations
	        continue;
        }
        else
        {
	        attrs->push_back(attr);  
	    }
    }
      
    return attrs;
}

XMLChString DOMUtils::getAttribute (DOMElement* el, const XMLCh* attrName, 
		DOMUtils::AttrPtrListPtr remainingAttrs) 
{
    DOMAttr* attr = el->getAttributeNode(attrName);
    
    if (attr) {
        const XMLCh* sRet = attr->getValue();
        remainingAttrs->remove(attr);
	    return sRet;
    }
    return null;
}

void DOMUtils::throwWSDLException(DOMElement* location, 
		DOMUtils::AttrPtrListPtr remainingAttrs) throw(WSDLException)
{
    XMLChString elName = newQName(location)->toString();
    
    string sb;
    
    sb.append("Element '")
    	.append(toLocal(elName))
    	.append("' contained unexpected attributes: '");
    
    for (AttrPtrList::const_iterator i = remainingAttrs->begin(),
    	end = remainingAttrs->end(); i != end; i++)
    {
        XMLChString attrName = newQName((DOMAttr*)&(*i))->toString();
      
        sb.append(toLocal(attrName));
        sb.append( i != end ? " " : "");
    }
    
    sb.append("'");

    WSDLException wsdlExc(WSDLException::INVALID_WSDL, sb);

    //TODO: wsdlExc.setLocation(XPathUtils.getXPathExprFromNode(location));

    throw wsdlExc;
  }

void DOMUtils::throwWSDLException(DOMElement* location) throw(WSDLException)
{
    XMLChString elName = newQName(location)->toString();
    
    string sb;
    
    sb.append("Encountered unexpected element '")
    	.append(toLocal(elName))
    	.append("'.");
    
    WSDLException wsdlExc(WSDLException::INVALID_WSDL, sb);

    //TODO: wsdlExc.setLocation(XPathUtils.getXPathExprFromNode(location));

    throw wsdlExc;
  }

QNamePtr DOMUtils::getQualifiedAttributeValue(DOMElement* el,
     const XMLCh* attrName,
     const XMLCh* elDesc,
     bool isRequired,
     DefinitionsPtr def,
     AttrPtrListPtr remainingAttrs
)
       throw(WSDLException)
{
    XMLChString attrValue = DOMUtils::getAttribute(
							el, attrName, remainingAttrs);
    
	if ( attrValue != null )
	return getQName(attrValue, el, def);

    if (isRequired)
    {
    	string msg;
    	
        WSDLException wsdlExc(WSDLException::INVALID_WSDL,
      		string("The '").append(toLocal(attrName))
      			.append("' attribute must be specified for every ")
      			.append(toLocal(elDesc))
      			.append(" element."));

        //TODO: wsdlExc.setLocation(XPathUtils.getXPathExprFromNode(el));

        throw wsdlExc;
    }
    else
    {
        return (QNamePtr)0;
    }

}

QNamePtr DOMUtils::getQualifiedAttributeValue(DOMElement* el,
     const XMLCh* attrName,
     const XMLCh* elDesc,
     bool isRequired,
     DefinitionsPtr def
)
       throw(WSDLException)
{
    XMLChString attrValue = DOMUtils::getAttribute(el, attrName);

	if ( attrValue != null )
    return getQName(attrValue, el, def);

    if (isRequired)
    {
    	string msg;
    	
        WSDLException wsdlExc(WSDLException::INVALID_WSDL,
      		string("The '").append(toLocal(attrName))
      			.append("' attribute must be specified for every ")
      			.append(toLocal(elDesc))
      			.append(" element."));

        //TODO: wsdlExc.setLocation(XPathUtils.getXPathExprFromNode(el));

        throw wsdlExc;
    }
    else
    {
        return (QNamePtr)0;
    }

}

QNamePtr DOMUtils::getQName(XMLChString prefixedValue,
						    DOMElement* contextEl,
						    DefinitionsPtr def)
    throw(WSDLException)
{
    size_t    index        = prefixedValue.find_first_of(chColon);
    XMLChString localPart    = prefixedValue.substr(index + 1);
    
	XMLChString prefix;
	const XMLCh* prefixTemp = 0;
	if (index != XMLChString::npos ) {
		prefix = prefixedValue.substr(0, index);
		prefixTemp = prefix.c_str();
	}
 	XMLChString namespaceURI = getNamespaceURIFromPrefix(
									contextEl, prefixTemp);

	if ( namespaceURI == null ) 
	{
        string faultCode = (index == XMLChString::npos)
                         ? WSDLException::NO_PREFIX_SPECIFIED
                         : WSDLException::UNBOUND_PREFIX;
                         
        string message;
        message.append("Unable to determine namespace of '")
        		.append(toLocal(prefixedValue)).append("'.");

        WSDLException wsdlExc(faultCode, message);

        //TODO: wsdlExc.setLocation(XPathUtils.getXPathExprFromNode(contextEl));

        throw wsdlExc;
	}
	registerUniquePrefix(prefix, namespaceURI, def);

    return (QNamePtr)new QName(namespaceURI, localPart);
        
}

void DOMUtils::registerUniquePrefix(XMLChString prefix,
                                          XMLChString namespaceURI,
                                          DefinitionsPtr def)
{
    XMLChString tempNSUri = def->getNamespace(prefix);
    
    if ( tempNSUri != null && tempNSUri == namespaceURI)
    {
        return;
    }

    while ( tempNSUri != null && tempNSUri != namespaceURI )
    {
        prefix += toXmlStr("_");
        
        tempNSUri = def->getNamespace(prefix);
    }

    def->addNamespace(prefix, namespaceURI);

}

XMLChString DOMUtils::getNamespaceURIFromPrefix (
	DOMNode* context, const XMLCh* prefix) 
	
{
    short nodeType = context->getNodeType ();
    DOMNode* tempNode = 0;

    switch (nodeType)
    {
        case DOMNode::ATTRIBUTE_NODE :
        {
            tempNode = ((DOMAttr*) context)->getOwnerElement ();
            break;
        }
        case DOMNode::ELEMENT_NODE :
        {
	        tempNode = context;
	        break;
        }
        default :
        {
	        tempNode = context->getParentNode ();
	        break;
        }
    }

    while (tempNode && tempNode->getNodeType () == DOMNode::ELEMENT_NODE)
    {
        DOMElement* tempEl = (DOMElement*) tempNode;
        
        XMLChString namespaceURI = (prefix)
                ? getAttributeNS (tempEl, NS_URI_XMLNS, prefix)
                : getAttribute (tempEl, ATTR_XMLNS);
                
        if ( namespaceURI != null )
        {
            return namespaceURI;
        }
        else
        {
        	tempNode = tempEl->getParentNode ();
		}

    }

    return null;
}

WSDL_NAMESPACE_END
