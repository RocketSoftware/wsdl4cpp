/*
 * %fv:Definitions.hpp-11 % 
 * 
 * Written by Ming Zhu (ming.zhu@nl.compuware.com), March 2006
 * 
 * (c) Copyright Compuware Corp 2007
 * 
 * WSDL4CPP is a C++ translation of WSDL4J.
 * WSDL4J is an open source toolkit (See "http://sourceforge.net/projects/wsdl4j")
 * under the Common Public License Version 1.0
 */
/*
 * From release 1.0.0, WSDL4CPP is under the Eclipse Public License - v 2.0 (EPL 2.0)
 * 
 * History:
 * 
 * revision  date    refnum    version  who  description
 * -----------------------------------------------------------------------
 * 01-05     060509            9.SOAP   mzu  Migrated from WSDL4J
 * 06        060704  cr24024   9.SOAP   mzu  Add method isBasicTypesReady
 * 07        060713  cr24024   9.SOAP   mzu  Improved typeDefinitionIncluded handling
 * 08        060713  t85128    9.SOAP   mzu  Follow the method change in class Types
 * 09        070109  t85163    9.SOAP   mzu  Better format
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 * 
 */
#ifndef DEFINITIONS_HPP_
#define DEFINITIONS_HPP_
#include <xercesc/util/XercesDefs.hpp>

#include "wsdl/wsdlbas.hpp"
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/Binding.hpp"
#include "wsdl/BindingFault.hpp"
#include "wsdl/BindingInput.hpp"
#include "wsdl/BindingOperation.hpp"
#include "wsdl/BindingOutput.hpp"
#include "wsdl/Import.hpp"
#include "wsdl/Message.hpp"
#include "wsdl/Operation.hpp"
#include "wsdl/Part.hpp"
#include "wsdl/Port.hpp"
#include "wsdl/PortType.hpp"
#include "wsdl/Service.hpp"
#include "wsdl/QName.hpp"
#include "wsdl/NamedElement.hpp"
#include "wsdl/Fault.hpp"
#include "wsdl/Input.hpp"
#include "wsdl/Output.hpp"
#include "wsdl/Types.hpp"
#include "wsdl/ext/ExtensibilityElement.hpp"
#include "wsdl/ext/ExtensionRegistry.hpp"
#include "wsdl/util/ArrayTypeInfo.hpp"

WSDL_NAMESPACE_BEGIN

/**
 * This class represents a WSDL definition.
 * @author  Ming Zhu (ming.zhu@nl.compuware.com)
 * @version %v:%, rev07
 */
