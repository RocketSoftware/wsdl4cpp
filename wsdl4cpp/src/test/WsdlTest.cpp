#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <numeric>
#include <vector>

#include "wsdl/QName.hpp"
#include "wsdl/WsdlErrorHandler.hpp"
#include "wsdl/WsdlFramework.hpp"
#include "wsdl/WsdlReader.hpp"
#include "wsdl/schema/SchemaModel.hpp"
#include "wsdl/soap/SOAPAddress.hpp"
#include "wsdl/util/SOAPEncodingUtils.hpp"
#include "wsdl/wsdlxerces.hpp"
#include "xcurl/CurlInputSource.hpp"
#include "xercesc/util/BinInputStream.hpp"
#include "xercesc/util/XMLNetAccessor.hpp"

#if defined(_WIN32) || defined(WIN32)    
#define FILE_SEPARATOR '\\'
#define FILE_SEPARATOR_STRING "\\"
#else
#define FILE_SEPARATOR '/'
#define FILE_SEPARATOR_STRING "/"
#endif

void testXMLChString()
{
    wsdl::XMLChString xs1("");
    wsdl::XMLChString xs1a = std::string("");
    wsdl::XMLChString xs1b = std::string("Hello");
    wsdl::XMLChString xs2 = xs1;

    std::cout << "xs1 == null : " << ((xs1 == null) ? "true" : "false") << '\n';
    std::cout << "xs1 == xs1a : " << ((xs1 == xs1a) ? "true" : "false") << '\n';
    std::cout << "xs1a == null : " << ((xs1a == null) ? "true" : "false") << '\n';
    std::cout << "xs1a != null : " << ((xs1a != null) ? "true" : "false") << '\n';
    std::cout << "xs2 == xs1 : " << ((xs2 == xs1) ? "true" : "false") << '\n';
}

void testExtensibilityElement(wsdl::DefinitionsPtr def)
{
    try
    {
        std::cout << "\nTest extention: \n";
        std::cout << "\nSOAPAddress::DEFAULT_ELEM_TYPE = ";
        wsdl::QNamePtr qn = wsdl::SOAPAddress::DEFAULT_ELEM_TYPE;
        if (qn)
            std::cout << wsdl::SOAPAddress::DEFAULT_ELEM_TYPE->toString().toLocal() << '\n';
        else
            std::cout << "null\n";

        wsdl::ServicePtr service = def->getServices()->begin()->second;
        wsdl::PortPtr port = service->getPorts()->begin()->second;
    }
    catch (const char *s)
    {
        std::cout.flush();
        std::cout << '\n' << s << '\n';
        exit(-1);
    }
}

void testSOAPEncArray(wsdl::DefinitionsPtr def)
{
    std::cout << "\nTest SOAP encoding array type: \n";

    wsdl::QNamePtr typeQName(
        new wsdl::QName(wsdl::toXmlStr("urn:SoapZipServiceIntf"), wsdl::toXmlStr("TArrayPostcodeResponse")));

    std::cout << "\n  TypeDefinition: " << typeQName->toString().toLocal() << '\n';

    // XSTypeDefinitionPtr typeDef = def->getType(typeQName);

    wsdl::QNamePtr arrayTypeAttribute = wsdl::SOAPEncodingUtils::getArrayTypeAttribute(typeQName, def);

    if (arrayTypeAttribute)
    {
        std::cout << "\n    wsdl:arrayType = " << arrayTypeAttribute->toString().toLocal() << '\n';

        wsdl::QNamePtr arrayType = wsdl::SOAPEncodingUtils::getArrayType(arrayTypeAttribute);
        wsdl::XMLChString rank = wsdl::SOAPEncodingUtils::getRank(arrayTypeAttribute);

        std::cout << "\n    default soap-enc arrayType = " << arrayType->toString().toLocal() << '\n';
        std::cout << "\n                      its rank = " << rank.toLocal() << '\n';
    }
    else
    {
        std::cout << "\n    no arrayType: \n";
    }
}

