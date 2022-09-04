#pragma once


#include "aura/graphics/write_text/font.h"


namespace draw2d_quartz2d
{
   
   
   class CLASS_DECL_DRAW2D_QUARTZ2D font :
      virtual public ::write_text::font
   {
   public:
   
//      class metrics
//      {
//      public:
//
//
//         CGFloat ascent;
//         CGFloat descent;
//         CGFloat leading;
//         CGFloat width;
//
//         // mode, brush color, pen color
//         map < CGTextDrawingMode, colorrefmap < colorrefmap < CTLineRef > > > m_map;
//
//
//         metrics() {}
//         ~metrics() {}
//
//         void get(CGFloat * pascent, CGFloat * pdescent, CGFloat * pleading, CGFloat * pwidth);
//
//         void align(double & x, double & y, double wAlign, const ::e_align & ealign = e_align_top_left, const ::e_draw_text & edrawtext = e_draw_text_none);
//
//      };
      
//      string_map < metrics >  m_mapMetrics;
      CTFontRef               m_font;
      CTFontDescriptorRef     m_fontdescriptor;
      CFStringRef             m_fontName;
      
      
      font();
      ~font() override;
      
      
      void destroy() override;
      void destroy_os_data() override;
      void create(::draw2d::graphics * pgraphics, i8 iCreate) override;

      //virtual void * get_os_data() const override;
      
      void dump(dump_context & dumpcontext) const override;
      
      double get_ascent(::draw2d::graphics * pgraphics) override;
      
      double get_descent(::draw2d::graphics * pgraphics) override;
      
      double get_leading(::draw2d::graphics * pgraphics) override;
      
      double get_height(::draw2d::graphics * pgraphics) override;
      
      
   };
   
   
} // namespace draw2d_quartz2d



