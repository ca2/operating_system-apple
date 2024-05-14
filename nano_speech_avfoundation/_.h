#pragma once


#include "audio/audio/_.h"
#include <AudioToolbox/AudioToolbox.h>


#if defined(_nano_speech_avfoundation_project)
   #define CLASS_DECL_NANO_SPEECH_AVFOUNDATION  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_NANO_SPEECH_AVFOUNDATION  CLASS_DECL_IMPORT
#endif



