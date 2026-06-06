//
//  cg_context.mm
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 08:44
//  <3ThomasBorregaardSørensen!!
//

#include <Cocoa/Cocoa.h>
#include "_mm.h"
#include "cg_image.h"



void cg_context_release(cg_context_t & cgcontext)
{
 
   if(cgcontext.is_set())
   {
      
      CGContextRelease(CGCONTEXT(cgcontext));
      
      cgcontext.clear();
      
   }
}


//#define CGCONTEXT(cgcontext) ((CGContextRef)cgcontext)

//
// Graphics.mm
// Objective-C++ macOS implementation using CoreGraphics/CoreText
//
//
//#import <Cocoa/Cocoa.h>
//#import <CoreText/CoreText.h>
//
//namespace innate_subsystem_macos
//{
//
//   constexpr int TRANSPARENT = 1;
//   constexpr int OPAQUE = 2;
//
//   class Graphics
//   {
//   public:
//
//      innate_subsystem::DeviceContextInterface * m_pdevicecontext = nullptr;
//
//      ::innate_subsystem::BrushInterface * m_pbrush = nullptr;
//      ::innate_subsystem::PenInterface * m_ppen = nullptr;
//      ::innate_subsystem::FontInterface * m_pfont = nullptr;
//
//      NSColor * m_pbrushText = nil;
//
//      ::color::color m_colorText;
//      ::color::color m_colorBk;
//      ::color::color m_colorBrushText;
//
//      int m_iBkMode = TRANSPARENT;
//
//      ::i32_point m_pointCurrent;
//
//      Graphics();
//      virtual ~Graphics();
//
//      innate_subsystem::DeviceContextInterface * device_context();
//
//      void initialize_graphics(
//         innate_subsystem::DeviceContextInterface * pdevicecontext);
//
//      void initialize_graphics(
//         innate_subsystem::BitmapInterface * pbitmap);
//
//      void setBkMode(bool transparent);
//
//      void setBlendModeOn(bool bSet);
//
//      void setAntiAliasOn(bool bOn);
//
//      void setTextColor(const ::color::color & color);
//
//      void setBkColor(const ::color::color & color);
//
//      void setBrush(::innate_subsystem::BrushInterface * pbrush);
//
//      void setPen(::innate_subsystem::PenInterface * ppen);
//
//      void setFont(::innate_subsystem::FontInterface * pfont);
//
//      void moveTo(const ::i32_point & point);
//
//      void lineTo(const ::i32_point & point);
//
//      void fillRect(
//         const ::i32_rectangle & rectangle,
//         ::innate_subsystem::BrushInterface * pbrush);
//
//      void fillRect(
//         const ::i32_rectangle & rectangle,
//         const ::color::color & color);
//
//      void ellipse(const ::i32_rectangle & rectangle);
//
//      void rectangle(const ::i32_rectangle & rectangle);
//
//      void drawBitmap(
//         ::innate_subsystem::BitmapInterface * pbitmap,
//         const ::i32_rectangle & rectangle);
//
//      void drawBitmap(
//         ::innate_subsystem::BitmapInterface * pbitmap,
//         const ::i32_point & point,
//         const ::i32_rectangle & rectangle);
//
//      void drawText(
//         const char * text,
//         int cchText,
//         ::i32_rectangle & rectangle,
//         unsigned int format,
//         enum_align ealign);
//
//      void _defer_text_tools();
//
//      CGContextRef context();
//
//   };
//
//
//   Graphics::Graphics()
//   {
//
//      m_iBkMode = TRANSPARENT;
//      m_pbrushText = nil;
//
//   }
//
//
//   Graphics::~Graphics()
//   {
//
//      if (m_pfont)
//      {
//
//         delete m_pfont;
//         m_pfont = nullptr;
//
//      }
//
//      m_pbrushText = nil;
//
//   }
//
//
//   CGContextRef Graphics::context()
//   {
//
//      return (CGContextRef)m_pdevicecontext->m_cgcontext;
//
//   }
//
//
//   innate_subsystem::DeviceContextInterface *
//   Graphics::device_context()
//   {
//
//      return m_pdevicecontext;
//
//   }
//
//
//   void Graphics::initialize_graphics(
//      innate_subsystem::DeviceContextInterface * pdevicecontext)
//   {
//
//      m_pdevicecontext = pdevicecontext;
//
//   }
//
//
//   void Graphics::initialize_graphics(
//      innate_subsystem::BitmapInterface * pbitmap)
//   {
//
//      construct_newø(m_pdevicecontext);
//
//      m_pdevicecontext->initialize_device_context(pbitmap);
//
//   }
//
//
//   void Graphics::setBkMode(bool transparent)
//   {
//
//      m_iBkMode = transparent ? TRANSPARENT : OPAQUE;
//
//   }
//
//
//   void Graphics::setBlendModeOn(bool bSet)
//   {
//
//      CGContextSetBlendMode(
//         context(),
//         bSet ? kCGBlendModeNormal : kCGBlendModeCopy);
//
//   }
//
//
//   void Graphics::setAntiAliasOn(bool bOn)
//   {
//
//      CGContextSetShouldAntialias(context(), bOn);
//
//   }
//
//
//   void Graphics::setTextColor(const ::color::color & color)
//   {
//
//      m_colorText = color;
//
//   }
//
//
//   void Graphics::setBkColor(const ::color::color & color)
//   {
//
//      m_colorBk = color;
//
//   }
//
//
//   void Graphics::setBrush(
//      ::innate_subsystem::BrushInterface * pbrush)
//   {
//
//      m_pbrush = pbrush;
//
//   }
//
//
//   void Graphics::setPen(
//      ::innate_subsystem::PenInterface * ppen)
//   {
//
//      m_ppen = ppen;
//
//   }
//
//
//   void Graphics::setFont(
//      ::innate_subsystem::FontInterface * pfont)
//   {
//
//      m_pfont = pfont;
//
//   }
//
//
//   void Graphics::moveTo(const ::i32_point & point)
//   {
//
//      m_pointCurrent = point;
//
//   }
//
//
//   void Graphics::lineTo(const ::i32_point & point)
//   {
//
//      auto cgpen = m_ppen->impl<::innate_subsystem_macos::Pen>();
//
//      CGContextRef ctx = context();
//
//      CGContextBeginPath(ctx);
//
//      CGContextMoveToPoint(
//         ctx,
//         m_pointCurrent.x,
//         m_pointCurrent.y);
//
//      CGContextAddLineToPoint(
//         ctx,
//         point.x,
//         point.y);
//
//      CGContextSetStrokeColorWithColor(
//         ctx,
//         cgpen->m_color.CGColor);
//
//      CGContextSetLineWidth(
//         ctx,
//         cgpen->m_width);
//
//      CGContextStrokePath(ctx);
//
//      m_pointCurrent = point;
//
//   }
//
//
//   void Graphics::fillRect(
//      const ::i32_rectangle & rectangle,
//      ::innate_subsystem::BrushInterface * pbrush)
//   {
//
//      auto pbrushMac =
//      pbrush->impl<::innate_subsystem_macos::Brush>();
//
//      CGContextRef ctx = context();
//
//      CGRect rc = CGRectMake(
//         rectangle.left,
//         rectangle.top,
//         rectangle.width(),
//         rectangle.height());
//
//      CGContextSetFillColorWithColor(
//         ctx,
//         pbrushMac->m_color.CGColor);
//
//      CGContextFillRect(ctx, rc);
//
//   }
//
//
//   void Graphics::fillRect(
//      const ::i32_rectangle & rectangle,
//      const ::color::color & color)
//   {
//
//      CGContextRef ctx = context();
//
//      CGRect rc = CGRectMake(
//         rectangle.left,
//         rectangle.top,
//         rectangle.width(),
//         rectangle.height());
//
//      NSColor * nscolor =
//      [NSColor colorWithCalibratedRed:
//         color.f32_red()
//                                 green:
//         color.f32_green()
//                                  blue:
//         color.f32_blue()
//                                 alpha:
//         color.f32_opacity()];
//
//      CGContextSetFillColorWithColor(
//         ctx,
//         nscolor.CGColor);
//
//      CGContextFillRect(ctx, rc);
//
//   }
//
//
//   void Graphics::ellipse(const ::i32_rectangle & rectangle)
//   {
//
//      auto pbrushMac =
//      m_pbrush->impl<::innate_subsystem_macos::Brush>();
//
//      auto ppenMac =
//      m_ppen->impl<::innate_subsystem_macos::Pen>();
//
//      CGContextRef ctx = context();
//
//      CGRect rc = CGRectMake(
//         rectangle.left,
//         rectangle.top,
//         rectangle.width(),
//         rectangle.height());
//
//      CGContextSetFillColorWithColor(
//         ctx,
//         pbrushMac->m_color.CGColor);
//
//      CGContextFillEllipseInRect(ctx, rc);
//
//      CGContextSetStrokeColorWithColor(
//         ctx,
//         ppenMac->m_color.CGColor);
//
//      CGContextSetLineWidth(
//         ctx,
//         ppenMac->m_width);
//
//      CGContextStrokeEllipseInRect(ctx, rc);
//
//   }
//
//
//   void Graphics::rectangle(const ::i32_rectangle & rectangle)
//   {
//
//      auto pbrushMac =
//      m_pbrush->impl<::innate_subsystem_macos::Brush>();
//
//      auto ppenMac =
//      m_ppen->impl<::innate_subsystem_macos::Pen>();
//
//      CGContextRef ctx = context();
//
//      CGRect rc = CGRectMake(
//         rectangle.left,
//         rectangle.top,
//         rectangle.width(),
//         rectangle.height());
//
//      CGContextSetFillColorWithColor(
//         ctx,
//         pbrushMac->m_color.CGColor);
//
//      CGContextFillRect(ctx, rc);
//
//      CGContextSetStrokeColorWithColor(
//         ctx,
//         ppenMac->m_color.CGColor);
//
//      CGContextSetLineWidth(
//         ctx,
//         ppenMac->m_width);
//
//      CGContextStrokeRect(ctx, rc);
//
//   }
//
//
//   void Graphics::drawBitmap(
//      ::innate_subsystem::BitmapInterface * pbitmap,
//      const ::i32_rectangle & rectangle)
//   {
//
//      auto pbitmapMac =
//      pbitmap->impl<::innate_subsystem_macos::Bitmap>();
//
//      CGContextRef ctx = context();
//
//      CGRect rc = CGRectMake(
//         rectangle.left,
//         rectangle.top,
//         rectangle.width(),
//         rectangle.height());
//
//      CGContextDrawImage(
//         ctx,
//         rc,
//         pbitmapMac->m_cgimage);
//
//   }
//
//
//   void Graphics::drawBitmap(
//      ::innate_subsystem::BitmapInterface * pbitmap,
//      const ::i32_point & point,
//      const ::i32_rectangle & rectangle)
//   {
//
//      auto pbitmapMac =
//      pbitmap->impl<::innate_subsystem_macos::Bitmap>();
//
//      CGContextRef ctx = context();
//
//      CGRect rc = CGRectMake(
//         point.x,
//         point.y,
//         rectangle.width(),
//         rectangle.height());
//
//      CGImageRef subImage =
//      CGImageCreateWithImageInRect(
//         pbitmapMac->m_cgimage,
//         CGRectMake(
//            rectangle.left,
//            rectangle.top,
//            rectangle.width(),
//            rectangle.height()));
//
//      CGContextDrawImage(ctx, rc, subImage);
//
//      CGImageRelease(subImage);
//
//   }
//
//
//   void cg_contex::_defer_text_tools()
//   {
//
//      if (!m_pfont)
//      {
//
//         constructø(m_pfont);
//
//         m_pfont->initialize_font("Arial", 14);
//
//      }
//
//      if (!m_pbrushText
//         || m_colorBrushText != m_colorText)
//      {
//
//         m_colorBrushText = m_colorText;
//
//         m_pbrushText =
//         [NSColor colorWithCalibratedRed:
//            m_colorText.f32_red()
//                                      green:
//            m_colorText.f32_green()
//                                       blue:
//            m_colorText.f32_blue()
//                                      alpha:
//            m_colorText.f32_opacity()];
//
//      }
//
//   }


