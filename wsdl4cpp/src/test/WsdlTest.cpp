/*
 * %fv:WsdlTest.cpp-10 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 */
#include "wsdl/wsdlxerces.hpp"
#include <iostream>

#include "wsdl/WsdlFramework.hpp"
#include "wsdl/QName.hpp"
#include "wsdl/schema/SchemaModel.hpp"
#include "wsdl/soap/SOAPAddress.hpp"
#include "wsdl/util/SOAPEncodingUtils.hpp"
#include "wsdl/WsdlReader.hpp"
#include "WsdlTest.hpp"

USING_STD

XERCES_CPP_NAMESPACE_USE

USING_WSDL_NAMESPACE

WsdlTest::WsdlTest()
{
}

WsdlTest::~WsdlTest()
{
}


void testXMLChString()
{
	//XMLChString xs0;
	XMLChString xs1("");
    XMLChString xs1a = string("");
    XMLChString xs1b = string("Hello");
	//XMLChString xs02 = xs0;
	XMLChString xs2 = xs1;

	//cout << "xs0 == null : " << ((xs0 == null)?"true":"false") << endl;
	cout << "xs1 == null : " << ((xs1 == null)?"true":"false") << endl;
	cout << "xs1 == xs1a : " << ((xs1 == xs1a)?"true":"false") << endl;
	cout << "xs1a == null : " << ((xs1a == null)?"true":"false") << endl;
	cout << "xs1a != null : " << ((xs1a != null)?"true":"false") << endl;
	//cout << "xs02 == xs0 : " << ((xs02 == xs0)?"true":"false") << endl;
	cout << "xs2 == xs1 : " << ((xs2 == xs1)?"true":"false") << endl;
	
}

void testExtensibilityElement(DefinitionsPtr def) throw (WSDLException)
{
    try {
        cout << "\nTest extention: " << endl;
        cout << "\nSOAPAddress::DEFAULT_ELEM_TYPE = ";
        QNamePtr qn = SOAPAddress::DEFAULT_ELEM_TYPE;
        if ( qn )
            cout << SOAPAddress::DEFAULT_ELEM_TYPE->toString().toLocal() << endl;
        else
            cout << "null" << endl;

        ServicePtr service = def->getServices()->begin()->second;
        PortPtr port = service->getPorts()->begin()->second;
        
    
    } catch (const char* s) {
        cout.flush();
        cout << endl << s << endl;
    }
}

void testSOAPEncArray(DefinitionsPtr def) throw (WSDLException)
{
    cout << "\nTest SOAP encoding array type: " << endl;

    QNamePtr typeQName(new wsdl::QName(toXmlStr("urn:SoapZipServiceIntf"),
        toXmlStr("TArrayPostcodeResponse")));

    cout << "\n  TypeDefinition: " << typeQName->toString().toLocal() << endl;
    
    //XSTypeDefinitionPtr typeDef = def->getType(typeQName);
    
    QNamePtr arrayTypeAttribute = SOAPEncodingUtils::getArrayTypeAttribute(typeQName, def);
    
    if ( arrayTypeAttribute )
    {
        cout << "\n    wsdl:arrayType = " << arrayTypeAttribute->toString().toLocal() << endl;
        
        QNamePtr arrayType = SOAPEncodingUtils::getArrayType(arrayTypeAttribute);
        XMLChString rank = SOAPEncodingUtils::getRank(arrayTypeAttribute);
        
        cout << "\n    default soap-enc arrayType = " << arrayType->toString().toLocal() << endl;
        cout << "\n                      its rank = " << rank.toLocal() << endl;
        
    }
    else
    {
         cout << "\n    no arrayType: " << endl;
    }
    
}

int main(int argC, char* argV[]) {
	int i = 0;
	string url;
	string host = "";
	int port = 8000;

    if ( argC < 2 )
    {
    	std::cout << "Usage: wsdltest [-h<proxy-host>] [-p<proxy-port>] <wsdl_file>" << std::endl;
    	return 2;
    }

	for ( i=0; i<argC; i++ )
	{
		string argu = argV[i];
		if ( argu.compare(0, 2, "-h") == 0 )
		{
			host = argu.substr(2);
		}
		else if ( argu.compare(0, 2, "-p") == 0 )
		{
			port = atoi(argu.substr(2).c_str());
		}
		else
		{
			url = argu;
		}

	}

    WsdlFrameworkPtr theWsdlFrameworkPtr;
    
    try
    {
    	// Must do this. Initialize the XML4C system,
    	// and release before return.
    	theWsdlFrameworkPtr = (WsdlFrameworkPtr)new WsdlFramework();
    }
    catch (const XMLException& toCatch)
    {
         XERCES_STD_QUALIFIER cerr << "Error during initialization! :\n"
              << toLocal(toCatch.getMessage()) << XERCES_STD_QUALIFIER endl;
         return 1;
    }
    
                                      
    //WsdlReaderPtr readerPtr;
	XMLChString wsdlURL = toXmlStr(url.c_str());
    
    try {
		InputSourceEnvPtr isePtr = (InputSourceEnvPtr)new InputSourceEnv();

		if ( host.length() > 0 )
		{
			isePtr->setProxyAddress(host);
			isePtr->setProxyPort(port);
		}
	    WsdlReader reader;
		reader.setInputSourceEnv(isePtr);
        
		//reader.setSOAPEncBaseURI(toXmlStr("file:///cygdrive/d/local/mproj/mirror/wsdl4c/doc"));
		//reader.setSOAPEncBaseURI(toXmlStr("file:///D:/local/mproj/mirror/wsdl4c/doc"));
		reader.setSOAPEncBaseURI(toXmlStr("D:\\local\\mproj\\mirror\\wsdl4cpp\\xsd\\"));
		//reader.setSOAPEncBaseURI(toXmlStr("D:/local/mproj/mirror/wsdl4c/doc"));
        //reader.setSOAPEncBaseURI(toXmlStr("D:/the/directory_of_soapencoding.xsd"));
	    
	    DefinitionsPtr def(reader.readWsdl(wsdlURL));
	    
		XMLChString xs = def->toString();
		string s = toLocal(xs);
	    cout << "\nDefinition:" << endl << s << endl;

        bool testImport = true;
        if ( testImport )
        {
            //={urn:GoogleSearch}doGetCachedPage
            QNamePtr name(new wsdl::QName(toXmlStr("urn:GoogleSearch"), toXmlStr("doGetCachedPage")));
            MessagePtr m = def->getMessage(name);
			if ( m )
			{
                cout << "\nImported message:" << m->toString().toLocal() << endl;
			}
            
        }

        bool testExt = true;
        if ( testExt )
        {
            testExtensibilityElement(def);
            
        }

        bool testArray = ( wsdlURL.find(toXmlStr("test_soaparray.wsdl")) != XMLChString::npos );
        if ( testArray )
        {
            
            testSOAPEncArray(def);
        }

		cout.flush();
    } catch (WSDLException e) {
        cerr << "WSDLException: " << e.getFaultCode() 
        << ", " << e.getMessage() << endl;
    } catch (std::exception e) {
        cerr << "Exception: " << e.what() << endl;
	} catch (XMLException& e) {
        cerr << "Exception: " << TO_LOCAL(e.getMessage()) << endl;
    }
		cout.flush();

    return 0;
}
