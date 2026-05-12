//
//  ns_bitmap.mm
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/26.
//
#include <CoreGraphics/CoreGraphics.h>


void ns_bitmap_release(void * & pNS)
{
 
   if(!pNS)
   {
      
      return;
      
   }
   
   __bridge_transfer NSBitmap * pns = pNS;
   
   pNS = nullptr;
   
   pns = nil;
   
}


void ns_bitmap_get_size(void * pNS, ::i32 & w,::i32 & h)
{
   __bridge NSBitmap * pns = pNS;
 
   pns size
   
}
