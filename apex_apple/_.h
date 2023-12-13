#pragma once


#include "acme_apple/_.h"
#include "apex_darwin/_.h"


#if defined(_apex_apple_project)
   #define CLASS_DECL_APEX_APPLE  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_APEX_APPLE  CLASS_DECL_IMPORT
#endif


namespace apex_apple
{

   class node;


} // namespace apex_apple