void cg_context_draw_text(
      cg_context_t cgcontext,
      const char * text,
      int cchText,
      cg_rect rect,
      cg_color_t cgcolor,
      ct_font_t ctfont,
      unsigned int format,
      enum_align ealign)
{

   
   CGRect cgrect;
   
   cgrect.origin.x = rect.origin.x;
   cgrect.origin.y = rect.origin.y;
   cgrect.size.width = rect.size.w;
   cgrect.size.height = rect.size.h;

   auto cfstr = create_cf_string(text, cchText);

   CTTextAlignment alignment = kCTTextAlignmentLeft;

   if (ealign & e_align_right)
   {

      alignment = kCTTextAlignmentRight;

   }
   else if (ealign & e_align_horizontal_center)
   {

      alignment = kCTTextAlignmentCenter;

   }

   CGFloat lineSpacing = 0.0;

   CTParagraphStyleSetting settings[] =
   {
      {
         kCTParagraphStyleSpecifierAlignment,
         sizeof(CTTextAlignment),
         &alignment
      },
      {
         kCTParagraphStyleSpecifierLineSpacingAdjustment,
         sizeof(CGFloat),
         &lineSpacing
      }
   };

   CTParagraphStyleRef paragraphStyle =
   CTParagraphStyleCreate(
      settings,
      sizeof(settings) / sizeof(settings[0]));

   //
   // Attributes
   //
   CFTypeRef keys[] =
   {
      kCTFontAttributeName,
      kCTForegroundColorAttributeName,
      kCTParagraphStyleAttributeName
   };

   CFTypeRef values[] =
   {
      CTFONT(ctfont),
      CGCOLOR(cgcolor),
      paragraphStyle
   };

   CFDictionaryRef attributes =
   CFDictionaryCreate(
      kCFAllocatorDefault,
      (const void **)keys,
      (const void **)values,
      3,
      &kCFTypeDictionaryKeyCallBacks,
      &kCFTypeDictionaryValueCallBacks);

   //
   // Attributed string
   //
   CFAttributedStringRef attributedString =
   CFAttributedStringCreate(
      kCFAllocatorDefault,
      CFSTRING(cfstr),
      attributes);

   CTFramesetterRef framesetter =
   CTFramesetterCreateWithAttributedString(
      attributedString);

   CGMutablePathRef path =
   CGPathCreateMutable();

   CGPathAddRect(path, nullptr, cgrect);

   CTFrameRef frame =
   CTFramesetterCreateFrame(
      framesetter,
      CFRangeMake(0, 0),
      path,
      nullptr);

   CGContextSaveGState(CGCONTEXT(cgcontext));

//   CGContextTranslateCTM(
//                         CGCONTEXT(cgcontext),
//      0,
//      cgrect.origin.y * 2.0 + cgrect.size.height);
//
//   CGContextScaleCTM(CGCONTEXT(cgcontext), 1.0, -1.0);

   CTFrameDraw(frame, CGCONTEXT(cgcontext));

   CGContextRestoreGState(CGCONTEXT(cgcontext));

   CFRelease(frame);
   CFRelease(path);
   CFRelease(framesetter);
   CFRelease(attributedString);
   CFRelease(attributes);
   CFRelease(paragraphStyle);

}


