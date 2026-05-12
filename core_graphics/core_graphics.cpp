//
//  core_graphics.cpp
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-11 07:07
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "core_graphics.h"


static ::core_graphics::core_graphics * g_pcoregraphics = nullptr;

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


} // namespace core_graphics




CLASS_DECL_CORE_GRAPHICS ::core_graphics::core_graphics & CoreGraphics()
{
   
   if(!g_pcoregraphics)
   {
      
      g_pcoregraphics = new ::core_graphics::core_graphics();
      
      g_pcoregraphics->initialize(::system());
      
   }
   *
   return g_pcoregraphics;
   
}
