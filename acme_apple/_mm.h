//
//  _mm.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 28/02/20.
//
#pragma once


#include "_mm_common.h"


void set_apex_system_as_thread();


#import <Foundation/Foundation.h>


#include "NSObject+DDExtensions.h"


#include "DDInvocationGrabber.h"


char * ns_string(NSString * str);

void ns_main_sync(dispatch_block_t block, unsigned int uiMillis = -1);
void ns_main_async(dispatch_block_t block);


#include "NSString+SymlinksAndAliases.h"


#include "UncaughtExceptionHandler.h"



