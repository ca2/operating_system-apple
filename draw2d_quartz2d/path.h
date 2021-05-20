#pragma once


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
      virtual ~path();
      
      
      virtual bool internal_begin_figure(bool bFill, ::draw2d::enum_fill_mode efillmode);
      virtual bool internal_close(bool bClose);
      virtual bool internal_add_arc(const ::rectangle_f64 & rectangle, double dStart, double dAngle, bool bClockwise);
      virtual bool internal_add_line(int x1, int y1, int x2, int y2);
      virtual bool internal_add_line(int x, int y);
      virtual bool internal_add_move(int x, int y);
      virtual bool internal_add_text_out(int x, int y, const string & strText, ::write_text::font * pfont, ::draw2d_quartz2d::graphics * p);
      
      //virtual void * get_os_data() const;
      
      virtual bool create(::draw2d::graphics * pgraphics, i8 iCreate) override;

      virtual void destroy() override;

      virtual void * detach() override;
      
      //bool set(const ::draw2d::path::matter & e);
      bool _set(::draw2d::graphics * pgraphics, const enum_shape & eshape) override;
      bool _set(::draw2d::graphics * pgraphics, const ::arc & arc) override;
      bool _set(::draw2d::graphics * pgraphics, const ::rectangle & rectangle) override;
      //bool set(::draw2d::path::move * pmove);
      bool _set(::draw2d::graphics* pgraphics, const ::line & line) override;
      bool _set(::draw2d::graphics* pgraphics, const ::lines & lines) override;
      bool _set(::draw2d::graphics* pgraphics, const ::polygon & polygon) override;
      bool _set(::draw2d::graphics* pgraphics, const ::write_text::text_out & textout) override;
      bool _set(::draw2d::graphics* pgraphics, const ::write_text::draw_text & drawtext) override;
      //bool _set(::draw2d::graphics* pgraphics, ::draw2d::path::close * pclose) override;
   
      virtual bool contains(::draw2d::graphics_pointer & pgraphics, const ::point_f64 & point) override;
      
      
   };
   
   
} // namespace draw2d_quartz2d





