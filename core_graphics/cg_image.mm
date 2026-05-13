//
//  ns_image.mm
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/26.
//
#include <AppKit/AppKit.h>
#include "_mm.h"

void cg_image_release(cg_image_t & cgimage)
{
 
   if(cgimage.is_set())
   {
      
      CGImageRelease(CGIMAGE(cgimage));
      
      cgimage.clear();
      
   }
}


cg_size cg_image_get_size(cg_image_t cgimage)
{
   
   cg_size size;
   
   size.w  = (::i32) CGImageGetWidth(CGIMAGE(cgimage));
   size.h = (::i32) CGImageGetHeight(CGIMAGE(cgimage));
   
   return size;
   
}
