//
//  debug.cpp
//  acme_apple
//
//  Created by Camilo Sasuke on 2021-06-05 12:40 BRT <3ThomasBS_!!
//
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif


char * mm_error_string(OSStatus status);

char * mm_error_description(OSStatus status);


string apple_error_string(OSStatus status)
{
   
   return string_from_strdup(mm_error_string(status));
   
}


string apple_error_description(OSStatus status)
{
   
   return string_from_strdup(mm_error_description(status));
   
}




