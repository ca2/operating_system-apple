//
//  cg_context.mm
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 08:44
//  <3ThomasBorregaardSørensen!!
//

#include <Cocoa/Cocoa.h>
#include "__mm.h"

//#define CG() ((CGContextRef)cgcontext)

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
   void Graphics::_defer_text_tools()
   {

      if (!m_pfont)
      {

         constructø(m_pfont);

         m_pfont->initialize_font("Arial", 14);

      }

      if (!m_pbrushText
         || m_colorBrushText != m_colorText)
      {

         m_colorBrushText = m_colorText;

         m_pbrushText =
         [NSColor colorWithCalibratedRed:
            m_colorText.f32_red()
                                      green:
            m_colorText.f32_green()
                                       blue:
            m_colorText.f32_blue()
                                      alpha:
            m_colorText.f32_opacity()];

      }

   }


void cg_context_draw_text(
                          cg_context_t cgcontext,
      const char * text,
      int cchText,
      CGRect rect,
      CGColor cgcolor,
      unsigned int format,
      enum_align ealign)
   {

      ::string str;

      if (cchText >= 0)
      {

         str.assign(text, cchText);

      }
      else
      {

         str = text;

      }

      _defer_text_tools();

      NSString * nsstr =
      [NSString stringWithUTF8String:str.c_str()];

      auto pfontMac =
      m_pfont->impl<::innate_subsystem_macos::Font>();

      NSMutableParagraphStyle * style =
      [[NSMutableParagraphStyle alloc] init];

      if (ealign & e_align_right)
      {

         style.alignment = NSTextAlignmentRight;

      }
      else if (ealign & e_align_horizontal_center)
      {

         style.alignment = NSTextAlignmentCenter;

      }
      else
      {

         style.alignment = NSTextAlignmentLeft;

      }

   ::string str;

   if (cchText >= 0)
   {

      str.assign(text, cchText);

   }
   else
   {

      str = text;

   }

   NSString * nsstr =
   [NSString stringWithUTF8String:str.c_str()];

   //
   // Convert NSFont -> CTFont
   //
   CTFontRef ctfont =
   CTFontCreateWithName(
      (__bridge CFStringRef)pfont->m_nsfont.fontName,
      pfont->m_nsfont.pointSize,
      nullptr);

   //
   // Alignment
   //
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
      ctfont,
      cgcolor,
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
      (__bridge CFStringRef)nsstr,
      attributes);

   CTFramesetterRef framesetter =
   CTFramesetterCreateWithAttributedString(
      attributedString);

   CGMutablePathRef path =
   CGPathCreateMutable();

   CGPathAddRect(path, nullptr, rect);

   CTFrameRef frame =
   CTFramesetterCreateFrame(
      framesetter,
      CFRangeMake(0, 0),
      path,
      nullptr);

   //
   // CoreGraphics text coordinates:
   // flip vertically
   //
   CGContextSaveGState(cgcontext);

   CGContextTranslateCTM(
      cgcontext,
      0,
      rect.origin.y * 2.0 + rect.size.height);

   CGContextScaleCTM(cgcontext, 1.0, -1.0);

   CTFrameDraw(frame, cgcontext);

   CGContextRestoreGState(cgcontext);

   //
   // Cleanup
   //
   CFRelease(frame);
   CFRelease(path);
   CFRelease(framesetter);
   CFRelease(attributedString);
   CFRelease(attributes);
   CFRelease(paragraphStyle);
   CFRelease(ctfont);

   }
//
//
//} // namespace innate_subsystem_macos
//


voic cg_context_line_to(cg_context_t cgcontext, CGFloat x1, CGFloat y1, CGFloat x2, CGFloat y2)
{
   
   CGContextBeginPath(CG());
         
   CGContextMoveToPoint(
            CG(),
            x1,
            y1);
   
   CGContextAddLineToPoint(
      CG(),
      x2,
      y2;
   
  CGContextStrokePath(CG());
   
   
}

void cg_context_fill_rect(cg_context_t cgcontext, CGRect cgrect)
{
   
   CGContextFillRect(CG(), cgrect);

   
}


void cg_context_set_fill_color_with_color(cg_context_t cgcontext, CGColorRef cgcolor)
{
   
   CGContextSetFillColorWithColor(CG(), cgcolor);

}


void cg_context_draw_image(cg_context_t cgcontext, ns_image_t nsimage, CGPoint point, CGRect rect)
{
   
   
   
         CGRect rc = CGRectMake(
            point.x,
            point.y,
            rect.size.width,
            rect.size.height);
   
         CGImageRef subImage =
         CGImageCreateWithImageInRect(pbitmapMac->m_cgimage,
            rect);
   
   //      CGContextDrawImage(ctx, rc, subImage);
   //
   //      CGImageRelease(subImage);
   //
}



void cg_context_set_stroke_color_with_color(cg_context_t cgcontext, CGColorRef cgcolor)
{
   
   CGContextSetStrokeColorWithColor(CG(), cgcolor);

}


void cg_context_set_blend_mode_on(cg_context_t cgcontext, bool bSet)
{

      CGContextSetBlendMode(
         CG(),
         bSet ? kCGBlendModeNormal : kCGBlendModeCopy);

   //m_pcgcontext->set_blend_mode(bSet);
   
}


void cg_context_set_anti_alias_on(cg_context_t cgcontext, bool bSet)
{

   CGContextSetShouldAntialias(CG(), bOn);

}

void cg_context_set_stroke_with_color(cg_context_t cgcontext, CGColorRef cgcolor)
//      CGContextSetFillColorWithColor(
//         ctx,
//         pbrushMac->m_color.CGColor);


void cg_context_set_stroke_with_color(cg_context_t cgcontext, CGColorRef cgcolor)
{

   CGContextSetStrokeColorWithColor(CG(), cgcolor);

}



void cg_context_set_line_width(cg_context_t cgcontext, CGFloat fLineWidth)
{

   CGContextSetLineWidth(CG(), bOn);

}

