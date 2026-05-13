//
//  cg_color..cpp
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 10:11
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "cg_color.h"
#include "_mm.h"

namespace core_graphics
{

cg_color::cg_color()
{
   
   
}


cg_color::~cg_color()
{
   
   if(m_cgcolor.is_set())
   {
      
      cg_color_release(m_cgcolor);
      
   }
   
}


void cg_color::create_color(const ::color::color & color)
{
   
   cg_float red = 1.0;
   cg_float green = 0.0;
   cg_float blue = 0.0;
   cg_float alpha = 1.0;
   
   cg_float rgba[4] = {red, green, blue, alpha};
   
   m_cgcolor = cg_color_create(rgba);
   
}


} // namespace core_graphics



