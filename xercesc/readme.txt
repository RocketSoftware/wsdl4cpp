Xerces-C++ Extension 3.2.5 for WSDL4CPP
=======================================

The original source files are from apache package:

Xerces-C++ Version 3.2.5

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
New files:
  xercesc\util\XMLExceptMsgs.hpp

Modification:
  xercesc\validators\schema\TraverseSchema.hpp
  xercesc\validators\schema\TraverseSchema.cpp


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
  
