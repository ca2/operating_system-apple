#pragma once

#include "acme/_start.h"

#ifdef __OBJC__

#if defined(MACOS)

#include "aura/operating_system/macos/_mm.h"

#elif defined(APPLE_IOS)

#include "aura/node/operating_system/ios/_mm.h"

#else

#error "Not AppleIos, not AppleMacos... what it is? (to be implemented)"

#endif

#else

#include "_.h"

#endif

#ifndef __OBJC__


#include "aura/_defer.h"


#endif



