#include "framework.h"
#include "font.h"
#include "draw2d.h"
#include "aura/graphics/write_text/fonts.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "aura/platform/system.h"

double nsfont_get_ctweight(int iWeight);


namespace draw2d_quartz2d
{
   
   
   font::font()
   {
      
//      m_font = nullptr;
//      
//      m_fontdescriptor = nullptr;
//      
//      m_fontName = nullptr;
      
   }
   
   
   font::~font()
   {
      
      destroy();

   }
   
   
//   void font::dump(dump_context & dumpcontext) const
//   {
//
//      ::write_text::font::dump(dumpcontext);
//
//   }

   
   void font::create(::draw2d::graphics * pgraphics, char iCreate)
   {
   
      //array < CFTypeRef >  cfrel;
      ::ref_array refa;
      
      CGFontRef fontref = nullptr;
      
      if(m_path.has_character())
      {
         
         ::pointer < ::draw2d_quartz2d::draw2d > pdraw2d = system()->draw2d();
         
         fontref = pdraw2d->private_cgfontref(pgraphics->m_papplication, m_path);
         
      }
      
      if(fontref == nullptr)
      {

         if(m_fontName == nullptr)
         {
            
            auto psystem = system();
            
            auto * pdraw2d = psystem->draw2d();

            auto * pwritetext = pdraw2d->write_text();

            if(::is_set(pwritetext))
            {
               
               if(m_pfontfamily->m_efont == ::e_font_with_family_name)
               {
                  
                  auto * pfonts = pwritetext->fonts();
                  
                  auto * pfontenumeration = pfonts->enumeration("system");
                  
                  if(pfontenumeration->m_happeningReady.lock(2_s))
                  {
                     
                     auto efont = m_pfontfamily->m_efont;
                     
                     ::string strFamilyName = m_pfontfamily->m_strFamilyName;
                     
                     auto pszFamilyName = strFamilyName.c_str();
                     
                     pfontenumeration->adapt_font_name(m_pfontfamily->m_strFamilyName);
                     
                  }
                  
               }
               else
               {
                  
                  m_pfontfamily->m_strFamilyName = node()->font_name(m_pfontfamily->m_efont);
                  
               }
               
               m_fontName = CFStringCreateWithCString(kCFAllocatorDefault, m_pfontfamily->m_strFamilyName, kCFStringEncodingUTF8);
               
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
         
         int iWeight = m_fontweight.as_i32();
         
         double dCoreTextWeight = nsfont_get_ctweight(iWeight);
         
         if(dCoreTextWeight != 0.0)
         {
            
            cfref<CFNumberRef> dFontWeight(refa, CFNumberCreate(kCFAllocatorDefault, kCFNumberDoubleType, &dCoreTextWeight));
            
            //cfrel.add(dFontWeight);
            
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
         
         cfref<CFDictionaryRef> traits1;
         
         if(pkeyTraits.has_elements())
         {
            
            traits1.set(refa, CFDictionaryCreate(
                                         kCFAllocatorDefault,
                                         pkeyTraits.data(),
                                         pvalTraits.data(),
                                         pkeyTraits.size(),
                                         &kCFTypeDictionaryKeyCallBacks,
                                         &kCFTypeDictionaryValueCallBacks));
            
            pkeyAttrs.add(kCTFontTraitsAttribute);
            
            pvalAttrs.add(traits1);
            
            //cfrel.add(traits1);
            
         }
         
         cfref<CFDictionaryRef> attributes1;
         
         if(pkeyAttrs.has_elements())
         {
            
            attributes1.set(refa, CFDictionaryCreate(
                                             kCFAllocatorDefault,
                                             pkeyAttrs.data(),
                                             pvalAttrs.data(),
                                             pkeyAttrs.size(),
                                             &kCFTypeDictionaryKeyCallBacks,
                                             &kCFTypeDictionaryValueCallBacks));
            
            //cfrel.add(attributes1);
            
         }
         
         
         cfref<CTFontDescriptorRef> fontdescriptor;
         
         if(m_path.contains("FontAwesome"))
         {
            
            //output_debug_string("font awesome");
            
         }
         
         if(symbolicTraitsMsk || attributes1)
         {
            
            if(m_fontName != nullptr)
            {
               
               fontdescriptor.set(refa, CTFontDescriptorCreateWithNameAndSize(m_fontName, 0.0));
               
            }
            
            if(attributes1 != nullptr)
            {
               
               if(fontdescriptor == nullptr)
               {
                  
                  fontdescriptor.set(refa, CTFontDescriptorCreateWithAttributes(attributes1));
                  
               }
               else
               {
               
                  cfref<CTFontDescriptorRef> fontdescriptorAttributes1 (refa, CTFontDescriptorCreateCopyWithAttributes(fontdescriptor, attributes1));
               
//                  if(fontdescriptorAttributes1 != nullptr)
  //                {
                  
    //                 CFRelease(fontdescriptor);
                  
                     fontdescriptor = fontdescriptorAttributes1;
                  
      //            }

               }
               
            }

            if(symbolicTraitsMsk != 0)
            {

               if(fontdescriptor != nullptr)
               {


                  cfref<CTFontDescriptorRef> fontdescriptorSymbolicTraits (refa, CTFontDescriptorCreateCopyWithSymbolicTraits(fontdescriptor, symbolicTraitsVal,
   symbolicTraitsMsk));
               
                  //if(fontdescriptorSymbolicTraits != nullptr)
                  {
                  
                    // CFRelease(fontdescriptor);
                  
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
            
            m_font = CTFontCreateWithGraphicsFont(fontref, m_fontsize.as_f64() * pgraphics->size_scaler(), nullptr, m_fontdescriptor);
            
            if(m_fontName)
            {
               
               throw "";
               
            }
            
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
            
            auto pfont = CTFontCreateWithName(m_fontName, m_fontsize.as_f64() * pgraphics->size_scaler(), nullptr);
            
            m_font = pfont;

         }
         else
         {
            
            m_font =  CTFontCreateWithFontDescriptor(m_fontdescriptor, m_fontsize.as_f64() * pgraphics->size_scaler(), nullptr);
            
         }
         
      }

//      for(::collection::index i = 0; i < cfrel.count(); i++)
//      {
//         
//         CFRelease(cfrel[i]);
//         
//      }
      
      m_osdata[0] = (void *) (CTFontRef) m_font;
      
      m_osdata[1] = (void *) (CTFontDescriptorRef) m_fontdescriptor;
      
      if(m_font == nullptr)
      {
         
         throw exception(error_failed);
         
      }
      
   }
   
   
   void font::destroy()
   {
   
      destroy_os_data();
      
      ::write_text::font::destroy();
      
   }


   void font::destroy_os_data()
   {

//      if(m_fontName != nullptr)
//      {
//         
//         CFRelease(m_fontName);
//         
//         m_fontName = nullptr;
//         
//      }
      
//      if(m_fontdescriptor != nullptr)
//      {
//         
//         CFRelease(m_fontdescriptor);
//         
//         m_fontdescriptor = nullptr;
//         
//      }
      
//      if(m_font != nullptr)
//      {
//         
//         CFRelease(m_font);
//         
//         m_font = nullptr;
//         
//      }
      
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



