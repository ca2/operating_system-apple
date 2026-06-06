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
      
      
      virtual void create_font_with_name(const char * pszName, float fPointSize, int iFontWeight, bool bItalic, bool bUnderline);
      
   };


} // namespace core_text


