/*
 * %fv:SchemaModel.hpp-5 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * History:
 * 
 * revision  date    refnum    version  who  description
 * --------------------------------------------------------------------------
 * 01        060713            9.SOAP   mzu  First draft
 * 02        060713  t85128    9.SOAP   mzu  Change for xml schema cross-reference
 * --------------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 * 
 */
#ifndef SCHEMAMODEL_HPP_
#define SCHEMAMODEL_HPP_
#include "wsdl/wsdlbas.hpp"
#include "wsdl/schema/SchemaXercesc.hpp"

WSDL_NAMESPACE_BEGIN

class SchemaModel;

DEFINE_PTR(SchemaModel);

class WSDL_EXPORT SchemaModel
{
public:
    SchemaModel(XERCES_CPP_NAMESPACE_QUALIFIER XMLGrammarPool* grammarPool = 0);
    virtual ~SchemaModel();
    
	virtual XSElementDeclarationPtr getElementDeclaration(QNamePtr elementQName);
    virtual XSTypeDefinitionPtr getTypeDefinition(QNamePtr typeQName); //@rev02
    
    virtual XMLGrammarPoolPtr getGrammarPool() { return mGrammarPool; }
    virtual void setGrammarPool(XMLGrammarPoolPtr grammarPool);
    
    virtual XSModelPtr getModel();
    
    virtual XMLChString toString();
    
    static XMLChString typeDefToString(XSTypeDefinitionPtr typeDef);

protected:
    XMLGrammarPoolPtr mGrammarPool;
    XSModelPtr mModel;
    XERCES_CPP_NAMESPACE_QUALIFIER XSNamedMap<XERCES_CPP_NAMESPACE_QUALIFIER XSObject>* mTypeMap;
    XERCES_CPP_NAMESPACE_QUALIFIER XSNamedMap<XERCES_CPP_NAMESPACE_QUALIFIER XSObject>* mElementMap;

    virtual XERCES_CPP_NAMESPACE_QUALIFIER XSNamedMap<XERCES_CPP_NAMESPACE_QUALIFIER XSObject>* getElementDeclarations();
    virtual XERCES_CPP_NAMESPACE_QUALIFIER XSNamedMap<XERCES_CPP_NAMESPACE_QUALIFIER XSObject>* getTypes();
};


WSDL_NAMESPACE_END

#endif /*SCHEMAMODEL_HPP_*/