void cg_context_save_g_state(cg_context_t cgcontext)
{
   
   CGContextSaveGState(CGCONTEXT(cgcontext));
   
}


void cg_context_restore_g_state(cg_context_t cgcontext)
{
   
   CGContexRestoreGState(CGCONTEXT(cgcontext));
   
}

void cg_context_scale_ctm(cg_context_t cgcontext, cg_float x, cg_float y)
{
   
   CGContextScaleCTM(CGCONTEXT(cgcontext), x, y);
   
}


void cg_context_translate_ctm(cg_context_t cgcontext, cg_float x, cg_float y)
{
   
   CGContextranslateCTM(CGCONTEXT(cgcontext), x, y);
   
}


void cg_context_set_text_position(cg_context_t cgcontext, cg_float x, cg_float y)
{
   
   CGContextSetTextPosition(CGCONTEXT(cgcontext), x, y);
   
}


void cg_context_draw_line(cg_context_t cgcontext, cg_point point1, cg_point point2)
{
   
   CGContextBeginPath(CGCONTEXT(cgcontext));
         
   CGContextMoveToPoint(
                        CGCONTEXT(cgcontext),
            point1.x,
            point1.y);
   
   CGContextAddLineToPoint(
      CGCONTEXT(cgcontext),
      point2.x,
      point2.y);
   
  CGContextStrokePath(CGCONTEXT(cgcontext));
   
   
}


