//
//  core_graphics.h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-11 07:05
//  <3ThomasBorregaardSørensen!!
//
#pragma once



namespace core_graphics
{


   class CLASS_DECL_CORE_GRAPHICS core_graphics :
      virtual public ::particle
   {
   public:
   
      
      core_graphics();
      
      ~core_graphics();
   
      ::pointer < ns_image > load_icon();
   
   };


} // namespace core_graphics


CLASS_DECL_CORE_GRAPHICS ::core_graphics::core_graphics & CoreGraphics();
