#pragma once


#include "acme/_.h"


#if defined(_core_foundation_project)
#define CLASS_DECL_CORE_FOUNDATION  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_CORE_FOUNDATION  CLASS_DECL_IMPORT
#endif


#include "operating_system-apple/core_foundation/_struct.h"

namespace core_foundation
{

   class cf_string;

} // namespace core_foundation
