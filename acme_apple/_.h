#pragma once


#include "operating_system-darwin/acme_darwin/_.h"
#ifdef __OBJC__
#include "_mm.h"
#endif


#if defined(_ACME_POSIX_LIBRARY)
   #define CLASS_DECL_ACME_POSIX  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_ACME_POSIX  CLASS_DECL_IMPORT
#endif


namespace acme_apple
{

   
   class node;

   class file_listing_handler;


} // namespace acme_node



