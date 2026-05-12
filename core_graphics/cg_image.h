//
//  ns_image.h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 04:21
//  <3ThomasBorregaardSørensen!!
//
#pragma once


namespace core_graphics
{


   class CLASS_DECL_CORE_GRAPHICS cg_image :
      virtual public ::particle
   {
   public:
      
      
      cg_image_t m_cgimage;
      
      
      cg_image();
      ~cg_image();
      
      
      virtual ::i32_size get_size();
      
      
      
   };

} // namespace core_graphics





