#include "framework.h"


double nsfont_get_ctweight(int iWeight);


namespace draw2d_quartz2d
{
   
   
   font::font()
   {
      
      m_font = nullptr;
      
      m_fontdescriptor = nullptr;
      
      m_fontName = nullptr;
      
   }
   
   
   font::~font()
   {
      
      
      destroy();

   }
   
   
   void font::dump(dump_context & dumpcontext) const
   {
      
      ::write_text::font::dump(dumpcontext);
      
   }

   
   void font::create(::draw2d::graphics * pgraphics, i8 iCreate)
   {
   
      array < CFTypeRef >  cfrel;
      
      CGFontRef fontref = nullptr;
      
      if(m_path.has_char())
      {
         
         __pointer(::draw2d_quartz2d::draw2d) pdraw2d = m_psystem->m_paurasystem->draw2d();
         
         fontref = pdraw2d->private_cgfontref(pgraphics->m_pcontext, m_path);
         
      }
      
      if(fontref == nullptr)
      {

         if(m_fontName == nullptr)
         {
            
            auto psystem = m_psystem->m_paurasystem;
            
            auto * pdraw2d = psystem->draw2d();

            auto * pwritetext = pdraw2d->write_text();

            if(::is_set(pwritetext))
            {
               
               auto * pfonts = pwritetext->fonts();
               
               auto * pfontenumeration = pfonts->enumeration();
               
               if(pfontenumeration->m_eventReady.lock(2_s))
               {

                  pfonts->m_pfontenumeration->adapt_font_name(m_strFontFamilyName);
                  
               }
               
               m_fontName = CFStringCreateWithCString(kCFAllocatorDefault, m_strFontFamilyName, kCFStringEncodingUTF8);
               
            }
            
         }
         
      }
      
      if(m_fontdescriptor == nullptr)
      {
         
         array < CFTypeRef >  pkeyTraits;
         
         array < CFTypeRef >  pvalTraits;
         
         array < CFTypeRef >  pkeyAttrs;
         
         array < CFTypeRef >  pvalAttrs;
         
         CTFontSymbolicTraits symbolicTraitsVal = 0;
         
         CTFontSymbolicTraits symbolicTraitsMsk = 0;
         
         int iWeight = m_iFontWeight;
         
         double dCoreTextWeight = nsfont_get_ctweight(iWeight);
         
         if(dCoreTextWeight != 0.0)
         {
            
            CFNumberRef dFontWeight = CFNumberCreate(kCFAllocatorDefault, kCFNumberDoubleType, &dCoreTextWeight);
            
            cfrel.add(dFontWeight);
            
            pkeyTraits.add(kCTFontWeightTrait);
            
            pvalTraits.add(dFontWeight);
            
            if(dCoreTextWeight > 0.0)
            {
               
               symbolicTraitsVal |= kCTFontTraitBold;
               
               symbolicTraitsMsk |= kCTFontTraitBold;
               
            }
            
         }
         
         if(m_bItalic)
         {
            
            symbolicTraitsVal |= kCTFontTraitItalic;
            
            symbolicTraitsMsk |= kCTFontTraitItalic;
            
         }
         
         CFDictionaryRef traits1 = nullptr;
         
         if(pkeyTraits.has_elements())
         {
            
            traits1 = CFDictionaryCreate(
                                         kCFAllocatorDefault,
                                         pkeyTraits.get_data(),
                                         pvalTraits.get_data(),
                                         pkeyTraits.get_size(),
                                         &kCFTypeDictionaryKeyCallBacks,
                                         &kCFTypeDictionaryValueCallBacks);
            
            pkeyAttrs.add(kCTFontTraitsAttribute);
            
            pvalAttrs.add(traits1);
            
            cfrel.add(traits1);
            
         }
         
         CFDictionaryRef attributes1 = nullptr;
         
         if(pkeyAttrs.has_elements())
         {
            
            attributes1 = CFDictionaryCreate(
                                             kCFAllocatorDefault,
                                             pkeyAttrs.get_data(),
                                             pvalAttrs.get_data(),
                                             pkeyAttrs.get_size(),
                                             &kCFTypeDictionaryKeyCallBacks,
                                             &kCFTypeDictionaryValueCallBacks);
            
            pkeyAttrs.add(kCTFontTraitsAttribute);
            
            pvalAttrs.add(traits1);
            
            cfrel.add(attributes1);
            
         }
         
         
         CTFontDescriptorRef fontdescriptor = nullptr;
         
         if(m_path.contains("FontAwesome"))
         {
            
            output_debug_string("font awesome");
            
         }
         
         if(symbolicTraitsMsk || attributes1)
         {
            
            if(m_fontName != nullptr)
            {
               
               fontdescriptor = CTFontDescriptorCreateWithNameAndSize(m_fontName, 0.0);
               
            }
            
            if(attributes1 != nullptr)
            {
               
               if(fontdescriptor == nullptr)
               {
                  
                  fontdescriptor = CTFontDescriptorCreateWithAttributes(attributes1);
                  
               }
               else
               {
               
                  CTFontDescriptorRef fontdescriptorAttributes1 = CTFontDescriptorCreateCopyWithAttributes(fontdescriptor, attributes1);
               
                  if(fontdescriptorAttributes1 != nullptr)
                  {
                  
                     CFRelease(fontdescriptor);
                  
                     fontdescriptor = fontdescriptorAttributes1;
                  
                  }

               }
               
            }

            if(fontdescriptor != nullptr)
            {

               if(symbolicTraitsMsk != 0)
               {
               
                  CTFontDescriptorRef fontdescriptorSymbolicTraits = CTFontDescriptorCreateCopyWithSymbolicTraits(fontdescriptor, symbolicTraitsVal,
   symbolicTraitsMsk);
               
                  if(fontdescriptorSymbolicTraits != nullptr)
                  {
                  
                     CFRelease(fontdescriptor);
                  
                     fontdescriptor = fontdescriptorSymbolicTraits;
                  
                  }
                  
               }
               
            }
            
         }

         m_fontdescriptor = fontdescriptor;

      }
      
      if(m_font == nullptr)
      {
         
         if(fontref != nullptr)
         {
            
            m_font = CTFontCreateWithGraphicsFont(fontref, m_dFontSize, nullptr, m_fontdescriptor);
            
            m_fontName = CFStringCreateMutable(nullptr, 0);
            
            CTFontCopyName(m_font, m_fontName);
            
            string strFontName;
            
            char sz[1024];
            
            CFStringGetCString(m_fontName, sz, 1024, kCFStringEncodingUTF8);
            
            strFontName = sz;
            
            output_debug_string(strFontName);
            
         }
         else if(m_fontdescriptor == nullptr)
         {
            
            auto pfont = CTFontCreateWithName(m_fontName, m_dFontSize, nullptr);
            
            m_font = pfont;

         }
         else
         {
            
            m_font =  CTFontCreateWithFontDescriptor(m_fontdescriptor, m_dFontSize, nullptr);
            
         }
         
      }

      for(index i = 0; i < cfrel.count(); i++)
      {
         
         CFRelease(cfrel[i]);
         
      }
      
      if(fontref != nullptr)
      {
         
         CGFontRelease(fontref);
         
         fontref = nullptr;

      }
      
      m_osdata[0] = (void *) m_font;
      
      m_osdata[1] = (void *) m_fontdescriptor;
      
      
      if(m_font == nullptr)
      {
         
         throw exception(error_failed);
         
      }
      
      //return m_font != nullptr;
      
   }
   
   
   void font::destroy()
   {
   
      //auto estatusOsData =
      
      destroy_os_data();
      
      //auto estatusDestroy =
      
      ::write_text::font::destroy();
      
      //return estatusOsData && estatusDestroy;
      
   }


