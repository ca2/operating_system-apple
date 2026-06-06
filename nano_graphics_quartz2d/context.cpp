//
// Created by camilo on 31/01/2022 20:15 <3ThomasBorregaardSorensen!! Thomas Likes number 5!!
//
#include "framework.h"
#include "context.h"
#include "icon.h"
#include "brush.h"
#include "font.h"
#include "image.h"
#include "path.h"
#include "pen.h"
#include "acme/nano/graphics/font.h"
#include "acme/nano/graphics/font_family.h"
#include "acme/nano/graphics/brush.h"
#include "acme/nano/graphics/pen.h"
#include "operating_system-apple/core_foundation/cf_string.h"
#include "operating_system-apple/core_graphics/cg_context.h"
#include "operating_system-apple/core_graphics/cg_font.h"
#include "operating_system-apple/core_graphics/cg_image.h"
#include "operating_system-apple/core_graphics/ct_line.h"
#include "acme/prototype/geometry2d/rectangle.h"
//#include <CoreText/CoreText.h>

//void ns_draw_image(CGContextRef cgcontextref, void * pNSImage, int x, int y, int cx);


namespace quartz2d
{

   namespace nano
   {

  
      namespace graphics
      {



   context::context()
   {
      
      m_bOwn = true;
      
//      auto colorspace = CGColorSpaceCreateDeviceRGB();
//      
//      int width = 256;
//      
//      int height = 256;
//      
//      int bitsPerComponent = 8;
//      
//      int bytesPerRow = width * 4;
//
//      m_cgcontext = CGBitmapContextCreate(
//         nullptr,
//         width, height,
//         bitsPerComponent, bytesPerRow,
//         colorspace, kCGImageAlphaPremultipliedLast);
//      
//      CGColorSpaceRelease(colorspace);

   }
//
//
//   context::context(CGContextRef pdc)
//   {
//      
//      m_bOwn = false;
//
//      m_cgcontext = pdc;
//
//   }


   context::~context()
   {
      
      if(!m_bOwn)
      {
         
         m_pcgcontext->m_cgcontext.m_u = 0;

//         if(m_cgcontext)
//         {
//          
//            CGContextRelease(m_cgcontext);
//            
//         }
         
      }

   }
      
      
      ::pointer < ::nano::graphics::image > context::create_bitmap_context(void * pdata,
                                                                 const ::i32_size & size, int iBytesPerRow)
      {
         
         construct_newø(m_pcgcontext);
         
         auto pimage = create_newø<::quartz2d::nano::graphics::image >();
         
         pimage->m_pcgimage = m_pcgcontext->create_bitmap_context(pdata, size, iBytesPerRow);
         
         return pimage;
         
      }
      
      
      void context::update_bitmap_context_image(::pointer < ::nano::graphics::image > & pimage)
      {
         
         ::cast < ::quartz2d::nano::graphics::image > pimageQuartz2d = pimage;
         
         m_pcgcontext->update_bitmap_context_image(pimageQuartz2d->m_pcgimage);
         
      }
      
      
      void context::set_pen(::nano::graphics::pen * ppen)
      {
      
         m_ppen = ppen;
         
      }
   
   
      void context::set_brush(::nano::graphics::brush * pbrush)
      {
         
         m_pbrush = pbrush;
         
      }
   
   
      void context::set_font(::nano::graphics::font * pfont)
      {
      
         m_pfont = pfont;
         
      }

      
      void context::set_blend_mode(::nano::graphics::enum_blend_mode eblendmode)
      {

         if(eblendmode == ::nano::graphics::e_blend_mode_copy)
         {
            
            m_pcgcontext->set_blend_mode_on(false);
            
         }
         else
         {
          
            m_pcgcontext->set_blend_mode_on(true);
            
         }
         
         // 2. Set the C enum blend mode constant
           //CGContextSetBlendMode(context, kCGBlendModeMultiply);

      }

      
      void context::set_smoothing_mode(::nano::graphics::enum_smoothing_mode esmoothingmode)
      {

         
         if(esmoothingmode == ::nano::graphics::e_smoothing_mode_high_quality)
         {
            
            m_pcgcontext->set_anti_alias_on(true);
            
         }
         else
         {
          
            m_pcgcontext->set_anti_alias_on(false);
            
         }
         

      }
      
      
      void context::line(const ::f64_point& point1, const ::f64_point& point2)
      {

         _set_pen(m_ppen);
         m_pcgcontext->draw_line(point1, point2);

      }


