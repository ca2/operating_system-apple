// Created by camilo on 2026-06-04 19:22 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
// From innate_subsystem_macos on 2026-06-05 17:00 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "acme/nano/graphics/path.h"
#include "core_graphics/cg_path.h"


namespace quartz2d
{

   namespace nano
   {

  
      namespace graphics
   {
      
   class CLASS_DECL_NANO_GRAPHICS_QUARTZ2D path :
      virtual public ::nano::graphics::path
   {
   public:

      //CGMutablePathRef m_ppath;
      
      ::pointer < ::core_graphics::cg_path > m_pcgpath;
      
      path();
      ~path();

      
      virtual void add_arc(::f64 x, ::f64 y, ::f64 w, ::f64 h, const ::f64_angle & angleStart, const ::f64_angle & angleSweep);

      virtual void close_figure();
     
   };

      
      } // namespace graphics
      } // namespace nano
      } // namespace quartz2d



