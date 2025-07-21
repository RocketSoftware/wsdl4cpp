/*
 * %fv:SchemaModel.cpp-9 % 
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
 * 01-04     060509            9.SOAP   mzu  Migrated from WSDL4J
 * 05        060704  t83290    9.SOAP   mzu  Refactor toString() method to display
 *                                           ElementDeclarations too.
 * 06        060713  t85128    9.SOAP   mzu  Change for xml schema cross-reference
 * --------------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 * 
 */
#include "wsdl/wsdlxerces.hpp"

#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/framework/psvi/XSComplexTypeDefinition.hpp>
#include <xercesc/framework/psvi/XSParticle.hpp>
#include <xercesc/framework/psvi/XSModelGroup.hpp>
#include <xercesc/framework/psvi/XSElementDeclaration.hpp>

#include "wsdl/QName.hpp"
#include "wsdl/util/StringUtils.hpp"
#include "wsdl/schema/SchemaModel.hpp"

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

SchemaModel::SchemaModel(XMLGrammarPool* grammarPool)
//    : mGrammarPool(grammarPool)
//    , mModel(0)
//    , mTypeMap(0)
{
    setGrammarPool((XMLGrammarPoolPtr)grammarPool);
}

XSModelPtr SchemaModel::getModel()
{
    return mModel;
}

SchemaModel::~SchemaModel()
{
    //delete mGrammarPool; 
}

void SchemaModel::setGrammarPool(XMLGrammarPoolPtr grammarPool)
{
    mGrammarPool = grammarPool;
    if ( mGrammarPool )
    {
        XSModelPtr model(mGrammarPool->getXSModel(), mGrammarPool);
        mModel = model;
        if ( mModel )
        {
            mTypeMap = mModel->getComponents(XSConstants::TYPE_DEFINITION);
			mElementMap = mModel->getComponents(XSConstants::ELEMENT_DECLARATION);
        }
    }
}

XSNamedMap<XSObject>* SchemaModel::getTypes()
{
    return mTypeMap;
}

XSNamedMap<XSObject>* SchemaModel::getElementDeclarations()
{
    return mElementMap;
}

//@rev06: changed name from getType to this.
XSTypeDefinitionPtr SchemaModel::getTypeDefinition(QNamePtr typeQName)
{
	XSTypeDefinition* p = 0;
	if ( typeQName )
	{
		p = (XSTypeDefinition*)getTypes()->itemByName(
        typeQName->getNamespaceURI().c_str(), typeQName->getLocalPart().c_str());
		return XSTypeDefinitionPtr(p, mGrammarPool);
	}
	else
	{
		return XSTypeDefinitionPtr();
	}
}

XSElementDeclarationPtr SchemaModel::getElementDeclaration(QNamePtr elementQName)
{
    XSElementDeclarationPtr elementDec((XSElementDeclaration*)getElementDeclarations()->itemByName(
        elementQName->getNamespaceURI().c_str(), elementQName->getLocalPart().c_str()), mGrammarPool);
    return elementDec;
}

XMLChString SchemaModel::toString()
{
    XMLChString strBuf(toXmlStr("\nTypes: "));
    
    XSNamedMap<XSObject>* map = getTypes();
    int i,l;
    for ( i = 0, l= map ? map->getLength() : 0; i<l; i++)
    {
        XSObject* xsobj = map->item(i);
        XSTypeDefinition* xsDef = (XSTypeDefinition*)xsobj;
        QNamePtr qname(new wsdl::QName(xsDef->getNamespace(), xsDef->getName()));
        strBuf.append(toXmlStr("\n")).append(qname->toString());
    }
    
    //Added since rev05
    strBuf.append(toXmlStr("\nElement declarations: "));
    map = getElementDeclarations();
    for ( i = 0, l= map ? map->getLength() : 0; i<l; i++)
    {
        XSObject* xsobj = map->item(i);
        XSElementDeclaration* xeDec = (XSElementDeclaration*)xsobj;
        QNamePtr qname(new wsdl::QName(xeDec->getNamespace(), xeDec->getName()));
        strBuf.append(toXmlStr("\n")).append(qname->toString());
    }
    
    return strBuf;
}

XMLChString SchemaModel::typeDefToString(XSTypeDefinitionPtr typeDef)
{
    XMLChString strBuf("");
    if ( !typeDef )
        return XMLChString("Null");
    QNamePtr tName(new wsdl::QName(typeDef->getNamespace(), typeDef->getName()));
    strBuf.append(toXmlStr("\n  TypeDefinition: ")).append(tName->toString()).append(toXmlStr("\n"));
    
    if ( typeDef->getTypeCategory() == XSTypeDefinition::COMPLEX_TYPE )
    {
        XSComplexTypeDefinition* ctp = (XSComplexTypeDefinition*)(typeDef.getOwned());
        XSParticle *topParticle = ctp->getParticle();
        if ( topParticle && topParticle->getTermType() == XSParticle::TERM_MODELGROUP )
        {
            XSModelGroup* mgroup = topParticle->getModelGroupTerm();
            XSParticleList *list = mgroup->getParticles();
            for (int i=0, l= list->size(); i<l; i++)
            {
                XSParticle* particle = list->elementAt(i);
                if ( particle->getTermType() == XSParticle::TERM_ELEMENT )
                {
                    XSElementDeclaration* element = (XSElementDeclaration*)particle->getElementTerm();
                    XSTypeDefinition* tdp = element->getTypeDefinition();
                    strBuf.append(toXmlStr("    " ))
                        .append(element->getName()) 
                        .append(toXmlStr(": {"))
                        .append(tdp->getNamespace())
                        .append(toXmlStr("}"))
                        .append(tdp->getName())
                        .append(toXmlStr("\n"));
                } else if ( particle->getTermType() == XSParticle::TERM_MODELGROUP ) {
                    
                }
            }
        }
    }
    else
    {
        strBuf.append(toXmlStr("\nXSObject: "))
            .append(typeDef->getNamespace()) 
            .append(toXmlStr(", "))
            .append(typeDef->getName())
            .append(toXmlStr("\n"));
    }
    
    return strBuf;
}

WSDL_NAMESPACE_END

