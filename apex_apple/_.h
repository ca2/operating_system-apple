#pragma once


#include "apex_posix/_.h"
#include "acme_apple/_.h"


#if defined(_APEX_APPLE_LIBRARY)
   #define CLASS_DECL_APEX_APPLE  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_APEX_APPLE  CLASS_DECL_IMPORT
#endif


namespace apex
{


   namespace apple
   {


      class node;


   } // namespace apple


} // namespace apex



