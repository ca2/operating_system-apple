//
//  cf_string.mm
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 12:30
//  <3ThomasBorregaardSørensen!!
//

#include <CoreFoundation/CoreFoundation.h>
#include "_mm.h"



cf_string_t create_cf_string(const char * psz, int size)
{
   
   CFStringRef cfstr = CFStringCreateWithBytes(
                           kCFAllocatorDefault,
                           (const UInt8 *)psz,
                           size,
                           kCFStringEncodingUTF8,
                           false);
   
   return {(::uptr) cfstr};
   
}


void cf_release(cf_string_t & cfstring)
{
   
   if(cfstring.is_set())
   {
      
      CFRelease(CFSTRING(cfstring));
      
      cfstring.clear();
      
   }
   
}
