#pragma once


#include "app-core/audio/_.h"
#include <AudioToolbox/AudioToolbox.h>


#if defined(_AUDIO_MMSYSTEM_LIBRARY)
   #define CLASS_DECL_AUDIO_CORE_AUDIO  CLASS_DECL_EXPORT
#else
   #define  CLASS_DECL_AUDIO_CORE_AUDIO  CLASS_DECL_IMPORT
#endif



