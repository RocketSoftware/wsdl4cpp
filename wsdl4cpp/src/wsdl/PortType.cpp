/*
 * %fv:PortType.cpp-6 % 
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
 * -----------------------------------------------------------------------
 * 01-03     060509            9.SOAP   mzu  Migrated from WSDL4J
 * 04        070109  t85163    9.SOAP   mzu  Add constants for attribute extentions
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 */
#include "wsdl/wsdlxerces.hpp"
#include "wsdl/NamedElement.hpp"
#include "wsdl/PortType.hpp"

USING_STD

XERCES_CPP_NAMESPACE_USE

WSDL_NAMESPACE_BEGIN

PortType::PortType()
	: AttributeExtensible(), NamedElement() //rev04
    , undefined(true)
    , mOperationList(new Operation::List())
{
}

PortType::~PortType()
{
}

OperationPtr PortType::getOperation(XMLChString name,
        XMLChString inputName, XMLChString outputName)
    throw (WSDLException)
{
    bool found = false;
    OperationPtr ret;
    Operation::List::iterator i = mOperationList->begin();

    for ( Operation::List::iterator ei = mOperationList->end(); 
        i != ei; i++ )
    {
      OperationPtr op = (*i);
      XMLChString opName = op->getName();

      if (name != opName)
      {
          op = (OperationPtr)0;
      } else if ( name == null ) {
          op = (OperationPtr)0;
      }

      if (op && inputName != null )
      {
        OperationTypePtr opStyle = op->getStyle();
        XMLChString defaultInputName = opName;

        if (opStyle == OperationType::REQUEST_RESPONSE)
        {
          defaultInputName = opName.append(toXmlStr("Request"));
        }
        else if (opStyle == OperationType::SOLICIT_RESPONSE)
        {
          defaultInputName = opName.append(toXmlStr("Solicit"));
        }

        bool specifiedDefault = (inputName == defaultInputName);
        InputPtr input = op->getInput();

        if (input)
        {
          XMLChString opInputName = input->getName();

          if (opInputName == null)
          {
            if (!specifiedDefault)
            {
              op = (OperationPtr)0;
            }
          }
          else if (opInputName != inputName)
          {
            op = (OperationPtr)0;
          }
        }
        else
        {
          op = (OperationPtr)0;
        }
      }

      if (op && outputName != null)
      {
        OperationTypePtr opStyle = op->getStyle();
        XMLChString defaultOutputName = opName;

        if (opStyle == OperationType::REQUEST_RESPONSE
            || opStyle == OperationType::SOLICIT_RESPONSE)
        {
          defaultOutputName = opName.append(toXmlStr("Response"));
        }

        bool specifiedDefault = (outputName == defaultOutputName);
        OutputPtr output = op->getOutput();

        if (output)
        {
          XMLChString opOutputName = output->getName();

          if (opOutputName == null)
          {
            if (!specifiedDefault)
            {
              op = (OperationPtr)0;
            }
          }
          else if (opOutputName != outputName )
          {
            op = (OperationPtr)0;
          }
        }
        else
        {
          op = (OperationPtr)0;
        }
      }

      if (op)
      {
        if (found)
        {
            string sb = "Duplicate operation with name=";
            
            sb.append(toLocal(name));
            if (inputName != null)
            {
                sb.append(", inputName=").append(toLocal(inputName));
            }
            if (outputName != null)
            {
                sb.append(", outputName=").append(toLocal(outputName));
            }
            sb.append(", found in portType '");
            sb.append(toLocal(getQName()->toString()));
            sb.append("'.");
           throw WSDLException(WSDLException::INVALID_WSDL, sb);
        }
        else
        {
          found = true;
          ret = op;
        }
      }
    }

    return ret;
}
        
XMLChString PortType::getTagName() 
{
    return toXmlStr("portType");
}

XMLChString PortType::toString()
{
	XMLChString strBuf = NamedElement::toString();
	
	// Add message information
	//strBuf.append(toXmlStr("\n"));
	for (Operation::List::iterator it = mOperationList->begin(), ie = mOperationList->end(); 
			it != ie; it++) 
	{
		strBuf.append(toXmlStr("\n  "))
			.append((*it)->toString());
	}

	return strBuf;
}

WSDL_NAMESPACE_END