void usage()
{
    std::cout
        << "Usage: wsdltest [-h<proxy-host>] [-p<proxy-port>] [--only-test-request] [-c<http-status-code>] "
           "[--self-test] -s<soapencoding dir> <wsdl_file> [-u<url to wsdl dir>]\n"
        << "<soapencoding dir> location of soapencoding.xsd, eg -s=d:\\uniface\\usys\\\n"
        << "<url to wsdl> location of wsdl file, eg -u=file:///D:/v97TEST/temp/source/wsdl4cpp/wsdl4cpp/xsd/soep.wsdl\n"
        << "Examples:\n"
        << "  wsdltest -sD:\\v97TEST\\temp\\source\\wsdl4cpp\\wsdl4cpp\\xsd "
           "-uhttp://www.dneonline.com/calculator.asmx?wsdl\n"
        << "  wsdltest --test-request-only -uhttps://self-signed.badssl.com/ -c502\n"
        << "  wsdltest --self-test\n";
}

void initialize_memory_manager()
{
    static bool initialized = false;
    if (!initialized)
    {
        XMLPlatformUtils::Initialize();
        initialized = true;
    }
}

// Remove when C++11 is available
namespace forwards_compatibility
{
template <typename T> class unique_ptr
{
  public:
    explicit unique_ptr(T *instance) : instance(instance)
    {
    }

    ~unique_ptr()
    {
        delete instance;
    }

    T *operator->() const
    {
        return instance;
    }

  private:
    T *instance;
};

template <typename InputIterator, typename UnaryPredicate>
InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPredicate q)
{
    for (; first != last; ++first)
    {
        if (!q(*first))
        {
            return first;
        }
    }
    return last;
}

template <typename InputIterator, typename UnaryPredicate>
bool all_of(InputIterator first, InputIterator last, UnaryPredicate p)
{
    return forwards_compatibility::find_if_not(first, last, p) == last;
}

template <typename T> struct identity
{
    T operator()(T instance) const
    {
        return instance;
    }
};

template <typename Callable> bool invoke(Callable const &callable)
{
    return callable();
}

} // namespace forwards_compatibility

namespace
{
class test_case
{
  public:
    explicit test_case(std::string url, int expected_curl_status_code, bool exception_expected) :
        url(url), expected_curl_status_code(expected_curl_status_code), exception_expected(exception_expected)
    {
    }

    bool operator()() const
    {
        std::cout << "Performing HTTP GET to '" << url << " expecting CURL status code '" << expected_curl_status_code
                  << "'\n";
        initialize_memory_manager();
        wsdl::CurlInputSource const source(wsdl::toXmlStr(url).c_str());
        forwards_compatibility::unique_ptr<BinInputStream> const stream(source.makeStream());
        unsigned int const buffer_size = 8196;
        XMLByte buffer[buffer_size] = {'\0'};
        unsigned int status = 0;
        try
        {
            status = stream->readBytes(buffer, buffer_size);
        }
        catch (const XERCES_CPP_NAMESPACE::NetAccessorException &e)
        {
            std::cerr << "Exception caught: " << wsdl::toLocal(e.getMessage()) << '\n'
                      << (exception_expected ? "Success: ignored" : "Fail: unexpected") << '\n';
            return exception_expected;
        }
        bool const success = status == expected_curl_status_code;
        if (success)
        {
            std::cout << "Success\n";
        }
        else
        {
            std::cout << "Fail: CURL status code = '" << status << "' Data read: '" << buffer << "'\n";
        }
        return success;
    }

  private:
    std::string url;
    int expected_curl_status_code;
    bool exception_expected;
};
} // namespace

