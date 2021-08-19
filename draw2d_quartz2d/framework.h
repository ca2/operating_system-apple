#ifndef __GNUC__
#pragma once
#endif

#include "acme/_start.h"


#ifdef __OBJC__

#ifdef MACOS

#include "aura/node/operating_system/macos/_mm.h"

#else

#include "aura/os/ios/_mm.h"

#endif

#include <CoreText/CoreText.h>

#import <Foundation/Foundation.h>

#else

#include "_.h"


#ifdef cplusplus


#include "aura/operating_system.h"


#endif


#include "aura/_defer.h"


#endif




