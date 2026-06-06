//
//  ct_line.h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 05/06/26 20:36
//  <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#pragma once


namespace core_text
{


   class CLASS_DECL_CORE_GRAPHICS ct_line :
   virtual public ::particle
   {
   public:
      
      
      ct_line_t m_ctline;
      
      ct_line();
      ~ct_line() override;
      
      
      virtual void create_with_text_and_font(::core_foundation::cf_string * pcfstring, ::core_text::ct_font * pctfont);
      
      virtual ::f64 get_typographic_bounds(::f64  * pascent, ::f64 * pdescent, ::f64 * pleading);
      
      virtual void draw(::core_graphics::cg_context * pcgcontext);
      
   };


} // namespace core_text


