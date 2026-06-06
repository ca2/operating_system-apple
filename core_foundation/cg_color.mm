//
//  cg_color.mm
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 10:12
//  <3ThomasBorregaardSørensen!!
//

#include <CoreGraphics/CoreGraphics.h>
#include "_mm.h"


void cg_color_release(cg_color_t & cgcolor)
{
 
   if(cgcolor.is_set())
   {
      
      CGColorRelease(CGCOLOR(cgcolor));
      
      cgcolor.clear();
      
   }
   
   
}


cg_color_t cg_color_create(cg_float rgba[4])
{
   
   CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
   
   auto r = rgba[0];
   auto g = rgba[1];
   auto b = rgba[2];
   auto a = rgba[3];
   
   CGFloat cgfloata[4];
   
   cgfloata[0] = r;
   cgfloata[1] = g;
   cgfloata[2] = b;
   cgfloata[3] = a;

   CGColorRef color = CGColorCreate(colorSpace, cgfloata);

   CGColorSpaceRelease(colorSpace);

   return {(::uptr) color};

}



