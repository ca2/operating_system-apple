//
//  ct_font.mm
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-11 12:27
//  <3ThomasBorregaardSørensen!!
//
#include <CoreText/CoreText.h>
#include "_mm.h"


void ct_font_release(ct_font_t & ctfont)
{
   if(ctfont.is_set())
   {
      
      CFRelease(CTFONT(ctfont));
      
      ctfont.clear();
      
   }
   
}




ct_font_t ct_font_create_with_name_and_attributes_1(cf_string_t cfstring, cg_float fPointSize, int iFontWeight, bool bItalic, bool bUnderline)
{
   
   
   //
   // Base font
   //
   CTFontRef baseFont =
   CTFontCreateWithName(
                        CFSTRING(cfstring),
                        fPointSize,
                        nullptr);
   
   //cf_release(cfstr);
   
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
      
      return {(::uptr)finalFont};
      
   }
   else
   {
      
      return {(::uptr)baseFont};
      
   }
   
   
}