bool self_test()
{
    std::vector<test_case> test_cases;
    test_cases.push_back(test_case("https://expired.badssl.com/", 494, false));
    test_cases.push_back(test_case("https://self-signed.badssl.com/", 502, false));
    test_cases.push_back(test_case("https://untrusted-root.badssl.com/", 600, false));
    test_cases.push_back(test_case("https://revoked.badssl.com/", 575, false));
    test_cases.push_back(test_case("https://pinning-test.badssl.com/", 573, false));
    test_cases.push_back(test_case("https://no-common-name.badssl.com/", 566, false));
    test_cases.push_back(test_case("https://no-subject.badssl.com/", 579, false));
    test_cases.push_back(test_case("https://incomplete-chain.badssl.com/", 865, false));
    test_cases.push_back(test_case("https://sha256.badssl.com/", 498, false));
    test_cases.push_back(test_case("https://sha384.badssl.com/", 498, false));
    test_cases.push_back(test_case("https://sha512.badssl.com/", 498, false));
    test_cases.push_back(test_case("https://1000-sans.badssl.com/", 636, false));
    test_cases.push_back(test_case("https://ecc256.badssl.com/", 684, false));
    test_cases.push_back(test_case("https://ecc384.badssl.com/", 684, false));
    test_cases.push_back(test_case("https://rsa2048.badssl.com/", 603, false));
    test_cases.push_back(test_case("https://rsa4096.badssl.com/", 602, false));
    test_cases.push_back(test_case("https://rsa8192.badssl.com/", 840, false));
    test_cases.push_back(test_case("https://extended-validation.badssl.com/", 700, false));
    test_cases.push_back(test_case("https://mixed-script.badssl.com/", 677, false));
    test_cases.push_back(test_case("https://very.badssl.com/", 1408, false));
    test_cases.push_back(test_case("https://mixed.badssl.com/", 603, false));
    test_cases.push_back(test_case("https://mixed-favicon.badssl.com/", 524, false));
    test_cases.push_back(test_case("https://mixed-form.badssl.com/", 744, false));
    test_cases.push_back(test_case("http://http.badssl.com/", 483, false));
    test_cases.push_back(test_case("http://http-textarea.badssl.com/", 713, false));
    test_cases.push_back(test_case("http://http-password.badssl.com/", 797, false));
    test_cases.push_back(test_case("http://http-login.badssl.com/", 1000, false));
    // {"http://http-dynamic-login.badssl.com/", 1816, false}, // 1147
    test_cases.push_back(test_case("http://http-credit-card.badssl.com/", 876, false));
    test_cases.push_back(test_case("https://cbc.badssl.com/", 485, false));
    test_cases.push_back(test_case("https://mozilla-old.badssl.com/", 660, false));
    test_cases.push_back(test_case("https://mozilla-intermediate.badssl.com/", 721, false));
    test_cases.push_back(test_case("https://mozilla-modern.badssl.com/", 669, false));
    test_cases.push_back(test_case("https://dh1024.badssl.com/", 573, false));
    test_cases.push_back(test_case("https://dh2048.badssl.com/", 593, false));
    test_cases.push_back(test_case("https://dh-small-subgroup.badssl.com/", 647, false));
    test_cases.push_back(test_case("https://dh-composite.badssl.com/", 615, false));
    test_cases.push_back(test_case("https://static-rsa.badssl.com/", 551, false));
    test_cases.push_back(test_case("https://no-sct.badssl.com/", 667, false));
    test_cases.push_back(test_case("https://hsts.badssl.com/", 799, false));
    test_cases.push_back(test_case("https://upgrade.badssl.com/", 819, false));
    test_cases.push_back(test_case("https://preloaded-hsts.badssl.com/", 851, false));
#if defined(_WIN32) || defined(WIN32)    
    test_cases.push_back(test_case("https://tls-v1-0.badssl.com:1010/", 496, true)); // 4ed2ffd0
    test_cases.push_back(test_case("https://tls-v1-1.badssl.com:1011/", 496, true)); // 4ed2ffd0
    test_cases.push_back(test_case("https://tls-v1-2.badssl.com:1012/", 502, false));  
    test_cases.push_back(test_case("https://subdomain.preloaded-hsts.badssl.com/", 0, true));
    test_cases.push_back(test_case("https://superfish.badssl.com/", 498, false));    
    test_cases.push_back(test_case("https://wrong.host.badssl.com/", 0, true));
    test_cases.push_back(test_case("https://reversed-chain.badssl.com/", 0, true));    
    test_cases.push_back(test_case("https://10000-sans.badssl.com/", 0, true));    
    test_cases.push_back(test_case("https://client.badssl.com/", 0, true));
    test_cases.push_back(test_case("https://client-cert-missing.badssl.com/", 0, true));    
    test_cases.push_back(test_case("https://rc4-md5.badssl.com/", 0, true));    
    test_cases.push_back(test_case("https://rc4.badssl.com/", 0, true));    
    test_cases.push_back(test_case("https://3des.badssl.com/", 0, true));    
    test_cases.push_back(test_case("https://null.badssl.com/", 0, true));    
    test_cases.push_back(test_case("https://dh480.badssl.com/", 0, true));  
    test_cases.push_back(test_case("https://dh512.badssl.com/", 0, true));    
    test_cases.push_back(test_case("https://captive-portal.badssl.com/", 0, true));    
#endif    
    test_cases.push_back(test_case("https://https-everywhere.badssl.com/", 995, false));
    test_cases.push_back(test_case("https://spoofed-favicon.badssl.com/", 620, false));
    test_cases.push_back(test_case("https://lock-title.badssl.com/", 707, false));
    test_cases.push_back(
        test_case("https://long-extended-subdomain-name-containing-many-letters-and-dashes.badssl.com/", 619, false));
    test_cases.push_back(
        test_case("https://longextendedsubdomainnamewithoutdashesinordertotestwordwrapping.badssl.com/", 607, false));
    test_cases.push_back(test_case("https://edellroot.badssl.com/", 498, false));
    test_cases.push_back(test_case("https://dsdtestprovider.badssl.com//", 510, false));
    test_cases.push_back(test_case("https://preact-cli.badssl.com/", 500, false));
    test_cases.push_back(test_case("https://webpack-dev-server.badssl.com/", 515, false));
    test_cases.push_back(test_case("https://mitm-software.badssl.com/", 505, false));
    test_cases.push_back(test_case("https://sha1-2016.badssl.com/", 631, false));
    test_cases.push_back(test_case("https://sha1-2017.badssl.com/", 610, false));
    test_cases.push_back(test_case("https://sha1-intermediate.badssl.com/", 614, false));
    test_cases.push_back(test_case("https://invalid-expected-sct.badssl.com/", 772, false));

    std::vector<bool> test_results;
    test_results.reserve(test_cases.size());
    std::transform(test_cases.begin(), test_cases.end(), std::back_inserter(test_results),
                   &forwards_compatibility::invoke<test_case>);
    return forwards_compatibility::all_of(test_results.begin(), test_results.end(),
                                          forwards_compatibility::identity<bool>());
}