   void context::_draw_text(const ::scoped_string & scopedstr, const ::f64_rectangle & rectangleText,
                            const ::e_draw_text & edrawtext, const ::e_align & ealign)
   {
      
      //_select_font(pnanofont);
      
      float w, h;

      w = rectangleText.width();

      h = rectangleText.height();
      
      //_select_font(pnanofont);

      //CGContextSetTextPosition(m_cgcontext, 0, 0);
      //CGContextSetTextDrawingMode (m_cgcontext, kCGTextInvisible);
      
      
      //CGContextShowText (m_cgcontext, str, str.length());
      
      ::string strFontFamilyName;
      
      strFontFamilyName = m_pfont->m_pfontfamily->get_font_family_name();
      
      // Step 1: Create a CFString from the C string
      auto pcfstring = create_newø<::core_foundation::cf_string >();
      
      pcfstring->create_string(scopedstr);
//      = as_CFRef(CFStringCreateWithCString(NULL, scopedstr.c_str(), kCFStringEncodingUTF8));
  
      //auto pstring = create_newø<::core_foundation::cf_string >();

      
      auto pctfont = create_newø<::core_text::ct_font >();
      //auto font_name = as_CFRef(CFStringCreateWithCString(NULL, strFontFamilyName.c_str(), kCFStringEncodingUTF8));
      
      pctfont->create_font_with_name(strFontFamilyName,
                                     m_pfont->m_fFontSize,
                                     m_pfont->m_bBold ? 600 : 400,
                                     m_pfont->m_bItalic,
                                     m_pfont->m_bUnderline);

      ///::cast <::quartz2d::nano

//      // Step 2: Create a CTFont to specify the font and size
//      auto font = as_CFRef(CTFontCreateWithName(font_name, m_pfont->m_fFontSize, NULL));
//
//      // Step 3: Create an attributes dictionary
//      auto attributes = as_CFRef(CFDictionaryCreate(
//              NULL,
//              (const void *[]){ kCTFontAttributeName },
//              (const void *[]){ font },
//              1,
//              &kCFTypeDictionaryKeyCallBacks,
//              &kCFTypeDictionaryValueCallBacks));
//
//      // Step 4: Create an attributed string
//      auto attrString = as_CFRef(CFAttributedStringCreate(NULL, string, attributes));
//
//      // Step 5: Create a CTLine from the attributed string
//      auto line = as_CFRef(CTLineCreateWithAttributedString(attrString));

      
      auto pctline = create_newø<::core_text::ct_line >();
      
      pctline->create_with_text_and_font(pcfstring, pctfont);

      double ascent, descent, leading;
      auto width = pctline->get_typographic_bounds(&ascent, &descent, &leading);
//      double width = CTLineGetTypographicBounds(line, &ascent, &descent, &leading);
      double height = ascent + descent;

      // Create a CGSize with the measured dimensions
      //CGSize textSize = CGSizeMake(width, height);

      ::f64_size sizeText(width, height);
      
      double x = rectangleText.left;
      
      double y = rectangleText.top;

      if(ealign & e_align_horizontal_center)
      {

         x += ((double) rectangleText.width() - sizeText.width()) / 2.0;

      }
      else if(ealign & e_align_right)
      {

         x += (double) rectangleText.width() - sizeText.width();

      }

      if(ealign & e_align_vertical_center)
      {

         y += ((double) rectangleText.height() - sizeText.height()) / 2.0;

      }
      else if(ealign & e_align_bottom)
      {

         y += (double) rectangleText.height() - sizeText.height();

      }
      
      //y += textSize.height;
      
      y += ascent;
      
      m_pcgcontext->set_text_position(0, 0);
      
      //CGContextSetRGBFillColor(context, red, green, blue, alpha);
      
      _set_brush(m_pbrush);

//oordinate system if needed
      
      {

         ::core_graphics::keep_cgcontext keepcgcontext(m_pcgcontext);
         
         m_pcgcontext->scale_ctm(1.0, -1.0);
         m_pcgcontext->translate_ctm(x, -y);

         // Step 7: Draw the text
         //CTLineDraw(line, m_cgcontext);
         pctline->draw(m_pcgcontext);
         
         
      }

          // Release Core Foundation objects
      //CFRelease(line);
      //CFRelease(attrString);
      //CFRelease(attributes);
      //CFRelease(font);
      //CFRelease(font_name);
      //CFRelease(string);
      
//      
//      CGPoint pointSize = CGContextGetTextPosition(m_cgcontext);
//      pointSize.y = pnanofont->m_iFontSize;
//
//      CGContextSetTextDrawingMode (m_cgcontext, kCGTextFill);
//      CGAffineTransform trans = CGAffineTransformMakeScale(1, -1);
//      CGContextSetTextMatrix(m_cgcontext, trans);
//      CGContextSetRGBFillColor (m_cgcontext, __expand_float_rgba(pnanobrushText->m_color));

//      double x = rectangleText.left;
//      
//      double y = rectangleText.top;
//
//      if(ealign & e_align_horizontal_center)
//      {
//
//         x += ((double) rectangleText.width() - pointSize.x) / 2.0;
//
//      }
//      else if(ealign & e_align_right)
//      {
//
//         x += (double) rectangleText.width() - pointSize.x;
//
//      }
//
//      if(ealign & e_align_vertical_center)
//      {
//
//         y += ((double) rectangleText.height() - pointSize.y) / 2.0;
//
//      }
//      else if(ealign & e_align_bottom)
//      {
//
//         y += (double) rectangleText.height() - pointSize.y;
//
//      }
//      
//      y += pointSize.y;
//
//      CGContextShowTextAtPoint (m_cgcontext, x, y, str, str.length());

   }


