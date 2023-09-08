#include "framework.h"
#include "path.h"
#include "graphics.h"
#include "acme/primitive/collection/_generic_array.h"
#include "acme/primitive/geometry2d/arc.h"
#include "acme/primitive/geometry2d/line.h"
//void copy(::draw2d::graphics * pgraphics, const ::lines & lines)
//{
//
//   ::array < CGPoint > points;
//
//   ::copy(points, lines);
//
//   for(auto & point : points)
//   {
//
//      point.x += m_pointOffset.x;
//      point.y += m_pointOffset.y;
//
//   }

namespace draw2d_quartz2d
{
   
   
   path::path()
   {
      
      m_path = nullptr;
      
      m_bBegin = true;
      
   }
   
   
   path::~path()
   {
      
      destroy();
      
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
      
      CGFloat d1 = rectangle.right() - rectangle.left();
      
      if(d1 <= 0)
         return true;
      
      CGFloat d2 = rectangle.bottom() - rectangle.top();
      
      if(d2 <= 0)
         return true;
      
      CGFloat x = (rectangle.right() + rectangle.left()) / 2.0;
   
      CGFloat y = (rectangle.bottom() + rectangle.top()) / 2.0;
   
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
      
      x1+= m_pointOffset.x();
      y1+= m_pointOffset.y();
      x2+= m_pointOffset.x();
      y2+= m_pointOffset.y();

      if(CGPathIsEmpty(m_path))
      {
         
         internal_add_move(x1, y1);
         
      }
      else
      {
      
         CGPathAddLineToPoint(m_path, nullptr, x1, y1);
         
      }

      CGPathAddLineToPoint(m_path, nullptr, x2, y2);
      
      m_pointBegin.x() = x1;
      m_pointBegin.y() = y1;
      m_pointEnd.x() = x2;
      m_pointEnd.y() = y2;
      
      return true;
      
   }
   
   
   bool path::internal_add_line(double x, double y)
   {
      
      x+= m_pointOffset.x();
      y+= m_pointOffset.y();
      
      m_pointBegin = m_pointEnd;
      
      if(CGPathIsEmpty(m_path))
      {
         
         internal_add_move(x, y);
         
      }
      else
      {
         
         CGPathAddLineToPoint(m_path, nullptr, x, y);
         
      }
      
      m_pointEnd.x() = x;
      m_pointEnd.y() = y;
      
      
      return true;
      
   }


   bool path::internal_add_text_out(double x, double y, const string & strText, ::write_text::font * pfont, ::draw2d_quartz2d::graphics * p)
   {
      
      x+= m_pointOffset.x();
      y+= m_pointOffset.y();
      
      CGContextSaveGState(p->m_cgcontext);
      
      p->internal_show_text(x, y, 0, strText, kCGTextInvisible, e_align_top_left, e_draw_text_none, true,
         nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
         pfont);
      
      CGPathAddPath(m_path, nullptr, CGContextCopyPath(p->m_cgcontext));

      CGContextSaveGState(p->m_cgcontext);

      return true;
      
   }
   

   bool path::internal_add_move(double x, double y)
   {
      
      x+= m_pointOffset.x();
      y+= m_pointOffset.y();
      
      m_pointBegin = m_pointEnd;
      
      CGPathMoveToPoint(m_path, nullptr, x, y);
      
      m_pointEnd.x() = x;
      m_pointEnd.y() = y;
      
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
      
      destroy_os_data();
      
      ::draw2d::path::destroy();
      
   }
   
   
   void path::destroy_os_data()
   {
      
      if(m_path != nullptr)
      {
         
         CGPathRelease(m_path);
         
         m_path = nullptr;
         
      }
      
   }


