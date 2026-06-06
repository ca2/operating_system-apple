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


