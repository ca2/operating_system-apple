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
      
      CTLineRelease(CTLINE(ctline));
      
      ctline.clear();
      
   }
   
}


ct_line_t ct_line_create_from_text_and_font(cf_string_t cfstr, cg_font_t cgfont)
{
   
   
   // Step 3: Create an attributes dictionary
   auto attributes = as_CFRef(CFDictionaryCreate(
                                                 NULL,
                                                 (const void *[]){ kCTFontAttributeName },
                                                 (const void *[]){ CGFONT(cgfont) },
                                                 1,
                                                 &kCFTypeDictionaryKeyCallBacks,
                                                 &kCFTypeDictionaryValueCallBacks));
   
   // Step 4: Create an attributed string
   auto attrString = as_CFRef(CFAttributedStringCreate(NULL, CFSTRING(cfstr), attributes));
   
   // Step 5: Create a CTLine from the attributed string
   auto line = as_CFRef(CTLineCreateWithAttributedString(attrString));
   
   
}


cg_float ct_line_get_typographics_bounds(ct_line_t ctline, cg_float * pascent, cg_float * pdescent, cg_float & pleading)
{
   
   double width = CTLineGetTypographicBounds(CTLINE(ctline), pascent, pdescent, pleading);
   
   return width;
   
}
