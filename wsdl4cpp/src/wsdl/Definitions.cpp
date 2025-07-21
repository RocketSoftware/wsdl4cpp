/*
 * %fv:Definitions.cpp-8 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 * 
 * History:
 * 
 * revision  date    refnum    version  who  description
 * --------------------------------------------------------------------------
 * 01-05     060509            9.SOAP   mzu  Migrated from WSDL4J
 * 06        060704  cr24024   9.SOAP   mzu  Add method isBasicTypesReady
 * --------------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 * 
 */
#include "wsdl/wsdlxerces.hpp"
#include <sstream>
#include <string>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/XMLUniDefs.hpp>
#include "wsdl/Definitions.hpp"
#include "wsdl/Constants.hpp"
#include "wsdl/schema/SchemaConstants.hpp"
#include "wsdl/util/StringUtils.hpp"

USING_STD
XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

const XMLCh Definitions::DEFAULT_SOAPENC_BASE_URI[] = // "."
{
    chPeriod
    //, chForwardSlash
    , chNull
};

XMLChString Definitions::getSOAPEncBaseURI() const
{
    return soapEncBaseURI;
}

void Definitions::setSOAPEncBaseURI(XMLChString uri)
{
    soapEncBaseURI = uri;
}

Definitions::Definitions()
    : soapEncBaseURI(DEFAULT_SOAPENC_BASE_URI)
    , mNamespaceMap(new XMLChString::XMLStrMap())
    , imports(new Import::ListMap())
    , importsOfTypes(new Import::List())
    , typeDefinitionIncluded(false)
    , mMessageMap(new Message::Map())
    , mPortTypeMap(new PortType::Map())
    , mBindingMap(new Binding::Map())
    , mServiceMap(new Service::Map())
    , mArrayTypeMap(new ArrayTypeInfo::Map())
{
}

Definitions::~Definitions()
{
}

ImportPtr Definitions::createImport() 
{
     return (ImportPtr)new Import(); 
}

void Definitions::addImport(ImportPtr importDef)
{ 
    XMLChString namespaceURI = importDef->getNamespaceURI();
    
    Import::ListMap::iterator listIt = imports->find(namespaceURI);
    if (listIt == imports->end())
    {
        listIt = imports->insert(Import::ListMap::value_type(
            namespaceURI, (Import::ListPtr)new Import::List())).first;
    }

    listIt->second->push_back(importDef);
    
    DefinitionsPtr def = importDef->getDefinition();
    if ( def && def->isTypeDefinitionIncluded() )
    {
        importsOfTypes->push_back(importDef);
        typeDefinitionIncluded = true;
    }
}

Import::ListPtr Definitions::getImports(XMLChString namespaceURI) 
{
    Import::ListMap::iterator i = imports->find(namespaceURI);
    return (i == imports->end()) ? Import::ListPtr(0) : i->second; 
}
    
XMLChString Definitions::getTagName() 
{
    return toXmlStr("definitions");
}

NamedElementPtr Definitions::getFromImports(XMLChString typeOfDefinition, QNamePtr name)
{
    NamedElementPtr ret;
    Import::ListPtr importList = getImports(name->getNamespaceURI());

    if ( importList )
    {
 
      for (Import::List::iterator importIterator = importList->begin(), itEnd = importList->end(); 
            importIterator != itEnd; importIterator++ )
      {
        ImportPtr importDef = *importIterator;

        if (importDef)
        {
          DefinitionsPtr importedDef = importDef->getDefinition();
    
          if (importedDef)
          {
            /*
              These object comparisons will work fine because
              this private method is only called from within
              this class, using only the pre-defined constants
              from the Constants class as the typeOfDefinition
              argument.
            */
            if (typeOfDefinition == Constants::ELEM_SERVICE)
            {
                ret = importedDef->getService(name);
				//importedDef = ret.downcastTo<Definitions>();
                //ret.downcastTo<Import>();
            }
            else if (typeOfDefinition == Constants::ELEM_MESSAGE)
            {
              ret = importedDef->getMessage(name);
            }
            else if (typeOfDefinition == Constants::ELEM_BINDING)
            {
              ret = importedDef->getBinding(name);
            }
            else if (typeOfDefinition == Constants::ELEM_PORT_TYPE)
            {
              ret = importedDef->getPortType(name);
            }

            if (ret)
            {
              return ret;
            }
          }
        }
      }
    }

    return ret;
}

XSTypeDefinitionPtr Definitions::getTypeFromImports(QNamePtr typeQName)
{
    XSTypeDefinitionPtr typeDef;

    if ( importsOfTypes )
    {
 
      for (Import::List::iterator importIterator = importsOfTypes->begin(), itEnd = importsOfTypes->end(); 
            importIterator != itEnd; importIterator++ )
      {
          ImportPtr importDef = *importIterator;

          if (importDef)
          {
              DefinitionsPtr importedDef = importDef->getDefinition();
    
              if (importedDef)
              {
            
                  typeDef = importedDef->getType(typeQName);

                  if (typeDef)
                  {
                       break;
                  }
              }
          }
      }
    }

    return typeDef;
}

