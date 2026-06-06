//
//  cg_color..h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 10:11
//  <3ThomasBorregaardSørensen!!
//
#pragma once



namespace core_graphics
{


   class CLASS_DECL_CORE_GRAPHICS cg_color :
      virtual public ::particle
   {
   public:
      
      
      cg_color_t m_cgcolor;
      
      
      cg_color();
      ~cg_color() override;
      
      virtual void create_color(const ::color::color & color);
         
      
   };


} // namespace core_graphics