class WSDL_EXPORT Definitions
    : public NamedElement
    , public ElementExtensible
{

public:
	Definitions();
	virtual ~Definitions();
	
    static const XMLCh DEFAULT_SOAPENC_BASE_URI[];
    /**
     * Returns the base URI of the soapencoding.xsd.
     * @return the base URI of the soapencoding.xsd.
     */
    virtual XMLChString getSOAPEncBaseURI() const;

    /**
     * Set the base URI of the soapencoding.xsd.
     * @param uri the base URI of the soapencoding.xsd.
     */
    virtual void setSOAPEncBaseURI(XMLChString uri);

	virtual void addNamespace(XMLChString prefix, XMLChString namespaceURI)
    { 
        mNamespaceMap->insert(XMLChString::XMLStrMap::value_type(
            prefix, namespaceURI));
    }
	virtual XMLChString getNamespace(XMLChString prefix) 
	{
		XMLChString::XMLStrMap::iterator i = mNamespaceMap->find(prefix);
		if (i == mNamespaceMap->end()) return null;
		return i->second; 
	}
	
    virtual ImportPtr createImport();
    virtual void addImport(ImportPtr importDef);
    virtual Import::ListPtr getImports(XMLChString namespaceURI) ;
    
    virtual TypesPtr createTypes() { return (TypesPtr)new Types(); }
    virtual TypesPtr getTypes() { return mTypes; }
    virtual void setTypes(TypesPtr ts)
    { 
        mTypes = ts;
        if ( ts && ts->isSchemaDefined() ) // rev07
        {
            typeDefinitionIncluded = true;
        }
    }
    
    /**
     * Returns true if and only if this definition or its imported
     * definition includes type definition. 
     * <p>This method is an extension of WSDL4C to WSDL4J.
     * 
     * @return true if and only if this definition includes type definition.
     */
    virtual bool isTypeDefinitionIncluded() { return typeDefinitionIncluded; }
    
    /**
     * Get the element decliaration of the specified type. 
     * <p>This method is an extension of WSDL4C to WSDL4J.
     * 
     * @param typeQName the qualified name of element.
     * @return the element decliaration.
     */
    virtual XSElementDeclarationPtr getElementDeclaration(QNamePtr elementQName)
    {
        XSElementDeclarationPtr elementDec;
        
        if ( mTypes )
        {
            elementDec = mTypes->getElementDeclaration(elementQName);
        }
        
        if ( !elementDec )
        {
            elementDec = getElementDecFromImports(elementQName);
        }
        return elementDec;
    }
    
    /**
     * Get the type definition of the specified type.
     * <p>This method is an extension of WSDL4C to WSDL4J.
     * 
     * @param typeQName the qualified name of type.
     * @return the type definition.
     */
    virtual XSTypeDefinitionPtr getType(QNamePtr typeQName)
    {
        XSTypeDefinitionPtr typeDef;
        
        if ( mTypes )
        {
            typeDef = mTypes->getTypeDefinition(typeQName); //@rev08
        }
        
        if ( !typeDef )
        {
            typeDef = getTypeFromImports(typeQName);
        }
        return typeDef;
    }
    
	virtual BindingPtr createBinding() { return (BindingPtr)new Binding(); }
	virtual void addBinding(BindingPtr aBinding)
    { 
        mBindingMap->insert(Binding::Map::value_type(
            aBinding->getQName(), aBinding));
    }
	virtual BindingPtr getBinding(QNamePtr name) 
	{
		Binding::Map::iterator i = mBindingMap->find(name);
		if ( i == mBindingMap->end() ) 
		{
			NamedElementPtr nePtr(getFromImports(Constants::ELEM_BINDING, name));
			return nePtr.downcastTo<Binding>();
		}
		else
		{
			return i->second;
		}
		
	}
	
	virtual MessagePtr createMessage() { return (MessagePtr)new Message(); }
	virtual void addMessage(MessagePtr msg)
    { 
        mMessageMap->insert(Message::Map::value_type(
            msg->getQName(), msg));
    }
	virtual MessagePtr getMessage(QNamePtr name) 
	{
		Message::Map::iterator i = mMessageMap->find(name);
		if ( i == mMessageMap->end() ) 
		{
			NamedElementPtr nePtr(getFromImports(Constants::ELEM_MESSAGE, name));
			return nePtr.downcastTo<Message>();
		}
		else
		{
			return i->second;
		}
	}
	
	virtual PortTypePtr createPortType() { return (PortTypePtr)new PortType(); }
	
	virtual void addPortType(PortTypePtr pt)
    { 
        mPortTypeMap->insert(PortType::Map::value_type(
            pt->getQName(), pt));
    }
	virtual PortTypePtr getPortType(QNamePtr name) 
	{
		PortType::Map::iterator i = mPortTypeMap->find(name);
		if ( i == mPortTypeMap->end() ) 
		{
			NamedElementPtr nePtr(getFromImports(Constants::ELEM_PORT_TYPE, name));
			return nePtr.downcastTo<PortType>();
		}
		else
		{
			return i->second;
		}
	}
	
	virtual ServicePtr createService() { return (ServicePtr)new Service(); }
	virtual void addService(ServicePtr aService)
    { 
        mServiceMap->insert(Service::Map::value_type(
            aService->getQName(), aService));
    }
    
    /**
     * Get the specified service. Also checks imported documents.
     *
     * @param name the name of the desired service.
     * @return the corresponding service, or null if there wasn't
     * any matching service
     */
	virtual ServicePtr getService(QNamePtr name) 
	{
		Service::Map::iterator i = mServiceMap->find(name);

		if ( i == mServiceMap->end() ) 
		{
			NamedElementPtr nePtr(getFromImports(Constants::ELEM_SERVICE, name));
			return nePtr.downcastTo<Service>();
		}
		else
		{
			return i->second;
		}
	}
	
    virtual XMLChString::XMLStrMapPtr getNamespaces() { return mNamespaceMap; }
    
    virtual Binding::MapPtr getBindings() { return mBindingMap; }
    virtual Import::ListMapPtr getImports() { return imports; }
    virtual Message::MapPtr getMessages() { return mMessageMap; }
    virtual PortType::MapPtr getPortTypes() { return mPortTypeMap; }
    
    /**
     * Get all the services defined here.
     */
    virtual Service::MapPtr getServices() { return mServiceMap; }
    
    /**
     * Get all the services defined here and in all imported documents.
     */
    virtual Service::ListPtr getAllServices();

	virtual PartPtr createPart() { return (PartPtr)new Part(); }
	virtual OperationPtr createOperation() { return (OperationPtr)new Operation(); }
    virtual InputPtr createInput() { return (InputPtr)new Input(); }
    virtual OutputPtr createOutput() { return (OutputPtr)new Output(); }
    virtual FaultPtr createFault() { return (FaultPtr)new Fault(); }
    virtual PortPtr createPort() { return (PortPtr)new Port(); }
    
    virtual BindingOperationPtr createBindingOperation() { return (BindingOperationPtr)new BindingOperation(); }
    virtual BindingInputPtr createBindingInput() { return (BindingInputPtr)new BindingInput(); }
    virtual BindingOutputPtr createBindingOutput() { return (BindingOutputPtr)new BindingOutput(); }
    virtual BindingFaultPtr createBindingFault() { return (BindingFaultPtr)new BindingFault(); }
	
	virtual XMLChString getTargetNamespace() { return targetNamespace; }
	virtual void setTargetNamespace(XMLChString tns) { targetNamespace = tns; }
	
	virtual XMLChString getDocumentBaseURI() { return documentBaseURI; }
	virtual void setDocumentBaseURI(XMLChString uri) { documentBaseURI = uri;}

    virtual ExtensionRegistryPtr getExtensionRegistry() { 
        return mExtensionRegistry; }
    virtual void setExtensionRegistry(ExtensionRegistryPtr er) { mExtensionRegistry = er; }
    
	virtual XMLChString toString();
	
private:

    XMLChString soapEncBaseURI;
	XMLChString documentBaseURI;
	XMLChString targetNamespace;
    
    ExtensionRegistryPtr mExtensionRegistry;
	
	XMLChString::XMLStrMapPtr mNamespaceMap;
    
    Import::ListMapPtr imports;
    Import::ListPtr importsOfTypes;
    
    bool typeDefinitionIncluded;
    TypesPtr mTypes;
	
	Message::MapPtr mMessageMap;
	PortType::MapPtr mPortTypeMap;
    
    Binding::MapPtr mBindingMap;
    
	Service::MapPtr mServiceMap;

	virtual XMLChString getTagName();
    virtual NamedElementPtr getFromImports(XMLChString typeOfDefinition, QNamePtr name);
    
    virtual XSElementDeclarationPtr getElementDecFromImports(QNamePtr elementQName);
    virtual XSTypeDefinitionPtr getTypeFromImports(QNamePtr typeQName);
    
    virtual void addServicesToList(Service::ListPtr slist);

public:
    virtual void addArrayTypeInfo(ArrayTypeInfoPtr info)
    { 
        mArrayTypeMap->insert(ArrayTypeInfo::Map::value_type(
            info->getType(), info));
    }
    virtual ArrayTypeInfoPtr getArrayTypeInfo(QNamePtr name) 
    {
        ArrayTypeInfo::Map::iterator i = mArrayTypeMap->find(name);
        return (i == mArrayTypeMap->end()) ? 
            (ArrayTypeInfoPtr)0 : i->second; 
    }
    
    /**
     * Check if the basic XML Schema types are ready.
     * @since rev06
     */
    virtual bool isBasicTypesReady();
    
private:

    ArrayTypeInfo::MapPtr mArrayTypeMap;

};

WSDL_NAMESPACE_END

#endif /*DEFINITIONS_HPP_*/
