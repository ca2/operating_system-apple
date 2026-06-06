//
//  ct_font.h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-11 12:27
//  <3ThomasBorregaardSørensen!!
//
#pragma once



namespace core_graphics
{

   class CLASS_DECL_CORE_GRAPHICS cg_font :
   virtual public ::particle
   {
   public:
      
      
      cg_font_t m_cgfont;
      
      cg_font();
      ~cg_font() override;
      
      
//      virtual void create_font_with_name(const char * pszName, float fPointSize, int iFontWeight, bool bItalic, bool bUnderline);
//      
   };


} // namespace core_graphics