   void path::create(::draw2d::graphics * pgraphics, i8 iCreate)
   {
      
      if(m_path)
      {
         
         throw "";
         
      }
      
      m_path = CGPathCreateMutable();
      
      _set_create(pgraphics);
      
      m_osdata[0] = m_path;
      
   }

   
   bool path::_set(::draw2d::graphics * pgraphics, const ::draw2d::enum_item & eitem)
   {
      
      if(eitem == ::draw2d::e_item_close_figure)
      {
         
         if(CGPathIsEmpty(m_path))
         {
            
            return true;
            
         }
         
         CGPathCloseSubpath(m_path);
         
      }

      return true;
      
   }


   bool path::_set(::draw2d::graphics * pgraphics, const ::arc_f64 & arc)
   {
   
      ::rectangle_f64 rectangle;
      
      rectangle = arc;
      
      rectangle.offset(m_pointOffset);
      
      return internal_add_arc(rectangle, arc.m_angleBeg.radian(), arc.m_angleEnd2.radian(), arc.m_angleEnd2 < arc.m_angleBeg);
      
   }
   

   
   bool path::_set(::draw2d::graphics * pgraphics, const ::rectangle_f64 & rectangle)
   {
   
      CGRect r;
      
      r.origin.x = rectangle.left();
      r.origin.y = rectangle.top();
      r.size.width = rectangle.width();
      r.size.height = rectangle.height();
      
      r.origin.x += m_pointOffset.x();
      r.origin.y += m_pointOffset.y();
      
      CGPathAddRect(m_path, nullptr, r);
                    
      return true;
      
   }
         

   bool path::_set(::draw2d::graphics * pgraphics, const ::ellipse_f64 & ellipse)
   {

      CGRect r;
      
      r.origin.x = ellipse.left();
      r.origin.y = ellipse.top();
      r.size.width = ellipse.width();
      r.size.height = ellipse.height();
      
      r.origin.x += m_pointOffset.x();
      r.origin.y += m_pointOffset.y();
      
      CGPathAddEllipseInRect(m_path, nullptr, r);
                    
      return true;
      
   }

   bool path::_set(::draw2d::graphics * pgraphics, const ::lines_f64 & lines)
   {
   
      ::array < CGPoint > points;
      
      ::generic::array::copy(points, lines);
      
      for(auto & point : points)
      {
         
         point.x += m_pointOffset.x();
         point.y += m_pointOffset.y();
         
      }
      
      CGPathAddLines(m_path, nullptr, points.data(), points.count());
                    
      return true;
      
   }
                    

   bool path::_set(::draw2d::graphics * pgraphics, const ::polygon_f64 & polygon)
   {

      ::array < CGPoint > points;
      
      ::generic::array::copy(points, polygon);
      
      for(auto & point : points)
      {
         
         point.x += m_pointOffset.x();
         point.y += m_pointOffset.y();
         
      }
      
      CGPathAddLines(m_path, nullptr, points.data(), points.count());

      CGPathCloseSubpath(m_path);
      
      return true;
      
   }


   bool path::_set(::draw2d::graphics * pgraphics, const ::line_f64 & line)
   {
      
      if(line.m_p1 != m_pointEnd)
      {
         
         internal_add_move(line.m_p1.x(), line.m_p1.y());
         
      }
      
      return internal_add_line(line.m_p2.x(), line.m_p2.y());
      
   }


   bool path::_set(::draw2d::graphics * pgraphics, const ::write_text::text_out & textout)
   {
      
      return false;
      
   }
   

   bool path::_set(::draw2d::graphics * pgraphics, const ::write_text::draw_text & drawtext)
   {
      
      return false;
      
   }
   

   bool path::contains(::draw2d::graphics_pointer & pgraphics, const ::point_f64 & point)
   {
    
      CGMutablePathRef ppath = get_os_data <CGMutablePathRef>(pgraphics);
      
      if(::is_null(ppath))
      {
         
         return false;
         
      }
      
      return CGPathContainsPoint(ppath, nullptr,CGPointMake(point.x(), point.y()), false);
      
   }

   
} // namespace draw2d_quartz2d



