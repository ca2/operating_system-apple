#pragma once


#include "app-core/audio/audio/_.h"


#if defined(_AUDIO_MMSYSTEM_LIBRARY)
   #define CLASS_DECL_AUDIO_CORE_AUDIO  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_AUDIO_CORE_AUDIO  CLASS_DECL_IMPORT
#endif



