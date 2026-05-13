//
//  cg_context.cpp
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/26.
//

//
// Graphics.mm
// Objective-C++ macOS implementation using CoreGraphics/CoreText
//
#include "framework.h"
#include "cg_color.h"
#include "cg_context.h"
#include "cg_image.h"
#include "ct_font.h"
#include "_mm.h"
#include "acme/prototype/geometry2d/rectangle.h"
//#import <Cocoa/Cocoa.h>
//#import <CoreText/CoreText.h>


namespace core_graphics
{

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
//   void cg_context::setBlendModeOn(bool bSet)
//   {
//
////      CGContextSetBlendMode(
////         context(),
////         bSet ? kCGBlendModeNormal : kCGBlendModeCopy);
//
//      m_pcgcontext->set_blend_mode(bSet);
//      
//   }
//
//
//
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
//   void Graphics::_defer_text_tools()
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
//
//
//   void Graphics::drawText(
//      const char * text,
//      int cchText,
//      ::i32_rectangle & rectangle,
//      unsigned int format,
//      enum_align ealign)
//   {
//
//      ::string str;
//
//      if (cchText >= 0)
//      {
//
//         str.assign(text, cchText);
//
//      }
//      else
//      {
//
//         str = text;
//
//      }
//
//      _defer_text_tools();
//
//      NSString * nsstr =
//      [NSString stringWithUTF8String:str.c_str()];
//
//      auto pfontMac =
//      m_pfont->impl<::innate_subsystem_macos::Font>();
//
//      NSMutableParagraphStyle * style =
//      [[NSMutableParagraphStyle alloc] init];
//
//      if (ealign & e_align_right)
//      {
//
//         style.alignment = NSTextAlignmentRight;
//
//      }
//      else if (ealign & e_align_horizontal_center)
//      {
//
//         style.alignment = NSTextAlignmentCenter;
//
//      }
//      else
//      {
//
//         style.alignment = NSTextAlignmentLeft;
//
//      }
//
//      NSDictionary * attributes =
//      @{
//         NSFontAttributeName : pfontMac->m_nsfont,
//         NSForegroundColorAttributeName : m_pbrushText,
//         NSParagraphStyleAttributeName : style
//      };
//
//      CGRect rc = CGRectMake(
//         rectangle.left,
//         rectangle.top,
//         rectangle.width(),
//         rectangle.height());
//
//      [nsstr drawInRect:rc
//         withAttributes:attributes];
//
//   }
 void cg_context::draw_line(const ::i32_point & point1, const ::i32_point & point2)
{
    
    cg_point cgpoint1;
    cgpoint1.x = point1.x;
    cgpoint1.y = point1.y;
    
    cg_point cgpoint2;
    cgpoint2.x = point2.x;
    cgpoint2.y = point2.y;

    cg_context_draw_line(m_cgcontext, cgpoint1, cgpoint2);
   
}

void cg_context::draw_rect(const ::i32_rectangle & rectangle)
{
   
   cg_rect cgrect;

   cgrect.origin.x = rectangle.left;
   cgrect.origin.y = rectangle.top;
   cgrect.size.w = rectangle.width();
   cgrect.size.h = rectangle.height();
   
   cg_context_draw_rect(m_cgcontext, cgrect);
   
}


void cg_context::fill_ellipse(const ::i32_rectangle & rectangle)
{
   
   cg_rect cgrect;

   cgrect.origin.x = rectangle.left;
   cgrect.origin.y = rectangle.top;
   cgrect.size.w = rectangle.width();
   cgrect.size.h = rectangle.height();

   cg_context_fill_ellipse(m_cgcontext, cgrect);
   
}

void cg_context::draw_ellipse(const ::i32_rectangle & rectangle)
{
   
   cg_rect cgrect;

   cgrect.origin.x = rectangle.left;
   cgrect.origin.y = rectangle.top;
   cgrect.size.w = rectangle.width();
   cgrect.size.h = rectangle.height();

   cg_context_draw_ellipse(m_cgcontext, cgrect);
   
}


void cg_context::fill_rect(const ::i32_rectangle & rectangle)
{
   
   cg_rect cgrect;

   cgrect.origin.x = rectangle.left;
   cgrect.origin.y = rectangle.top;
   cgrect.size.w = rectangle.width();
   cgrect.size.h = rectangle.height();

   cg_context_fill_rect(m_cgcontext, cgrect);
   
}


void cg_context::draw_image(::core_graphics::cg_image * pcgimage, const ::i32_rectangle & rectangle)
{
   
   cg_rect cgrect;

   cgrect.origin.x = rectangle.left;
   cgrect.origin.y = rectangle.top;
   cgrect.size.w = rectangle.width();
   cgrect.size.h = rectangle.height();

   cg_context_draw_image(m_cgcontext, pcgimage->m_cgimage, cgrect);
   
   
}



void cg_context::draw_image(::core_graphics::cg_image * pcgimage, const ::i32_point & point, const ::i32_rectangle & rectangle)
{

   cg_point cgpoint;

   cgpoint.x = point.x;
   cgpoint.y = point.y;

   cg_rect cgrect;

   cgrect.origin.x = rectangle.left;
   cgrect.origin.y = rectangle.top;
   cgrect.size.w = rectangle.width();
   cgrect.size.h = rectangle.height();

   cg_context_draw_image(m_cgcontext, pcgimage->m_cgimage, cgpoint, cgrect);
   
   
}


void cg_context::set_blend_mode_on(bool bSet)
{
   
   cg_context_set_blend_mode_on(m_cgcontext, bSet);
   
}

void cg_context::set_anti_alias_on(bool bSet)
{
   
   cg_context_set_anti_alias_on(m_cgcontext, bSet);
   
}


void cg_context::set_fill_color(::core_graphics::cg_color * pcgcolor)
{
   
   cg_context_set_fill_color_with_color(m_cgcontext, pcgcolor->m_cgcolor);
   
}


void cg_context::set_stroke_color(::core_graphics::cg_color * pcgcolor)
{
   
   cg_context_set_stroke_color_with_color(m_cgcontext, pcgcolor->m_cgcolor);
   
}

void cg_context::set_line_width(float fWidth)
{
   
   cg_context_set_line_width(m_cgcontext, fWidth);
   
}


void cg_context::draw_text(
      const ::scoped_string & scopedstr,
      const ::i32_rectangle & rectangle,
      cg_color * pcgcolor,
      ::core_text::ct_font * pctfont,
      unsigned int format,
      enum_align ealign)
{
   
   
   cg_rect cgrect;
   
   cgrect.origin.x = rectangle.left;
   cgrect.origin.y = rectangle.top;
   cgrect.size.w = rectangle.width();
   cgrect.size.h = rectangle.height();
   
   
   cg_context_draw_text(
                        m_cgcontext,
                        scopedstr.c_str(), scopedstr.length(),
                        cgrect,
                        pcgcolor->m_cgcolor,
                        pctfont->m_ctfont,
                        format,
                        ealign
                        );
   
   }


} // namespace core_graphics