   ::f64_size context::get_text_extents(const ::scoped_string & scopedstr)
   {
      
      //_select_font(pnanofont);

//      CGContextSetTextPosition(m_cgcontext, 0, 0);
//      CGContextSetTextDrawingMode (m_cgcontext, kCGTextInvisible);//5
//      CGContextShowText (m_cgcontext, str, str.length());//10
//      CGPoint pointSize = CGContextGetTextPosition(m_cgcontext);

      
      auto pcfstring = create_newø<::core_foundation::cf_string >();
      
      pcfstring->create_string(scopedstr);
      
//      // Step 1: Create a CFString from the C string
//         auto string = as_CFRef(CFStringCreateWithCString(NULL, scopedstr.c_str(), kCFStringEncodingUTF8));
//
//      auto font_name = as_CFRef(CFStringCreateWithCString(NULL, pnanofont->m_strFontName.c_str(), kCFStringEncodingUTF8));
//
//          // Step 2: Create a CTFont to specify the font and size
//          auto font = as_CFRef(CTFontCreateWithName(font_name, pnanofont->m_fFontSize, NULL));
//
//         // Step 3: Create an attributes dictionary
//         auto attributes = as_CFRef(CFDictionaryCreate(
//             NULL,
//             (const void *[]){ kCTFontAttributeName },
//             (const void *[]){ font },
//             1,
//             &kCFTypeDictionaryKeyCallBacks,
//             &kCFTypeDictionaryValueCallBacks));
//
//         // Step 4: Create an attributed string
//         auto attrString = as_CFRef(CFAttributedStringCreate(NULL, string, attributes));
//
//         // Step 5: Create a CTLine from the attributed string
//         auto line =as_CFRef( CTLineCreateWithAttributedString(attrString));
//
//         // Step 6: Measure the text
//         double ascent, descent, leading;
//         double width = CTLineGetTypographicBounds(line, &ascent, &descent, &leading);
//         double height = ascent + descent;

         // Create a CGSize with the measured dimensions
         //CGSize textSize = CGSizeMake(width, height);
      
      auto pctline = create_newø<::core_text::ct_line >();
      
      pctline->create_with_text_and_font(pcfstring, m_pfont->m_pctfont);

      double ascent, descent, leading;
      auto width = pctline->get_typographic_bounds(&ascent, &descent, &leading);
//      double width = CTLineGetTypographicBounds(line, &ascent, &descent, &leading);
      double height = ascent + descent;

      // Create a CGSize with the measured dimensions
      //CGSize textSize = CGSizeMake(width, height);

      ::f64_size sizeText(width, height);


         // Release Core Foundation objects
//         CFRelease(line);
//         CFRelease(attrString);
//         CFRelease(attributes);
//         CFRelease(font);
//         CFRelease(string);

//      ::i32_size size;
//      
//      size.cx = textSize.width;
//      size.cy = textSize.height;
//      
      return sizeText;

   }


