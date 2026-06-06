//
//  ct_font.mm
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-11 12:27
//  <3ThomasBorregaardSørensen!!
//
#include <CoreText/CoreText.h>
#include "_mm.h"


void cg_font_release(cg_font_t & cgfont)
{
   if(cgfont.is_set())
   {
      
      CGFontRelease(CGFONT(cgfont));
      
      cgfont.clear();
      
   }
   
}

//
//cg_font_t create_font_with_name_and_attributes_1(cf_string_t cfstring, cg_float fPointSize, int iFontWeight, bool bItalic)
//{
//
//
//   //
//   // Base font
//   //
//   CTFontRef baseFont =
//   CTFontCreateWithName(
//      CFSTRING(cfstr),
//      fPointSize,
//      nullptr);
//
//   cf_release(cfstr);
//
//   //
//   // Build symbolic traits
//   //
//   CTFontSymbolicTraits traits = 0;
//
//   if (bItalic)
//   {
//
//      traits |= kCTFontItalicTrait;
//
//   }
//
//   if (iFontWeight >= 600)
//   {
//
//      traits |= kCTFontBoldTrait;
//
//   }
//
//   //
//   // Apply traits
//   //
//   CTFontRef finalFont =
//   CTFontCreateCopyWithSymbolicTraits(
//      baseFont,
//      0.0,
//      nullptr,
//      traits,
//      traits);
//
//   //
//   // Fallback:
//   // if traits version unavailable,
//   // use original font
//   //
//   if(finalFont)
//   {
//
//      CFRelease(baseFont);
//
//      m_cgfont.m_u = (::uptr) finalFont;
//
//   }
//   else
//   {
//
//      m_cgfont.m_u =(::uptr) baseFont;
//
//   }
