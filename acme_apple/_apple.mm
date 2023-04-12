//
//  apple.m
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 04/01/18. with tbs in <3
//
#include "framework.h"
#import "NSString+SymlinksAndAliases.h"
//#import "acme/primitive/primitive/runnable.h"
#include "acme/constant/data_type.h"
#import <UniformTypeIdentifiers/UniformTypeIdentifiers.h>


char * mm_ca2_command_line()
{
   
   return __strdup([[NSBundle mainBundle] objectForInfoDictionaryKey:@"ca2_command_line"]);
   
}


char * ns_get_bundle_identifier()
{
   
   return __strdup([[NSBundle mainBundle] bundleIdentifier]);
   
}

//
//char * ns_get_executable_path()
//{
//   
//   return __strdup([[NSBundle mainBundle] executablePath]);
//   
//}


char * mm_error_string(OSStatus status)
{
   
   NSError * error = [NSError errorWithDomain:NSOSStatusErrorDomain code: status userInfo: nil];
   
   NSString * strError = [error localizedDescription];
   
   return __strdup(strError);
   
}


char * mm_error_description(OSStatus status)
{
   
   NSError * error = [NSError errorWithDomain:NSOSStatusErrorDomain code: status userInfo: nil];
   
   NSString * strError = [error description];
   
   return __strdup(strError);
   
}







//char * ns_realpath(const char * pszPath)
//{
//   
//   NSString * str = [[NSString alloc] initWithUTF8String:pszPath];
//   
//   NSString * strFullPath = [str stringByResolvingSymlinksAndAliases];
//   
//   if(strFullPath == nil)
//   {
//    
//      return strdup(pszPath);
//      
//   }
//   
//   return __strdup(strFullPath);
//   
//}


//void ns_main_async(dispatch_block_t block)
//{
//   
//   //   dispatch_block_t block = ^{
//   //      // Code for the method goes here
//   //   };
//   //
//   
//   if ([NSThread isMainThread])
//   {
//      
//      block();
//      
//   }
//   else
//   {
//      
//      dispatch_async(dispatch_get_main_queue(), block);
//      
//   }
//   
//}



class matter;


///CLASS_DECL_ACME ::e_status call(::matter * prunnable);


void main_async_runnable(::matter * prunnable)
{
   
   ns_main_async(^
   {

      prunnable->run();
                    
   });
   
   //[[mmos get] runRunnableOnMainThread: prunnable];
   
}


void _main_sync_runnable(::matter * prunnable, DWORD dwMillis)
{
   
   ns_main_sync(^
                {
                   
                    __call(prunnable);
                   
                });
   
   //[[mmos get] runRunnableOnMainThread: prunnable];
   
}


NSString * __nsstring(const char * psz);


NSString * __nsstring(NSString * str)
{

   const char * psz = [str UTF8String];
   
   return __nsstring(psz);

}


NSString * __nsstring(const char * psz)
{
   
   //::string str(psz);
   
//   int iLen = __c_get_text_length(psz);
//
//   char * p = (char *) malloc(iLen+1);
//
//   memset(p, 0, iLen+1);
//
//   __c_get_text(p, iLen + 1, psz);
   
   NSString * strText = [[NSString alloc] initWithUTF8String: psz];
   
//   free(p);
   
   return strText;
   
}

//
//
//bool set_task_name(const char * pszTaskName)
//{
//
//   NSString * strTaskName = [[NSString alloc] initWithUTF8String:pszTaskName];
//
//   [[NSThread currentThread] setName : strTaskName];
//
//   return true;
//
//}
//
//bool set_task_name(void * p, const char * pszTaskName)
//{
//
//   NSString * strTaskName = [[NSString alloc] initWithUTF8String:pszTaskName];
//
//   [[NSThread currentThread] setName : strTaskName];
//
//   return true;
//                     
//}
//
//
//char * ns_get_task_name()
//{
//
//   return __strdup([[NSThread currentThread] name]);
//
//}




//char * ns_get_default_browser_path()
//{
//   
//    /*
//   CFURLRef appURL = LSCopyDefaultApplicationURLForURL((__bridge CFURLRef)[NSURL URLWithString: @"http:"], kLSRolesAll, NULL);
//   
//   CFStringRef str = CFURLGetString(appURL);
//   r
//   char * psz = strdup([(__bridge NSString *)str UTF8String]);
//   
//   CFRelease(appURL);r
//   
//   //CFRelease(str);
//   
//     */
//    
//    char * psz = strdup("");
//     
//   return psz;
//   
//}
//

//bool ns_open_url(const char * psz)
//{
//
//   NSString * str = [NSString stringWithUTF8String:psz];
//
//   if(str == NULL)
//   {
//
//      return false;
//
//   }
//
//   NSURL * url = [[NSURL alloc] initWithString: str];
//
//   if(url == NULL)
//   {
//
//      return false;
//
//   }
//
//   if(![[NSWorkspace sharedWorkspace] openURL: url])
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}



