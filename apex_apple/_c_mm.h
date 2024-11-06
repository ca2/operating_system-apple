//
//  apple.h
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 21/07/17.
//
//
#pragma once

// C and Objective-C include

#ifdef __OBJC__
//#include "NSObject+DDExtensions.h"
//#include "DDInvocationGrabber.h"

char * __strdup(NSString * str);

#endif


#include "graphics.h"
#include "ns_exception.h"
#include "time.h"

void ns_launch_app(const char * psz, const char ** argv, int iFlags);
bool ns_open_file(const char * psz);
void ns_main_post(dispatch_block_t block);

void apple_on_open_file(const char ** psza, int iCount, const char * pszExtra);
void apple_accumulate_on_open_file(const char ** psza, int iCount, const char * pszExtra);
void apple_on_new_file();


void apex_application_main(int argc, char *argv[], const char * pszCommandLine);



//int is_window(oswindow window);

//void ns_main_send(dispatch_block_t block, unsigned int uiMillis = -1);
//void ns_main_post(dispatch_block_t block);

