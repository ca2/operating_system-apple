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
      
//      m_ctfontref = nullptr;
//      
//      m_fontdescriptor = nullptr;
//      
//      m_cfstringrefFontName = nullptr;
      
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

   
   void font::update(::draw2d::graphics * pgraphics)
   {

      // defer_update calls us after font properties change. Rebuild native caches.
      m_ctfontref.release();
      m_ctfontdescriptorref.release();
      m_cfstringrefFontName.release();

   
      //array < CFTypeRef >  cfrel;
      //cf_array cfa;
      
      cfref <CGFontRef > cgfontref;
      
      if(m_pathFontFile.has_character())
      {
         
         ::pointer < ::draw2d_quartz2d::draw2d > pdraw2d = system()->draw2d();
         
         cgfontref = pdraw2d->private_cgfontref(pgraphics->m_papplication, m_pathFontFile);
         
      }
      
      if(!cgfontref)
      {

         if(!m_cfstringrefFontName)
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
               
               m_cfstringrefFontName = CFStringCreateWithCString(kCFAllocatorDefault, m_pfontfamily->m_strFamilyName, kCFStringEncodingUTF8);
               
            }
            
         }
         
      }
      
      if(!m_ctfontdescriptorref)
      {
         
         array < CFTypeRef >  pkeyTraits;
         
         cf_array  pvalTraits;
         
         array < CFTypeRef >  pkeyAttrs;
         
         cf_array  pvalAttrs;
         
         CTFontSymbolicTraits symbolicTraitsVal = 0;
         
         CTFontSymbolicTraits symbolicTraitsMsk = 0;
         
         int iWeight = m_fontweight.as_i32();
         
         double dCoreTextWeight = nsfont_get_ctweight(iWeight);
         
         if(dCoreTextWeight != 0.0)
         {
            
            auto dFontWeight = ::as_cfref(CFNumberCreate(kCFAllocatorDefault, kCFNumberDoubleType, &dCoreTextWeight));
            
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
            
            traits1 = CFDictionaryCreate(
                                         kCFAllocatorDefault,
                                         pkeyTraits.data(),
                                         pvalTraits.data(),
                                         pkeyTraits.size(),
                                         &kCFTypeDictionaryKeyCallBacks,
                                         &kCFTypeDictionaryValueCallBacks);
            
            pkeyAttrs.add(kCTFontTraitsAttribute);
            
            pvalAttrs.add(traits1);
            
            //cfrel.add(traits1);
            
         }
         
         cfref<CFDictionaryRef> attributes1;
         
         if(pkeyAttrs.has_elements())
         {
            
            attributes1 = CFDictionaryCreate(
                                             kCFAllocatorDefault,
                                             pkeyAttrs.data(),
                                             pvalAttrs.data(),
                                             pkeyAttrs.size(),
                                             &kCFTypeDictionaryKeyCallBacks,
                                             &kCFTypeDictionaryValueCallBacks);
            
            //cfrel.add(attributes1);
            
         }
         
         
         cfref<CTFontDescriptorRef> ctfontdescriptorref;
         
         if(m_pathFontFile.contains("FontAwesome"))
         {
            
            //output_debug_string("font awesome");
            
         }
         
         if(symbolicTraitsMsk || attributes1)
         {
            
            if(m_cfstringrefFontName != nullptr)
            {
               
               ctfontdescriptorref = CTFontDescriptorCreateWithNameAndSize(m_cfstringrefFontName, 0.0);
               
            }
            
            if(attributes1 != nullptr)
            {
               
               if(ctfontdescriptorref == nullptr)
               {
                  
                  ctfontdescriptorref = CTFontDescriptorCreateWithAttributes(attributes1);
                  
               }
               else
               {
               
                  auto fontdescriptorAttributes1 = ::as_cfref(CTFontDescriptorCreateCopyWithAttributes(ctfontdescriptorref, attributes1));
               
//                  if(fontdescriptorAttributes1 != nullptr)
  //                {
                  
    //                 CFRelease(ctfontdescriptorref);
                  
                     ctfontdescriptorref = fontdescriptorAttributes1;
                  
      //            }

               }
               
            }

            if(symbolicTraitsMsk != 0)
            {

               if(ctfontdescriptorref)
               {


                  //auto fontdescriptorSymbolicTraits = ::as_cfref();
               
                  //if(fontdescriptorSymbolicTraits != nullptr)
                  {
                  
                    // CFRelease(ctfontdescriptorref);
                  
                     ctfontdescriptorref = CTFontDescriptorCreateCopyWithSymbolicTraits(ctfontdescriptorref, symbolicTraitsVal,
                                                                                        symbolicTraitsMsk);
                  
                  }
                  
               }
               
            }
            
         }

         m_ctfontdescriptorref = ctfontdescriptorref;

      }
      
      if(!m_ctfontref)
      {
         
         cfref<CTFontRef> ctfontref;
         
         if(cgfontref)
         {
            
            ctfontref = CTFontCreateWithGraphicsFont(cgfontref, m_fontsize.as_f64() * pgraphics->size_scaler(), nullptr, m_ctfontdescriptorref);
            
            if(m_cfstringrefFontName)
            {
               
               throw "";
               
            }
            
            m_cfstringrefFontName = CFStringCreateMutable(nullptr, 0);
            
            CTFontCopyName(m_ctfontref, m_cfstringrefFontName);
            
            string strFontName;
            
            char sz[1024];
            
            CFStringGetCString(m_cfstringrefFontName, sz, 1024, kCFStringEncodingUTF8);
            
            strFontName = sz;
            
            output_debug_string(strFontName);
            
         }
         else if(!m_ctfontdescriptorref)
         {
            
            ctfontref = CTFontCreateWithName(m_cfstringrefFontName, m_fontsize.as_f64() * pgraphics->size_scaler(), nullptr);
            
         }
         else
         {
            
            ctfontref =  CTFontCreateWithFontDescriptor(m_ctfontdescriptorref, m_fontsize.as_f64() * pgraphics->size_scaler(), nullptr);
            
         }
         
         m_ctfontref = ctfontref;

      }