   void context::rectangle(const ::f64_rectangle & rectangle)
   {

//      CGRect rect;
//      
//      rect.origin.x = rectangle.left;
//      rect.origin.y = rectangle.top;
//      rect.size.width = rectangle.width();
//      rect.size.height = rectangle.height();

      if (m_pbrush && m_pbrush->m_color.has_opacity())
      {
   
         _set_brush(m_pbrush);

         m_pcgcontext->fill_rect(rectangle);

      }

      if(m_ppen && m_ppen->m_fWidth > 0)
      {

         _set_pen(m_ppen);

         m_pcgcontext->draw_rect(rectangle);

      }

   }

      
      void context::ellipse(const ::f64_rectangle & rectangle)
      {

   //      CGRect rect;
   //
   //      rect.origin.x = rectangle.left;
   //      rect.origin.y = rectangle.top;
   //      rect.size.width = rectangle.width();
   //      rect.size.height = rectangle.height();

         if (m_pbrush && m_pbrush->m_color.has_opacity())
         {
      
            _set_brush(m_pbrush);

            m_pcgcontext->fill_ellipse(rectangle);

         }

         if(m_ppen && m_ppen->m_fWidth > 0)
         {

            _set_pen(m_ppen);

            m_pcgcontext->draw_ellipse(rectangle);

         }

      }

      void context::attach(void * posdata, const ::i32_size & size, ::i32 iType)
      {
         
         if(iType == 0)
         {
            
            m_bOwn = false;
            
            construct_newø(m_pcgcontext);
            
            m_pcgcontext->m_cgcontext.m_u =(::uptr)posdata;
            
            m_size = size;
            
         }
         else
         {
          
            throw ::exception(error_wrong_type);
            
         }
            
            
         
      }
      
      
      void context::draw_icon(int x, int y, int cx, int cy, ::nano::graphics::icon * picon)
      {
         
         ::cast < ::quartz2d::nano::graphics::icon > pquartz2dicon = picon;
         
         pquartz2dicon->_draw_in_context(this, x, y, cx, cy);
         
      }
      
      
      void context::draw_image(const ::f64_rectangle & rectangle, ::nano::graphics::image * pimage)
      {
         
         ::cast < ::quartz2d::nano::graphics::image > pquartz2dimage = pimage;
         
         pquartz2dimage->_draw_in_context(this, rectangle);
         
      }

      
      void context::draw_image(const ::f64_point & point, const ::f64_rectangle & rectangle, ::nano::graphics::image * pimage)
      {
         
         ::cast < ::quartz2d::nano::graphics::image > pquartz2dimage = pimage;
         
         m_pcgcontext->draw_image(point, rectangle, pquartz2dimage->m_pcgimage);
         //pquartz2dimage->_draw_in_context(this, point, rectangle);
         
      }


   void context::_set_source(const ::color::color & color)
   {


   }


   void context::_set_brush(brush * pbrush)
   {

      //CGContextSetRGBFillColor(m_cgcontext, __expand_f32_rgba(color));
      
      m_pcgcontext->set_fill_color(pbrush->m_pcgcolor);

   }
      
      void context::_set_pen(pen * ppen)
      {
         
         m_pcgcontext->set_line_width(ppen->m_fWidth);
         
         m_pcgcontext->set_stroke_color(ppen->m_pcgcolor);
         
      }

//   
//   void context::_select_font(::nano::graphics::font * pnanofont)
//   {
//      
////      CGContextSelectFont (m_cgcontext,
////                   pnanofont->m_strFontName.c_str(),
////                   pnanofont->m_iFontSize,
////                   kCGEncodingMacRoman);
//
//   }

      
      void context::translate(::f64 x, ::f64 y)
      {
        
         m_pcgcontext->translate_ctm(x, y);
         
      }

      void context::do_path(::nano::graphics::path *ppath)
      {
         
         bool bHasBrush = m_pbrush && m_pbrush->m_color.has_opacity();
         
         bool bHasPen = m_ppen && m_ppen->m_fWidth > 0 && m_ppen->m_color.has_opacity();
         
         if(!bHasBrush && !bHasPen)
         {
            
            return;
            
         }
         
         ::cast < ::quartz2d::nano::graphics::path > ppathQuartz2d = ppath;

         if (bHasBrush)
         {
      
            _set_brush(m_pbrush);

            m_pcgcontext->add_path(ppathQuartz2d->m_pcgpath);
            
            m_pcgcontext->fill_path();

         }

         if(bHasPen)
         {

            _set_pen(m_ppen);

            m_pcgcontext->add_path(ppathQuartz2d->m_pcgpath);
            
            m_pcgcontext->draw_path();

         }


      }

      } //namespace user


   } //namespace nano


} // namespace quartz2d



