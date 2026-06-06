//
//  ct_line.mm
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 05/06/26.
//  <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#include <CoreText/CoreText.h>
#include "_mm.h"



void ct_line_release(ct_line_t & ctline)
{
   if(ctline.is_set())
   {
      
      CFRelease(CTLINE(ctline));
      
      ctline.clear();
      
   }
   
}


ct_line_t ct_line_create_from_text_and_font(cf_string_t cfstr, ct_font_t ctfont)
{
   
   
   // Step 3: Create an attributes dictionary
   auto attributes = CFDictionaryCreate(
                                                 NULL,
                                                 (const void *[]){ kCTFontAttributeName },
                                                 (const void *[]){ CTFONT(ctfont) },
                                                 1,
                                                 &kCFTypeDictionaryKeyCallBacks,
                                                 &kCFTypeDictionaryValueCallBacks);
   
   // Step 4: Create an attributed string
   auto attrString = CFAttributedStringCreate(NULL, CFSTRING(cfstr), attributes);
   
   // Step 5: Create a CTLine from the attributed string
   auto line = CTLineCreateWithAttributedString(attrString);
   
   CFRelease(attributes);
   
   CFRelease(attrString);
   
   return {(::uptr)line};
   
}


cg_float ct_line_get_typographic_bounds(ct_line_t ctline, cg_float * pascent, cg_float * pdescent, cg_float * pleading)
{
   
   double width = CTLineGetTypographicBounds(CTLINE(ctline), pascent, pdescent, pleading);
   
   return width;
   
}



void ct_line_draw(ct_line_t ctline, cg_context_t cgcontext)
{
   
   CTLineDraw(CTLINE(ctline), CGCONTEXT(cgcontext));
   
}
