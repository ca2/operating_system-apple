//
//  graphics_text.cpp
//  draw2d_quartz2d
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2023-06-05 11:30.
//  Copyright © 2023 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"
#include "graphics.h"
#include "font.h"


namespace draw2d_quartz2d
{


   void graphics::get_text_metrics(::write_text::text_metric * pmetric)
   {

      if(!m_pfont)
      {
       
         throw exception(::error_null_pointer);
         
      }
      
      CTFontRef pfont = (CTFontRef) m_pfont->get_os_data(this);

      if(pfont == nullptr)
      {
       
         throw exception(::error_null_pointer);
         
      }

      string str(L"123AWZwmc123AWZwmcpQg");

      array < CFTypeRef > pkeys;
      
      array < CFTypeRef > pvals;
      
      array < CFTypeRef > cfrel;
      
      pkeys.add(kCTFontAttributeName);
      
      pvals.add(pfont);
      
      if(m_pfont->m_bUnderline)
      {
         
         int iUnderlineStyle = kCTUnderlineStyleSingle;
         
         CFNumberRef num = CFNumberCreate(kCFAllocatorDefault, kCFNumberIntType, &iUnderlineStyle);
         
         cfrel.add(num);
         
         pkeys.add(kCTUnderlineStyleAttributeName);
         
         pvals.add(num);
         
      }
      
      CFDictionaryRef attributes = CFDictionaryCreate(
                                                      kCFAllocatorDefault,
                                                      pkeys.data(),
                                                      pvals.data(),
                                                      pkeys.size(),
                                                      &kCFTypeDictionaryKeyCallBacks,
                                                      &kCFTypeDictionaryValueCallBacks);
      
      cfrel.add(attributes);
         
      CFStringRef string = CFStringCreateWithCString(nullptr, str, kCFStringEncodingUTF8);
      
      cfrel.add(string);

      CFAttributedStringRef attrString = CFAttributedStringCreate(kCFAllocatorDefault, string, attributes);
      
      cfrel.add(attrString);
      
      CTLineRef line = CTLineCreateWithAttributedString(attrString);
      
      //CFRelease(attrString);
      
      //... contribution https://delphiscience.wordpress.com/2013/01/06/getting-text-metrics-in-firemonkey/
      //CFRelease(string);
      
      //CFRelease(attributes);
      
      CGFloat ascent;
      CGFloat descent;
      CGFloat leading;
      
   //      double width = CTLineGetTypographicBounds(line, &ascent,  &descent, &leading);
      CTLineGetTypographicBounds(line, &ascent,  &descent, &leading);
      
      CFRelease(line);
      
      for(auto & p : cfrel)
      {
         
         CFRelease(p);
         
      }
      
      pmetric->m_dAscent = ascent;
      pmetric->m_dDescent = descent;
      pmetric->m_dInternalLeading = leading;
      pmetric->m_dHeight = ascent + descent + leading;
      pmetric->m_dExternalLeading = leading;
      //CapHeight := CTFontGetCapHeight(LFontRef);
      //XHeight := CTFontGetXHeight(LFontRef);
      //CFRelease(LFontRef);
   //
   //      CGFloat ascent, descent, leading, width;
   //
   //      const_cast < graphics * > (this)->internal_show_text(0, 0, 0, DT_TOPLEFT, str, (int) str.get_length(), kCGTextInvisible, false, &ascent, &descent, &leading, &width);
   //
   //      lpMetrics->tmAscent              = ascent;
   //      lpMetrics->tmDescent             = descent;
   //
   //      pmetric->tmAveCharWidth        = (::i32) (width * (m_pfont.is_null() ? 1.0 : m_pfont->m_dFontWidth) / (double) str.get_length());

      //return true;

   }


} // namespace draw2d_quartz2d



