//
//  core_graphics.cpp
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-11 07:07
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "core_graphics.h"
#include "operating_system-apple/core_foundation/cf_string.h"
#include "cg_color.h"


static ::pointer <::core_graphics::core_graphics > g_pcoregraphics;


namespace core_graphics
{


   core_graphics::core_graphics()
   {
      
      
      if(::system()->has_property("core_graphics::core_graphics"))
      {
         
         throw ::exception(error_wrong_state);
         
      }
      
      ::system()->property("core_graphics::core_graphics") = this;
      
      
   }

   core_graphics::~core_graphics()

{
   
   
}

//::pointer < ns_image > core_graphics::load_icon(enum_cursor ecursor)
//{
//   
//   return {};
//   
//}

::pointer < cg_color > core_graphics::create_color(const ::color::color & color)
{
   
   auto pcgcolor = create_newø<cg_color>();
   
   pcgcolor->create_color(color);
   
   return pcgcolor;
   
}


::pointer < ::core_foundation::cf_string > core_graphics::create_string(const ::scoped_string & scopedstr)
{
   
   
   auto pcfstring = create_newø<::core_foundation::cf_string>();
   
   pcfstring->create_string(scopedstr);
   
   return pcfstring;
   
}

} // namespace core_graphics




CLASS_DECL_CORE_GRAPHICS ::core_graphics::core_graphics & CoreGraphics()
{
   
   if(!g_pcoregraphics)
   {
      
      g_pcoregraphics = allocateø ::core_graphics::core_graphics();
      
      g_pcoregraphics->initialize(::system());
      
   }
   
   return * g_pcoregraphics;
   
}
