/*
 * %fv:Documented.hpp-3 % 
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
#ifndef DOCUMENTED_HPP_
#define DOCUMENTED_HPP_
#include <xercesc/dom/DOMElement.hpp>
#include "wsdl/wsdlbas.hpp"

WSDL_NAMESPACE_BEGIN

class Documented;

DEFINE_PTR(Documented);

class WSDL_EXPORT Documented
{
public:
	Documented() : mDocEl(0){};
	virtual ~Documented(){};
	
  /**
   * Get the documentation element. This dependency on org.w3c.dom.Element
   * should eventually be removed when a more appropriate way of
   * representing this information is employed.
   *
   * @return the documentation element
   */
  virtual XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* getDocumentationElement() 
  {
    return mDocEl; 
  }

  /**
   * Set the documentation element for this document. This dependency
   * on org.w3c.dom.Element should eventually be removed when a more
   * appropriate way of representing this information is employed.
   *
   * @param docEl the documentation element
   */
  virtual void setDocumentationElement(XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* docEl)
  {
    mDocEl = docEl;
  }
	
protected:
	XERCES_CPP_NAMESPACE_QUALIFIER DOMElement* mDocEl;
    
};

WSDL_NAMESPACE_END

#endif /*DOCUMENTED_HPP_*/
