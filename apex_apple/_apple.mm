//
//  apple.m
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 04/01/18. with tbs in <3
//
#include "_mm.h"
//#import "NSString+SymlinksAndAliases.h"
#import "acme/prototype/prototype/runnable.h"

char * __strdup(NSString * str)
{
   
   if(str == nil)
   {
      
      return NULL;
      
   }
   
   const char * pszUtf8 = [str UTF8String];
   
   if(pszUtf8 == NULL)
   {
      
      return NULL;
      
   }
   
   return strdup(pszUtf8);
   
   
}



//char * mm_ca2_command_line()
//{
//   
//   return __strdup([[NSBundle mainBundle] objectForInfoDictionaryKey:@"ca2_command_line"]);
//   
//}
//
//



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


void ns_main_post(dispatch_block_t block)
{
   
   //   dispatch_block_t block = ^{
   //      // Code for the method goes here
   //   };
   //
   
   if ([NSThread isMainThread])
   {
      
      block();
      
   }
   else
   {
      
      dispatch_async(dispatch_get_main_queue(), block);
      
   }
   
}


void ns_main_send(dispatch_block_t block, unsigned int)
{
   
   //   dispatch_block_t block = ^{
   //      // Code for the method goes here
   //   };
   //
   
   if ([NSThread isMainThread])
   {
      
      block();
      
   }
   else
   {
      
      dispatch_sync(dispatch_get_main_queue(), block);
      
   }
   
}

class matter;


///CLASS_DECL_APEX ::e_status  * prunnable);
///call(::matter


void main_async_runnable(::matter * prunnable)
{
   
   ns_main_post(^
                 {

                    __call(prunnable);
                    
                 });
   
   //[[mmos get] runRunnableOnMainThread: prunnable];
   
}


void _main_sync_runnable(::matter * prunnable, DWORD dwMillis)
{
   
   ns_main_send(^
                {
                   
                    __call(prunnable);
                   
                }, dwMillis);
   
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
   
   int iLen = __c_get_text_length(psz);
   
   char * p = (char *) malloc(iLen+1);
   
   memset(p, 0, iLen+1);
   
   __c_get_text(p, iLen + 1, psz);
   
   NSString * strText = [[NSString alloc] initWithUTF8String: p];
   
   free(p);
   
   return strText;
   
}