void ns_launch_app(const char * psz, const char ** argv, int iFlags);


void node_launch_app(const char * psz, const char ** argv, int iFlags)
{
   
   return ns_launch_app(psz, argv, iFlags);
   
}


void ns_launch_app_at_url(NSURL * url, const char ** argv, int iFlags)
;










void ns_Sleep(unsigned int uiMillis)
{

   [NSThread sleepForTimeInterval: ((double) uiMillis / 1000.0) ];

}



//https://stackoverflow.com/questions/14699604/replacements-for-getmacosstatuserrorstring-getmacosstatuscommentstring

//11
//down vote
//accepted
//You can use [NSError errorWithDomain:NSOSStatusErrorDomain code:errorCode userInfo:nil] to get an NSError representing the OSStatus of errorCode. NSError provides the ability to get a localized error message from the error code (-localizedDescription), or a regular unlocalized one for debugging purposes (-description).

// GetMacOSStatusErrorString and GetMacOSStatusCommentString









char * macos_get_version()
{

   NSString *appVersion = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
 
   return strdup([appVersion UTF8String]);
   
}





void ns_launch_app(const char * psz, const char ** argv, int iFlags)
{

   NSString * path = [[NSString alloc] initWithUTF8String:psz];

   NSURL * url = [NSURL fileURLWithPath:path isDirectory:YES];

   ns_launch_app_at_url(url, argv, iFlags);

}


char * ns_resolve_alias(const char * psz, bool bNoUI = false, bool bNoMount = false)
{
   
   NSString * str = [[NSString alloc] initWithUTF8String: psz];
   
   NSURL * url = [NSURL fileURLWithPath: str];
   
   NSNumber * aliasFlag = nil;
   
   [url getResourceValue:&aliasFlag forKey: NSURLIsAliasFileKey error: nil];
   
   if(!aliasFlag.boolValue)
   {
   
      return NULL;
   
   }
   
   NSURL * resolved = nil;
   
   NSError * perror = nil;
   
   if (@available(macOS 10.10, *))
   {
   
      NSURLBookmarkResolutionOptions options = 0;
      
      options |= bNoUI ? NSURLBookmarkResolutionWithoutUI : 0;
      
      options |= bNoMount ? NSURLBookmarkResolutionWithoutMounting : 0;
      
      resolved = [NSURL URLByResolvingAliasFileAtURL: url options: options error: &perror];
      
   }
   else
   {
      
      NSError * perrorBookmarkData = nil;
      
      NSData * pdataBookmark = [ NSURL bookmarkDataWithContentsOfURL: url error: &perrorBookmarkData ];
      
      if(!pdataBookmark)
      {
         
         return nullptr;
         
      }
      
      NSURLBookmarkResolutionOptions options = NSURLBookmarkResolutionWithoutUI | NSURLBookmarkResolutionWithoutMounting;
      
      resolved = [ NSURL URLByResolvingBookmarkData: pdataBookmark options: options relativeToURL:nil bookmarkDataIsStale: nil error: &perror ];
      
   }

   if (resolved == nil)
   {
      
      return nullptr;
      
   }
   
   NSString * resolvedPath = [resolved absoluteString];

   return __strdup(resolvedPath);
   
}


bool os_is_alias(const char * psz)
{
   
   NSString * str = [[NSString alloc] initWithUTF8String: psz];
   
   NSURL * url = [NSURL fileURLWithPath: str];
   
   NSNumber * aliasFlag = nil;
   
   [url getResourceValue:&aliasFlag forKey:NSURLIsAliasFileKey error: nil];
   
   return aliasFlag.boolValue;
   
}


bool uniform_type_conforms_to_data_type(CFStringRef cfstr, enum_data_type edatatype)
{
   
   if (@available(macOS 11.0, *))
   {
   
      NSString * nsstr = (__bridge NSString *) cfstr;
   
      UTType * uttype = [ UTType typeWithIdentifier: nsstr ];
      
      switch(edatatype)
      {
         case e_data_type_gif:
            return [ uttype conformsToType: UTTypeGIF ];
         default:
            return false;
      }
      
   }
   else
   {
      
      switch(edatatype)
      {
         case e_data_type_gif:
            return UTTypeConformsTo(cfstr, kUTTypeGIF);
         default:
            return false;
            
      }
      
   }
   
}


::string apple_operating_system_store_release()
{
   
   NSOperatingSystemVersion version = [ [ NSProcessInfo processInfo] operatingSystemVersion ];
   
   ::string strRelease;
   
   strRelease.format("%d.%d", version.majorVersion, version.minorVersion);

   return strRelease;
   
}

void apple_operating_system_release(::i32 & iMajor, ::i32 & iMinor, ::i32 & iPatch)
{
   
   NSOperatingSystemVersion version = [ [ NSProcessInfo processInfo] operatingSystemVersion ];

   iMajor = version.majorVersion;
   iMinor = version.minorVersion;
   iPatch = version.patchVersion;

}
