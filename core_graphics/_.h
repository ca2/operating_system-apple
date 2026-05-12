#pragma once


#include "acme/_.h"


#if defined(_core_graphics_project)
#define CLASS_DECL_CORE_GRAPHICS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_CORE_GRAPHICS  CLASS_DECL_IMPORT
#endif


namespace core_graphics
{


   class ns_bitmap;


} // namespace core_graphics



