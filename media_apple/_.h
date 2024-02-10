#pragma once


#include "aura/_.h"



#ifdef _MEDIA_APPLE_STATIC
#define CLASS_DECL_MEDIA_APPLE
#elif defined(_MEDIA_APPLE_LIBRARY)
#define CLASS_DECL_MEDIA_APPLE  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_MEDIA_APPLE  CLASS_DECL_IMPORT
#endif


namespace media_apple
{


class media_item;


} // namespace media_apple