void cg_context_draw_rect(cg_context_t cgcontext, cg_rect rect)
{
   
   CGRect cgrect;
   
   cgrect.origin.x = rect.origin.x;
   cgrect.origin.y = rect.origin.y;
   cgrect.size.width = rect.size.w;
   cgrect.size.height = rect.size.h;
   
   CGContextStrokeRect(CGCONTEXT(cgcontext), cgrect);
   
}


void cg_context_fill_rect(cg_context_t cgcontext, cg_rect rect)
{
   
   CGRect cgrect;
   
   cgrect.origin.x = rect.origin.x;
   cgrect.origin.y = rect.origin.y;
   cgrect.size.width = rect.size.w;
   cgrect.size.height = rect.size.h;
   
   auto cgcontextref = CGCONTEXT(cgcontext);
   
   CGContextFillRect(cgcontextref, cgrect);
   
}


void cg_context_draw_ellipse(cg_context_t cgcontext, cg_rect rect)
{
   
   CGRect cgrect;
   
   cgrect.origin.x = rect.origin.x;
   cgrect.origin.y = rect.origin.y;
   cgrect.size.width = rect.size.w;
   cgrect.size.height = rect.size.h;
   
   CGContextStrokeEllipseInRect(CGCONTEXT(cgcontext), cgrect);
   
}


