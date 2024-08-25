#pragma once


#include "operating_system-darwin/aura_darwin/_.h"
#include "operating_system-apple/apex_apple/_.h"


#if defined(_AURA_APPLE_LIBRARY)
   #define CLASS_DECL_AURA_APPLE  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_AURA_APPLE  CLASS_DECL_IMPORT
#endif


namespace aura_apple
{


class node;


} // namespace aura_apple



