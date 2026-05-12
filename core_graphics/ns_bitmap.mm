//
//  ns_bitmap.mm
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/26.
//
#include <CoreGraphics/CoreGraphics.h>


void ns_bitmap_release(void * & pNSBitmap)
{
 
   if(!pNSBitmap)
   {
      
      return;
      
   }
   
   __bridge_transfer NSBitmap * pnsbitmap = pNSBitmap;
   
   pNSBitmap = nullptr;
   
   pnsbitmap = nil;
   
}
