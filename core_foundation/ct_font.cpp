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


void ct_font::create_font_with_name(const char *pszName, float fPointSize, int iFontWeight, bool bItalic)

{
   ct_font_release(m_ctfont);
   
   auto cfstr =
      create_cf_string(
         pszName,
         (int)strlen(pszName));

      //
      // Base font
      //
      CTFontRef baseFont =
      CTFontCreateWithName(
         CFSTRING(cfstr),
         fPointSize,
         nullptr);

      cf_release(cfstr);

      //
      // Build symbolic traits
      //
      CTFontSymbolicTraits traits = 0;

      if (bItalic)
      {

         traits |= kCTFontItalicTrait;

      }

      if (iFontWeight >= 600)
      {

         traits |= kCTFontBoldTrait;

      }

      //
      // Apply traits
      //
      CTFontRef finalFont =
      CTFontCreateCopyWithSymbolicTraits(
         baseFont,
         0.0,
         nullptr,
         traits,
         traits);

      //
      // Fallback:
      // if traits version unavailable,
      // use original font
      //
      if(finalFont)
      {

         CFRelease(baseFont);

         m_ctfont.m_u = (::uptr) finalFont;

      }
      else
      {

         m_ctfont.m_u =(::uptr) baseFont;

      }
}


} // namespace core_text