XSElementDeclarationPtr Definitions::getElementDecFromImports(QNamePtr elementQName)
{
    XSElementDeclarationPtr elementDec;

    if ( importsOfTypes )
    {
 
      for (Import::List::iterator importIterator = importsOfTypes->begin(), itEnd = importsOfTypes->end(); 
            importIterator != itEnd; importIterator++ )
      {
          ImportPtr importDef = *importIterator;

          if (importDef)
          {
              DefinitionsPtr importedDef = importDef->getDefinition();
    
              if (importedDef)
              {
            
                  elementDec = importedDef->getElementDeclaration(elementQName);

                  if (elementDec)
                  {
                       break;
                  }
              }
          }
      }
    }

    return elementDec;
}

void Definitions::addServicesToList(Service::ListPtr slist)
{
    for (Service::Map::iterator si = mServiceMap->begin(), se = mServiceMap->end(); 
        si != se; si++) {
        slist->push_back(si->second);
    }

}

Service::ListPtr Definitions::getAllServices()
{
    Service::ListPtr services(new Service::List());
    addServicesToList(services);
    if (imports)
    {
      for (Import::ListMap::iterator importIterator = imports->begin(), itEnd = imports->end(); 
            importIterator != itEnd; importIterator++ )
      {
        Import::ListPtr importList = importIterator->second;
        
          for (Import::List::iterator it = importList->begin(), ie = importList->end(); 
                it != ie; it++ )
          {
            ImportPtr importDef = *it;
    
            if (importDef)
            {
              DefinitionsPtr importedDef = importDef->getDefinition();
        
              if (importedDef)
              {
                importedDef->addServicesToList(services);
              }
            }
          }
      }
    }

    return services;
}

XMLChString Definitions::toString()
{
	XMLChString strBuf0 = NamedElement::toString();
	
	strBuf0.append(toXmlStr(" targetNamespace="))
		.append(targetNamespace);
        
    XMLChString strBuf("");

    strBuf.append(toXmlStr("\n"));
    
    if (imports)
    {
      for (Import::ListMap::iterator importIterator = imports->begin(), itEnd = imports->end(); 
            importIterator != itEnd; importIterator++ )
      {
        Import::ListPtr importList = importIterator->second;
        
          for (Import::List::iterator it = importList->begin(), ie = importList->end(); 
                it != ie; it++ )
          {
            strBuf.append(
                toXmlStr("\n") + it->get()->toString());
          }
      }
    }

    if (mTypes)
    {
      strBuf.append(toXmlStr("\n") + mTypes->toString());
    }


	// Add message information
	for (Message::Map::iterator mi = mMessageMap->begin(), me = mMessageMap->end(); mi != me; mi++) {
		strBuf.append(toXmlStr("\n"))
			.append(mi->second->toString());
	}

	// Add portType information
	strBuf.append(toXmlStr("\n"));
	for (PortType::Map::iterator pi = mPortTypeMap->begin(), pe = mPortTypeMap->end(); pi != pe; pi++) {
		strBuf.append(toXmlStr("\n"))
			.append(pi->second->toString());
	}

	// Add binding information
	strBuf.append(toXmlStr("\n"));
	for (Binding::Map::iterator bi = mBindingMap->begin(), be = mBindingMap->end(); bi != be; bi++) {
		strBuf.append(toXmlStr("\n"))
			.append(bi->second->toString());
	}

	// Add service information
	strBuf.append(toXmlStr("\n"));
	for (Service::Map::iterator si = mServiceMap->begin(), se = mServiceMap->end(); si != se; si++) {
		strBuf.append(toXmlStr("\n"))
			.append(si->second->toString());
	}

	strBuf.append(toXmlStr("\n"));
//
//    if (bindings != null)
//    {
//      Iterator bindingIterator = bindings.values().iterator();
//
//      while (bindingIterator.hasNext())
//      {
//        strBuf.append("\n" + bindingIterator.next());
//      }
//    }
//
//    if (services != null)
//    {
//      Iterator serviceIterator = services.values().iterator();
//
//      while (serviceIterator.hasNext())
//      {
//        strBuf.append("\n" + serviceIterator.next());
//      }
//    }

    strBuf0.append(StringUtils::addIndent(strBuf));
    return strBuf0;
}

// @since rev06
bool Definitions::isBasicTypesReady()
{
    QNamePtr typeQName = (QNamePtr)new QName(SchemaConstants::NS_URI_XSD_2001, toXmlStr("int"));
    return (bool)(getType(typeQName));
}

WSDL_NAMESPACE_END