void cg_context_fill_ellipse(cg_context_t cgcontext, cg_rect rect)
{
   
   CGRect cgrect;
   
   cgrect.origin.x = rect.origin.x;
   cgrect.origin.y = rect.origin.y;
   cgrect.size.width = rect.size.w;
   cgrect.size.height = rect.size.h;
   
   CGContextFillEllipseInRect(CGCONTEXT(cgcontext), cgrect);
   
}


void cg_context_set_fill_color_with_color(cg_context_t cgcontext, cg_color_t cgcolor)
{
   
   auto cgcontextref = CGCONTEXT(cgcontext);
   
   auto cgcolorref = CGCOLOR(cgcolor);
   
   CGContextSetFillColorWithColor(cgcontextref, cgcolorref);

}


void cg_context_draw_image(cg_context_t cgcontext, cg_image_t cgimage, cg_rect rect)
{
   
   auto cgcontextref = CGCONTEXT(cgcontext);
   
   auto cgimageref = CGIMAGE(cgimage);
   
   CGContextSaveGState(cgcontextref);
   
   auto imageHeight = (::i32) CGImageGetHeight(cgimageref);
   
   CGContextTranslateCTM(cgcontextref, 0, imageHeight);
   CGContextScaleCTM(cgcontextref, 1.0, -1.0);
   
   CGRect cgrectDraw;
   
   cgrectDraw.origin.x = rect.origin.x;
   cgrectDraw.origin.y = rect.origin.y;
   cgrectDraw.size.width = rect.size.w;
   cgrectDraw.size.height = rect.size.h;

   CGContextDrawImage(cgcontextref, cgrectDraw, cgimageref);
   
   CGContextRestoreGState(cgcontextref);
}


void cg_context_draw_image(cg_context_t cgcontext, cg_image_t cgimage, cg_point point, cg_rect rect)
{
   
   auto cgcontextref = CGCONTEXT(cgcontext);
   
   auto cgimageref = CGIMAGE(cgimage);
   
   CGContextSaveGState(cgcontextref);
   
   auto imageHeight = (::i32) CGImageGetHeight(cgimageref);

   CGRect cgrectDraw;
   
   cgrectDraw.origin.x = point.x;
   cgrectDraw.origin.y = -point.y - rect.size.h;
   cgrectDraw.size.width = rect.size.w;
   cgrectDraw.size.height = rect.size.h;

   CGRect cgrect;
   
   cgrect.origin.x = rect.origin.x;
   cgrect.origin.y = rect.origin.y;
   cgrect.size.width = rect.size.w;
   cgrect.size.height = rect.size.h;
   
   CGContextTranslateCTM(cgcontextref, 0, cgrectDraw.origin.y + cgrectDraw.size.height);
   
   CGContextScaleCTM(cgcontextref, 1.0, -1.0);

   CGImageRef subImage = CGImageCreateWithImageInRect(CGIMAGE(cgimage), cgrect);

   CGContextDrawImage(CGCONTEXT(cgcontext), cgrectDraw, subImage);
   
   CGImageRelease(subImage);
   
   CGContextRestoreGState(cgcontextref);
   
}



void cg_context_set_stroke_color_with_color(cg_context_t cgcontext, cg_color_t cgcolor)
{
   
   CGContextSetStrokeColorWithColor(CGCONTEXT(cgcontext), CGCOLOR(cgcolor));

}


void cg_context_set_blend_mode_on(cg_context_t cgcontext, bool bSet)
{

   CGContextSetBlendMode(
         CGCONTEXT(cgcontext),
         bSet ? kCGBlendModeNormal : kCGBlendModeCopy);

}


void cg_context_set_anti_alias_on(cg_context_t cgcontext, bool bSet)
{

   CGContextSetShouldAntialias(CGCONTEXT(cgcontext), bSet);

}


void cg_context_set_line_width(cg_context_t cgcontext, cg_float fLineWidth)
{

   CGContextSetLineWidth(CGCONTEXT(cgcontext), fLineWidth);

}

void cg_context_draw_dib(cg_context_t cgcontext, cg_dib_t * pdib)
{
   
   auto cgcontextref = CGCONTEXT(cgcontext);
   
   CGRect r{};
   
   r.size.width = pdib->m_cgsize.w;
   r.size.height = pdib->m_cgsize.h;
   
   auto cgimageref = CGIMAGE(pdib->m_pcgimage->m_cgimage);
   
   CGContextDrawImage(cgcontextref, r, cgimageref);
   
}

