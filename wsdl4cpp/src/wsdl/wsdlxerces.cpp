/*
 * %fv:wsdlxerces.cpp-5 % 
 * 
 * Written by Ming Zhu, March 2006
 * 
 * History:
 * 
 * revision  date    refnum    version  who  description
 * -----------------------------------------------------------------------
 * 01-02     060509            9.SOAP   mzu  First draft
 * 03        070109  t85163    9.SOAP   mzu  Add implementation for attribute extentions
 * -----------------------------------------------------------------------
 * revision  date    refnum    version  who  description
 * 
 */
#include "wsdl/wsdlxerces.hpp"

WSDL_NAMESPACE_BEGIN

const XMLCh XMLChString::EMPTY_STRING[] = { 0x00 };


XMLChString XMLChString::__NULL;

void XMLChString::init()
{
    __NULL._null = 1;
}

void XMLChString::release()
{
}


// @rev03
XMLChString::ListPtr XMLChString::createList(const XMLChString ss[])
{
    ListPtr sl(new List());
    for (int i=0; !ss[i].isNull(); i++)
    {
        sl->push_back(ss[i]);
    }
    return sl;
}

// @rev03
XMLChString::SetPtr XMLChString::createSet(const XMLChString ss[])
{
    SetPtr sl(new Set());
    for (int i=0; !ss[i].isNull(); i++)
    {
        sl->insert(ss[i]);
    }
    return sl;
}

WSDL_NAMESPACE_END

