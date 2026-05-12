//
//  ns_image.mm
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/26.
//
#include <AppKit/AppKit.h>


void ns_image_release(void * & pNS)
{
 
   if(!pNS)
   {
      
      return;
      
   }
   
   // Transfers ownership to ARC. ARC will release 'pns' when this function exits.
   NSImage * pns = (__bridge_transfer NSImage *)pNS;
   
   // Clear the original pointer so the caller knows it's gone
   pNS = nullptr;
   
}


void ns_image_get_size(void * pNS, ::i32 & w,::i32 & h)
{
   NSImage * image = (__bridge NSImage *)pNS;
 
   CGImageRef cgImage = [image CGImageForProposedRect:NULL
                                              context:nil
                                                hints:nil];

   w  = (::i32) CGImageGetWidth(cgImage);
   h = (::i32) CGImageGetHeight(cgImage);
   
}
