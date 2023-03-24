//
//  _mm.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 28/02/20.
//
#pragma once


#include "acme/_.h"
#include "_mm_common.h"


void set_apex_system_as_thread();


#import <Foundation/Foundation.h>


#include "NSObject+DDExtensions.h"


#include "DDInvocationGrabber.h"


char * __strdup(NSString * str);

void ns_main_sync(dispatch_block_t block);
void ns_main_async(dispatch_block_t block);


#include "NSString+SymlinksAndAliases.h"


#include "UncaughtExceptionHandler.h"



