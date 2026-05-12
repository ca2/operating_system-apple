//
//  cg_color..cpp
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 10:11
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "cg_color.h"

#include <Cocoa/Cocoa.h>

namespace core_graphics
{

   cg_color::cg_color()
{
      
      
   }


cg_color::~cg_color()
{
   
   if(m_cgcolor.m_u)
   {
      
      
      CGColorRelease((CGColorRef) m_cgcolor.m_u);
      
   }
   
}


void   cg_color:create_color(const ::color::color & color)
{
   CGFloat red = 1.0;
   CGFloat green = 0.0;
   CGFloat blue = 0.0;
   CGFloat alpha = 1.0;
   CGFloat components[4] = {red, green, blue, alpha};
   
   CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
   CGColorRef color = CGColorCreate(colorSpace, components);
   
   // Release memory
   CGColorSpaceRelease(colorSpace);
   // Use the color...
   // CGColorRelease(color); // Release if not using ARC/autorelease
   m_cgcolor.m_u = (::uptr) color;
   
}

}
