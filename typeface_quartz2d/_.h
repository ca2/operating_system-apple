#pragma once


#include "bred/_.h"
//#if defined(WINDOWS_DESKTOP)
//#include "windowing_win32/_.h"
//#include "acme/_operating_system.h"
//#endif
//#include "gpu_opengl/_.h"


#ifdef _TYPEFACE_FREETYPE_STATIC
#define CLASS_DECL_TYPEFACE_QUARTZ2D
#elif defined(_typeface_quartz2d_project)
#define CLASS_DECL_TYPEFACE_QUARTZ2D  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_TYPEFACE_QUARTZ2D  CLASS_DECL_IMPORT
#endif


namespace typeface_quartz2d
{

   class face;
   class face_freetype;
   class face_gdiplus;

} // namespace typeface_quartz2d
