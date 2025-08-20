Xerces-C++ Extension for WSDL4CPP
=======================================

This is an extension of Xerces-C++ for WSDL4CPP, under the Apache License 
version 2.0, see the file xercesc/license.txt.

The original source files are from apache package Xerces-C++ 
(https://xerces.apache.org/xerces-c/). The current Xerces-C++ version used
here is 3.2.5. 

-------------------
 How to build
-------------------
1. Download Xerces-C++ Version 3.2.5 from https://xerces.apache.org/xerces-c/;
2. Unzip it to some directory;
3. Copy the "src" subdirectory here to overwrite the "src" subdirectory 
   in the Xerces-C++ directory;
4. Rebuild Xerces-C++.

-------------------
 History of change
-------------------
20240725 (for WSDL4CPP release 10.4.03.000)
What's new?
  - Xerces C++ update from 2.7.0 to 3.2.5;
  - Improved exception messages.
    
New files:
  xercesc/license.txt
  xercesc/src/CMakeLists.txt
  xercesc/src/xercesc/sax/SAXParseException.hpp
  xercesc/src/xercesc/sax/SAXParseException.cpp
  xercesc/src/xercesc/util/XMLExceptMsgs.hpp

Modification:
  xercesc/readme.txt
  xercesc/src/xercesc/validators/schema/TraverseSchema.hpp
  xercesc/src/xercesc/validators/schema/TraverseSchema.cpp
  
Deleted:
  xercesc/Projects/Win32/VC7.1/xerces_all/XercesLib/XercesLib.vcproj
  xercesc/scripts/packageBinaries.pl
  xercesc/src/configure.in



20070213 (for WSDL4CPP beta release 0.9.2b)
New files for introducing InputSourceBuilder:
  xercesc\util\ISBuilder\InputSourceBuilder.hpp
  xercesc\util\ISBuilder\InputSourceBuilder.cpp
  xercesc\util\ISBuilder\Makefile.in
  xercesc\util\Makefile.in

Modification:
  xercesc\validators\schema\TraverseSchema.hpp
  xercesc\validators\schema\TraverseSchema.cpp


20060509:
Modification:
  xercesc\validators\schema\TraverseSchema.hpp
  xercesc\validators\schema\TraverseSchema.cpp


20060508:

Add original source files:
  xercesc\validators\schema\TraverseSchema.hpp
  xercesc\validators\schema\TraverseSchema.cpp
  