   void font::destroy_os_data()
   {

      if(m_fontName != nullptr)
      {
         
         CFRelease(m_fontName);
         
         m_fontName = nullptr;
         
      }
      
      if(m_fontdescriptor != nullptr)
      {
         
         CFRelease(m_fontdescriptor);
         
         m_fontdescriptor = nullptr;
         
      }
      
      if(m_font != nullptr)
      {
         
         CFRelease(m_font);
         
         m_font = nullptr;
         
      }
      
      //return ::success;
      
   }

   
   double font::get_ascent(::draw2d::graphics * pgraphics)
   {
      
      defer_update(pgraphics, 0);
      
      if(m_font == nil)
      {
       
         return 0.0;
         
      }
      
      return CTFontGetAscent(m_font);
      
   }
   
   
   double font::get_descent(::draw2d::graphics * pgraphics)
   {
      
      defer_update(pgraphics, 0);
      
      if(m_font == nil)
      {
         
         return 0.0;
         
      }
      
      return CTFontGetDescent(m_font);
      
   }
   
   
   double font::get_leading(::draw2d::graphics * pgraphics)
   {
      
      defer_update(pgraphics, 0);
      
      if(m_font == nil)
      {
         
         return 0.0;
         
      }
      
      return CTFontGetLeading(m_font);
      
   }
   
   
   double font::get_height(::draw2d::graphics * pgraphics)
   {
      
      defer_update(pgraphics, 0);
      
      if(m_font == nil)
      {
         
         return 0.0;
         
      }
      
      return CTFontGetAscent(m_font) + CTFontGetDescent(m_font) + CTFontGetLeading(m_font);
      
   }
   
   
} // namespace draw2d_quartz2d



