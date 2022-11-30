//
//  apple.m
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 04/01/18. with tbs in <3
//
#include "_mm.h"
//#import "NSString+SymlinksAndAliases.h"
#import "acme/primitive/primitive/runnable.h"

char * ns_string(NSString * str)
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
//   return ns_string([[NSBundle mainBundle] objectForInfoDictionaryKey:@"ca2_command_line"]);
//   
//}
//
//



char * mm_error_string(OSStatus status)
{
   
   NSError * error = [NSError errorWithDomain:NSOSStatusErrorDomain code: status userInfo: nil];
   
   NSString * strError = [error localizedDescription];
   
   return ns_string(strError);
   
}


char * mm_error_description(OSStatus status)
{
   
   NSError * error = [NSError errorWithDomain:NSOSStatusErrorDomain code: status userInfo: nil];
   
   NSString * strError = [error description];
   
   return ns_string(strError);
   
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
//   return ns_string(strFullPath);
//   
//}


void ns_main_async(dispatch_block_t block)
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


void ns_main_sync(dispatch_block_t block, unsigned int)
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
   
   ns_main_async(^
                 {

                    __call(prunnable);
                    
                 });
   
   //[[mmos get] runRunnableOnMainThread: prunnable];
   
}


void _main_sync_runnable(::matter * prunnable, DWORD dwMillis)
{
   
   ns_main_sync(^
                {
                   
                    __call(prunnable);
                   
                }, dwMillis);
   
   //[[mmos get] runRunnableOnMainThread: prunnable];
   
}


NSString * __ns_get_text(const char * psz);


NSString * __ns_get_text(NSString * str)
{

   const char * psz = [str UTF8String];
   
   return __ns_get_text(psz);

}


NSString * __ns_get_text(const char * psz)
{
   
   int iLen = __c_get_text_length(psz);
   
   char * p = (char *) malloc(iLen+1);
   
   memset(p, 0, iLen+1);
   
   __c_get_text(p, iLen + 1, psz);
   
   NSString * strText = [[NSString alloc] initWithUTF8String: p];
   
   free(p);
   
   return strText;
   
}

