//
//  ct_font.h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-11 12:27
//  <3ThomasBorregaardSørensen!!
//
#pragma once



namespace core_text
{

class CLASS_DECL_CORE_GRAPHICS ct_font :
virtual public ::particle
{
public:
   
   
   ct_font_t m_ctfont;
   
   ct_font();
   ~ct_font() override;
   
   
   virtual void create_font_with_name(const char * pszName, float fPointSize);
   
};


} // namespace core_text



