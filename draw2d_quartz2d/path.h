#pragma once


#include "object.h"
#include "aura/graphics/draw2d/path.h"


namespace draw2d_quartz2d
{
   
   
   class CLASS_DECL_DRAW2D_QUARTZ2D path :
      virtual public ::draw2d::path,
      virtual public object
   {
   public:
      
      
      CGMutablePathRef        m_path;
      bool                    m_bBegin;
      
      
      path();
      ~path() override;
      
      
      virtual bool internal_begin_figure(bool bFill, ::draw2d::enum_fill_mode efillmode);
      virtual bool internal_close(bool bClose);
      virtual bool internal_add_arc(const ::double_rectangle & rectangle, double dStart, double dAngle, bool bClockwise);
      virtual bool internal_add_line(double x1, double y1, double x2, double y2);
      virtual bool internal_add_line(double x, double y);
      virtual bool internal_add_move(double x, double y);
      virtual bool internal_add_text_out(double x, double y, const string & strText, ::write_text::font * pfont, ::draw2d_quartz2d::graphics * p);
      
      void create(::draw2d::graphics * pgraphics, char iCreate) override;

      void destroy() override;
      void destroy_os_data() override;

      void * detach() override;
      
      bool _set(::draw2d::graphics * pgraphics, const ::draw2d::enum_item & eitem) override;
      bool _set(::draw2d::graphics * pgraphics, const ::double_arc & arc) override;
      bool _set(::draw2d::graphics * pgraphics, const ::double_rectangle & rectangle) override;
      bool _set(::draw2d::graphics * pgraphics, const ::double_ellipse & ellipse) override;
      bool _set(::draw2d::graphics * pgraphics, const ::double_line & double_line) override;
      bool _set(::draw2d::graphics * pgraphics, const ::double_lines & lines) override;
      bool _set(::draw2d::graphics * pgraphics, const ::double_polygon & polygon) override;
      bool _set(::draw2d::graphics * pgraphics, const ::write_text::text_out & textout) override;
      bool _set(::draw2d::graphics * pgraphics, const ::write_text::draw_text & drawtext) override;
   
      bool contains(::draw2d::graphics_pointer & pgraphics, const ::double_point & point) override;
      
      
   };
   
   
} // namespace draw2d_quartz2d