int main(int argC, char *argV[])
{
    int i = 0;
    std::string url;
    std::string host = "";
    std::string soapEnc = "";
    int port = 8000;
    int expected_status_code = 0;
    bool test_request_only = false;

    if (argC == 2 && std::string(argV[1]) == "--self-test")
    {
        return self_test() ? 0 : 1;
    }

    if (argC < 3)
    {
        usage();
        return 3;
    }

    for (i = 1; i < argC; i++)
    {
        std::string argu = argV[i];
        if (argu.compare(0, 2, "-h") == 0)
        {
            host = argu.substr(2);
            std::cout << "Using host:" << host << std::endl;
        }
        else if (argu.compare(0, 2, "-p") == 0)
        {
            port = atoi(argu.substr(2).c_str());
            std::cout << "Using port:" << port << std::endl;
        }
        else if (argu.compare(0, 2, "-s") == 0)
        {
            /* -s defines a location where the 
            ** soapencoding.xsd can be found. Hence
            ** the location should end with a separator '/' or '\'.
            */
            soapEnc = argu.substr(2);
            if (soapEnc[soapEnc.length() - 1u] != FILE_SEPARATOR)
            {
                soapEnc.append(FILE_SEPARATOR_STRING);
            }
            std::cout << "Using soap encoding file:\"soapencoding.xsd\" in folder:" << soapEnc << std::endl;        
        }
        else if (argu.compare(0, 2, "-u") == 0)
        {
            url = argu.substr(2);
            std::cout << "Using url:" << url << std::endl;
            if (host.length())
            {
                std::cout << "The specified host:" << host << " with -h option is ignored, due to the specified url\n";
                host.clear();
            }
        }
        else if (argu.compare(0, 2, "-c") == 0)
        {
            expected_status_code = atoi(argu.substr(2).c_str());
            std::cout << "Expecting status code: " << expected_status_code << '\n';
        }
        else if (argu == "--test-request-only")
        {
            test_request_only = true;
        }
        else
        {
            std::cout << "Unknown argument passed: '" << argu << "' \n";
            return 6;
        }
    }

    if (test_request_only)
    {
        return test_case(url, expected_status_code, false)() ? 0 : -1;
    }

    if (soapEnc.empty() || url.empty())
    {
        usage();
        return (3);
    }

    wsdl::WsdlFrameworkPtr theWsdlFrameworkPtr;
    wsdl::WsdlErrorHandlerPtr errPtr;

    try
    {
        // Must do this. Initialize the XML4C system,
        // and release before return.
        theWsdlFrameworkPtr = (wsdl::WsdlFrameworkPtr) new wsdl::WsdlFramework();
    }
    catch (const XMLException &toCatch)
    {
        std::cerr << "Error during initialization! :\n"
                  << wsdl::toLocal(toCatch.getMessage()) << '\n';
        return 1;
    }

    try
    {
        wsdl::XMLChString wsdlURL = wsdl::toXmlStr(url.c_str());
        wsdl::InputSourceEnvPtr isePtr = (wsdl::InputSourceEnvPtr) new wsdl::InputSourceEnv();

        if (host.length() > 0)
        {
            isePtr->setProxyAddress(host);
            isePtr->setProxyPort(port);
        }
        wsdl::WsdlReader reader;

        reader.setInputSourceEnv(isePtr);
        reader.setSOAPEncBaseURI(wsdl::toXmlStr(soapEnc.c_str()));

        wsdl::DefinitionsPtr def(reader.readWsdl(wsdlURL));

        errPtr = reader.getWsdlErrorHandler();
        if (errPtr->getSawErrors())
        {
            std::cout << "Saw errors: " << errPtr->getMessage() << '\n';
            return 5;
        }

        wsdl::XMLChString xs = def->toString();
        std::string s = wsdl::toLocal(xs);
        std::cout << "\nDefinition:\n" << s << '\n';

        bool testImport = true;
        if (testImport)
        {
            //={urn:GoogleSearch}doGetCachedPage
            wsdl::QNamePtr name(new wsdl::QName(wsdl::toXmlStr("urn:GoogleSearch"), wsdl::toXmlStr("doGetCachedPage")));
            wsdl::MessagePtr m = def->getMessage(name);
            if (m)
            {
                std::cout << "\nImported message:" << m->toString().toLocal() << '\n';
            }
        }

        bool testExt = true;
        if (testExt)
        {
            testExtensibilityElement(def);
        }

        bool testArray = (wsdlURL.find(wsdl::toXmlStr("test_soaparray.wsdl")) != wsdl::XMLChString::npos);
        if (testArray)
        {

            testSOAPEncArray(def);
        }

        std::cout.flush();
    }
    catch (wsdl::WSDLException e)
    {
        std::cerr << "WSDLException: " << e.getFaultCode() << ", " << e.getMessage() << '\n';
        return 2;
    }
    catch (std::exception e)
    {
        std::cerr << "Exception: " << e.what() << '\n';
        return 3;
    }
    catch (XMLException &e)
    {
        std::cerr << "Exception: " << TO_LOCAL(e.getMessage()) << '\n';
        return 4;
    }
    std::cout.flush();

    return 0;
}
