#pragma once


#include "aura_posix/_.h"
#include "apex_apple/_.h"


#if defined(_AURA_APPLE_LIBRARY)
   #define CLASS_DECL_AURA_APPLE  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_AURA_APPLE  CLASS_DECL_IMPORT
#endif


namespace aura
{


   namespace apple
   {


      class node;


   } // namespace apple


} // namespace aura



