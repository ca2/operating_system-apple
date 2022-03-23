#include "framework.h"


namespace draw2d_quartz2d
{
   
   
   path::path()
   {
      
      m_path = nullptr;
      
      m_bBegin = true;
      
   }
   
   
   path::~path()
   {
      
      
   }
   
   
   bool path::internal_begin_figure(bool bFill, ::draw2d::enum_fill_mode efillmode)
   {
      
      m_bBegin = true;
      
      return true;
      
   }
   
   
   bool path::internal_close(bool bClose)
   {
      
      if(bClose)
      {
         
         CGPathCloseSubpath(m_path);
         
      }
      
      m_bBegin = true;
      
      return true;
      
   }
   
   
   bool path::internal_add_arc(const ::rectangle_f64 & rectangle, double dBeg, double dEnd, bool bClockwise)
   {
      
      CGFloat d1 = rectangle.right - rectangle.left;
      
      if(d1 <= 0)
         return true;
      
      CGFloat d2 = rectangle.bottom - rectangle.top;
      
      if(d2 <= 0)
         return true;
      
      CGFloat x = (rectangle.right + rectangle.left) / 2.0;
   
      CGFloat y = (rectangle.bottom + rectangle.top) / 2.0;
   
      if(d1 == d2)
      {
         
         CGPathAddArc(m_path, nullptr, x, y, d1/2.0, dBeg, dEnd, bClockwise ? 1 : 0);

      }
      else
      {
      
         CGAffineTransform t = CGAffineTransformMakeScale(1.0, d2 / d1);
      
//      CGFloat x1 = x + d1 * cos(dBeg);
//      
//      CGFloat y1 = y + d1 * sin(dBeg);
      
//      if(CGPathIsEmpty(m_path))
//      {
//
//         internal_add_move(x1, y1);
//
//      }
      
         CGPathAddArc(m_path, &t, x, y, d1/2.0, dBeg, dEnd, bClockwise ? 1 : 0);
         
      }
      
      return true;
      
   }
   
   
   bool path::internal_add_line(double x1, double y1, double x2, double y2)
   {
      
      x1+= m_pointOffset.x;
      y1+= m_pointOffset.y;
      x2+= m_pointOffset.x;
      y2+= m_pointOffset.y;

      if(CGPathIsEmpty(m_path))
      {
         
         internal_add_move(x1, y1);
         
      }
      else
      {
      
         CGPathAddLineToPoint(m_path, nullptr, x1, y1);
         
      }

      CGPathAddLineToPoint(m_path, nullptr, x2, y2);
      
      m_pointBegin.x = x1;
      m_pointBegin.y = y1;
      m_pointEnd.x = x2;
      m_pointEnd.y = y2;
      
      
      return true;
      
   }
   
   
   bool path::internal_add_line(double x, double y)
   {
      
      x+= m_pointOffset.x;
      y+= m_pointOffset.y;
      
      m_pointBegin = m_pointEnd;
      
      if(CGPathIsEmpty(m_path))
      {
         
         internal_add_move(x, y);
         
      }
      else
      {
         
         CGPathAddLineToPoint(m_path, nullptr, x, y);
         
      }
      
      m_pointEnd.x = x;
      m_pointEnd.y = y;
      
      
      return true;
      
   }


   bool path::internal_add_text_out(double x, double y, const string & strText, ::write_text::font * pfont, ::draw2d_quartz2d::graphics * p)
   {
      
      x+= m_pointOffset.x;
      y+= m_pointOffset.y;
      
      CGContextSaveGState(p->m_pdc);
      
      p->internal_show_text(x, y, 0, strText, kCGTextInvisible, e_align_top_left, e_draw_text_none, true,
         nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
         pfont);
      
      CGPathAddPath(m_path, nullptr, CGContextCopyPath(p->m_pdc));

      CGContextSaveGState(p->m_pdc);

      return true;
      
   }
   

   bool path::internal_add_move(double x, double y)
   {
      
      x+= m_pointOffset.x;
      y+= m_pointOffset.y;
      
      m_pointBegin = m_pointEnd;
      
      
      CGPathMoveToPoint(m_path, nullptr, x, y);
      
      m_pointEnd.x = x;
      m_pointEnd.y = y;
      
      m_bBegin = false;
      
      return true;
      
   }
   
   
   void * path::detach()
   {
      
      void * ppath = m_path;
      
      m_path = nullptr;
      m_osdata[0] = nullptr;
      
      return ppath;
      
   }
   
   
   void path::destroy()
   {
      
      //auto estatusOsData =
      destroy_os_data();
      
      //auto estatusDestroy =
      ::draw2d::path::destroy();
      
      //return estatusOsData && estatusDestroy;
      
   }
   
   
   void path::destroy_os_data()
   {
      
      if(m_path != nullptr)
      {
         
         CGPathRelease(m_path);
         
         m_path = nullptr;
         
      }
      
      //return ::success;
      
   }


