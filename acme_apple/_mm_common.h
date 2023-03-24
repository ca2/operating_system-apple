//
//  macos_mm.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2013-09-17.
//
//
#pragma once



#include "acme/include/objcpp.h"

#include "acme/include/_simple_templates.h"


#import <Foundation/Foundation.h>

#ifdef MACOS

#import <AppKit/AppKit.h>

#endif

#ifdef APPLE_IOS

#import <UIKit/UIKit.h>

#endif

#ifdef MACOS

//#include "acme/os/macos/mm_oswindow.h"
//#include "acme/os/macos/windowing.h"

#elif defined(APPLE_IOS)

//#include "acme/os/ios/mm_oswindow.h"
//#include "acme/os/ios/windowing.h"

#else

#error "Not implemented... (not MACOS, not APPLE_IOS, but __APPLE__ ?)"

#endif


#undef _

#define _(str) (__nsstring(str))

NSString * __nsstring(NSString * str);
NSString * __nsstring(const char * psz);



