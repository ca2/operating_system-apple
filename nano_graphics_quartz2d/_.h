#pragma once


#include "operating_system-apple/core_graphics/_.h"


#if defined(_nano_graphics_quartz2d_project)
#define CLASS_DECL_NANO_GRAPHICS_QUARTZ2D  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_NANO_GRAPHICS_QUARTZ2D  CLASS_DECL_IMPORT
#endif


namespace quartz2d
{

namespace nano
{


namespace graphics
{


class context;

class pen;
class brush;
class font;

}

}


}
