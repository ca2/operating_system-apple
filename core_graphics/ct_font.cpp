//
//  ct_font.cpp
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-11 12:27
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "ct_font.h"
#include <CoreText/CoreText.h>
#include "_mm.h"


namespace core_text
{

ct_font::ct_font()
{
   
   
   
}

ct_font::~ct_font()
{
   
   if(m_ctfont.is_set())
   {
      
      ct_font_release(m_ctfont);
      
   }
   
}


void ct_font::create_font_with_name(const char *pszName, float fPointSize)

{
   
   
   auto cfstr = create_cf_string(pszName, (int) strlen(pszName));
   
   

   //
   // Convert NSFont -> CTFont
   //
   CTFontRef ctfont = CTFontCreateWithName(
      CFSTRING(cfstr),
      fPointSize,
      nullptr);
   
   
   cf_release(cfstr);

}


} // namespace core_text



