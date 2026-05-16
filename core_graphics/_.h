#pragma once


#include "acme/_.h"


#if defined(_core_graphics_project)
#define CLASS_DECL_CORE_GRAPHICS  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_CORE_GRAPHICS  CLASS_DECL_IMPORT
#endif


#include "operating_system-apple/core_graphics/_struct.h"

namespace core_graphics
{

   class core_graphics;

   class cg_image;

   class cg_context;

   class cg_color;

   class cg_dib;

} // namespace core_graphics


namespace core_text
{

   class ct_font;

} // namespace core_text


namespace core_foundation
{

   class cf_string;

} // namespace core_foundation
