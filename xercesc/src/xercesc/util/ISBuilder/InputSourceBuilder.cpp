/*
 * Created by Ming Zhu, 2007-01
 * 
 */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include    <xercesc/util/ISBuilder/InputSourceBuilder.hpp>
#include    <xercesc/util/XMLString.hpp>

XERCES_CPP_NAMESPACE_BEGIN

// ---------------------------------------------------------------------------
//  InputSourceBuilder: Destructor
// ---------------------------------------------------------------------------
InputSourceBuilder::~InputSourceBuilder()
{
}

// ---------------------------------------------------------------------------
//  InputSourceBuilder: Hidden Constructors
// ---------------------------------------------------------------------------
InputSourceBuilder::InputSourceBuilder(MemoryManager* const manager) :

    fMemoryManager(manager)
    , fFatalErrorIfNotFound(true)
{
}

XERCES_CPP_NAMESPACE_END