   void path::create(::draw2d::graphics * pgraphics, i8 iCreate)
   {
      
      m_path = CGPathCreateMutable();
      
      _set_create(pgraphics);
      
      m_osdata[0] = m_path;
      
      //return true;
      
   }

   
   bool path::_set(::draw2d::graphics * pgraphics, const ::enum_shape & eshape)
   {
      
      if(eshape == e_shape_close_figure)
      {
         
         CGPathCloseSubpath(m_path);
         
      }

      return true;
      
   }


   bool path::_set(::draw2d::graphics * pgraphics, const ::arc & arc)
   {
   
      ::rectangle_f64 rectangle;
      
      rectangle.left = arc.m_pointCenter.x - arc.m_sizeRadius.cx;
      rectangle.right = arc.m_pointCenter.x + arc.m_sizeRadius.cx;
      rectangle.top = arc.m_pointCenter.y - arc.m_sizeRadius.cy;
      rectangle.bottom = arc.m_pointCenter.y + arc.m_sizeRadius.cy;
      
      rectangle.offset(m_pointOffset);
      
      return internal_add_arc(rectangle, arc.m_angleBeg.radian(), arc.m_angleEnd2.radian(), arc.m_angleEnd2 < arc.m_angleBeg);
      
   }
   

   
   bool path::_set(::draw2d::graphics * pgraphics, const ::rectangle & rectangle)
   {
   
      CGRect r;
      
      r.origin.x = rectangle.left;
      r.origin.y = rectangle.top;
      r.size.width = rectangle.width();
      r.size.height = rectangle.height();
      
      r.origin.x += m_pointOffset.x;
      r.origin.y += m_pointOffset.y;
      
      CGPathAddRect(m_path, nullptr, r);
                    
      return true;
      
   }
         

   bool path::_set(::draw2d::graphics * pgraphics, const ::ellipse & ellipse)
   {

      CGRect r;
      
      r.origin.x = ellipse.left;
      r.origin.y = ellipse.top;
      r.size.width = ellipse.width();
      r.size.height = ellipse.height();
      
      r.origin.x += m_pointOffset.x;
      r.origin.y += m_pointOffset.y;
      
      CGPathAddEllipseInRect(m_path, nullptr, r);
                    
      return true;
      
   }

   bool path::_set(::draw2d::graphics * pgraphics, const ::lines & lines)
   {
   
      ::array < CGPoint > points;
      
      ::papaya::array::__copy(points, lines);
      
      for(auto & point : points)
      {
         
         point.x += m_pointOffset.x;
         point.y += m_pointOffset.y;
         
      }
      
      CGPathAddLines(m_path, nullptr, points.get_data(), points.get_count());
                    
      return true;
      
   }
                    

   bool path::_set(::draw2d::graphics * pgraphics, const ::polygon & polygon)
   {

      ::array < CGPoint > points;
      
      ::papaya::array::__copy(points, polygon);
      
      for(auto & point : points)
      {
         
         point.x += m_pointOffset.x;
         point.y += m_pointOffset.y;
         
      }
      
      CGPathAddLines(m_path, nullptr, points.get_data(), points.get_count());

      CGPathCloseSubpath(m_path);
      
      return true;
      
   }


   bool path::_set(::draw2d::graphics * pgraphics, const ::line & line)
   {
      
      if(line.m_p1 != m_pointEnd)
      {
         
         internal_add_move(line.m_p1.x, line.m_p1.y);
         
      }
      
      return internal_add_line(line.m_p2.x, line.m_p2.y);
      
   }


   bool path::_set(::draw2d::graphics * pgraphics, const ::write_text::text_out & textout)
   {
      
      return false;
      
   }
   

   bool path::_set(::draw2d::graphics * pgraphics, const ::write_text::draw_text & drawtext)
   {
      
      return false;
      
   }
   

//   bool path::_set(::draw2d::graphics * pgraphics, ::draw2d::path::close * pclose)
//   {
//
//      CGPathCloseSubpath(m_path);
//
//      return true;
//
//   }



   bool path::contains(::draw2d::graphics_pointer & pgraphics, const ::point_f64 & point)
   {
    
      CGMutablePathRef ppath = get_os_data <CGMutablePathRef>(pgraphics);
      
      if(::is_null(ppath))
      {
         
         return false;
         
      }
      
      return CGPathContainsPoint(ppath, nullptr,CGPointMake(point.x, point.y), false);
      
   }

   
} // namespace metrowin