//      for(::collection::index i = 0; i < cfrel.count(); i++)
//      {
//         
//         CFRelease(cfrel[i]);
//         
//      }
      
//      m_osdata[0] = (void *) (CTFontRef) m_ctfontref;
//      
//      m_osdata[1] = (void *) (CTFontDescriptorRef) m_fontdescriptor;
      
      if(m_ctfontref == nullptr)
      {
         
         throw exception(error_failed);
         
      }
      
   }
   
   
   void font::destroy()
   {

      m_ctfontref.release();
      m_ctfontdescriptorref.release();
      m_cfstringrefFontName.release();

   }


   double font::get_ascent(::draw2d::graphics * pgraphics)
   {
      
      defer_update(pgraphics);
      
      if(m_ctfontref == nil)
      {
       
         return 0.0;
         
      }
      
      return CTFontGetAscent(m_ctfontref);
      
   }
   
   
   double font::get_descent(::draw2d::graphics * pgraphics)
   {
      
      defer_update(pgraphics);
      
      if(m_ctfontref == nil)
      {
         
         return 0.0;
         
      }
      
      return CTFontGetDescent(m_ctfontref);
      
   }
   
   
   double font::get_leading(::draw2d::graphics * pgraphics)
   {
      
      defer_update(pgraphics);
      
      if(m_ctfontref == nil)
      {
         
         return 0.0;
         
      }
      
      return CTFontGetLeading(m_ctfontref);
      
   }
   
   
   double font::get_height(::draw2d::graphics * pgraphics)
   {
      
      defer_update(pgraphics);
      
      if(m_ctfontref == nil)
      {
         
         return 0.0;
         
      }
      
      return CTFontGetAscent(m_ctfontref) + CTFontGetDescent(m_ctfontref) + CTFontGetLeading(m_ctfontref);
      
   }
   
   
} // namespace draw2d_quartz2d



