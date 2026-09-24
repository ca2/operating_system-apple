#include "framework.h"
#include "region.h"
#include "acme/prototype/geometry2d/item.h"
#include "acme/prototype/geometry2d/_defer_item.h"


namespace draw2d_quartz2d
{


   region::region()
   {

   }


   region::~region()
   {
      
      destroy();
      
   }


//   void region::destroy()
//   {
//
//      destroy_os_data();
//      
//      ::draw2d::region::destroy();
//      
//   }


   void region::destroy()
   {
      
      m_cgmutablepathref.release();
      
   }


   void region::update(::draw2d::graphics * pgraphics)
   {

      auto cgmutablepathref = ::as_cfref(CGPathCreateMutable());

      if(m_pitem->type() == ::draw2d::e_item_rectangle)
      {

         CGRect rectangle;
         
         ::pointer < ::geometry2d::rectangle_item > pitem = m_pitem;

         copy(rectangle, pitem->m_item);
//         rectangle.origin.x = m_x1;
//         rectangle.origin.y = m_y1;
//         rectangle.size.width = m_x2 - m_x1;
//         rectangle.size.height = m_y2 - m_y1;
         
         CGPathAddRect (cgmutablepathref, nullptr, rectangle);

      }
      else if(m_pitem->type() == ::draw2d::e_item_polygon)
      {

         ::pointer < ::geometry2d::polygon_item > pitem = m_pitem;

         if(pitem->m_polygon.has_element())
         {
            
            CGPathMoveToPoint(cgmutablepathref, nullptr, pitem->m_polygon[0].x, pitem->m_polygon[0].y);

            for(int i = 1; i < pitem->m_polygon.size(); i++)
            {

               CGPathAddLineToPoint(cgmutablepathref, nullptr, pitem->m_polygon[i].x, pitem->m_polygon[i].y);

            }

         }
         
      }
      else if(m_pitem->type() == ::draw2d::e_item_ellipse)
      {

         CGRect rectangle;
         
         ::pointer < ::geometry2d::ellipse_item > pitem = m_pitem;

         copy(rectangle, pitem->m_item);
//         rectangle.origin.x = m_x1;
//         rectangle.origin.y = m_y1;
//         rectangle.size.width = m_x2 - m_x1;
//         rectangle.size.height = m_y2 - m_y1;

         CGPathAddEllipseInRect(cgmutablepathref, nullptr, rectangle);

      }
      else if(m_pitem->type() == ::draw2d::e_item_combine)
      {

         throw ::exception(error_not_supported, "not supported");

      }

      CGPathCloseSubpath(cgmutablepathref);
      
      CGAffineTransform transformTranslation = CGAffineTransformMakeTranslation(m_pointOffset.x, m_pointOffset.y);
      
      m_cgmutablepathref = CGPathCreateMutableCopyByTransformingPath(cgmutablepathref, &transformTranslation);
      
      //CGPathRelease(ppath);

   }


   CGMutablePathRef region::_detach()
   {

      return m_cgmutablepathref.detach();

   }


} // namespace draw2d_quartz2d



