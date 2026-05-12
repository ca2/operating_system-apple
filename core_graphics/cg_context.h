//
//  cg_context.h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/26.
//
#pragma once
//
// Graphics.mm
// Objective-C++ macOS implementation using CoreGraphics/CoreText
//

//#import <Cocoa/Cocoa.h>
//#import <CoreText/CoreText.h>

namespace core_graphics
{

//struct cg_context_t
//{
//   
//   ::uptr m_u;
//   
//};
//
//
//   constexpr int TRANSPARENT = 1;
//   constexpr int OPAQUE = 2;

   class CLASS_DECL_CORE_GRAPHICS cg_context :
virtual public ::particle
   {
   public:
      
      
      cg_context_t m_cgcontext;
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
//
      
      virtual void draw_line(const ::i32_point & point1, const ::i32_point & point2);
      virtual void draw_rect(const ::i32_rectangle & rectangle);
      virtual void fill_rect(const ::i32_rectangle & rectangle);
      virtual void draw_ellipse(const ::i32_rectangle & rectangle);
      virtual void fill_ellipse(const ::i32_rectangle & rectangle);
      virtual void draw_image(::core_graphics::cg_image * pcgimage, const ::i32_rectangle & rectangle);
      virtual void draw_image(::core_graphics::cg_image * pcgimage, const ::i32_point& point, const ::i32_rectangle & rectangle);
      virtual void set_blend_mode_on(bool bSet);
      virtual void set_anti_alias_on(bool bSet);
      virtual void set_line_width(int iWidth);
      virtual void set_stroke_color(::core_graphics::cg_color * pcgcolor);
      virtual void set_fill_color(::core_graphics::cg_color * pcgcolor);
      
   };
} // namespace innate_subsystem_macos
