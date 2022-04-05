#include "framework.h"


namespace draw2d_quartz2d
{


   region::region()
   {

   }


   region::~region()
   {
      
      destroy();
      
   }


   void region::destroy()
   {

      destroy_os_data();
      
      ::draw2d::region::destroy();
      
   }


   void region::destroy_os_data()
   {
      
      if(m_path != nullptr)
      {

         CGPathRelease(m_path);

         m_path = nullptr;

      }
      
   }


   void region::create(::draw2d::graphics * pgraphics, i8 iCreate)
   {

      auto ppath = CGPathCreateMutable();

      if(m_eregion == ::draw2d::e_region_rect)
      {

         CGRect rectangle;

         rectangle.origin.x = m_x1;
         rectangle.origin.y = m_y1;
         rectangle.size.width = m_x2 - m_x1;
         rectangle.size.height = m_y2 - m_y1;
         
         CGPathAddRect (ppath, nullptr, rectangle);

      }
      else if(m_eregion == ::draw2d::e_region_polygon)
      {

         CGPathMoveToPoint(ppath, nullptr, m_lppoints[0].x, m_lppoints[0].y);

         for(i32 i = 1; i < m_nCount; i++)
         {

            CGPathAddLineToPoint(ppath, nullptr, m_lppoints[i].x, m_lppoints[i].y);

         }

      }
      else if(m_eregion == ::draw2d::e_region_ellipse)
      {

         CGRect rectangle;

         rectangle.origin.x = m_x1;
         rectangle.origin.y = m_y1;
         rectangle.size.width = m_x2 - m_x1;
         rectangle.size.height = m_y2 - m_y1;

         CGPathAddEllipseInRect(ppath, nullptr, rectangle);

      }
      else if(m_eregion == ::draw2d::e_region_combine)
      {

         throw ::exception(error_not_supported, "not supported");

      }

      CGPathCloseSubpath(ppath);
      
      CGAffineTransform transformTranslation = CGAffineTransformMakeTranslation(m_pointOffset.x, m_pointOffset.y);
      
      m_path = CGPathCreateMutableCopyByTransformingPath(ppath, &transformTranslation);
      
      CGPathRelease(ppath);

   }


   void * region::detach()
   {

      void * ppath = m_path;

      m_path = nullptr;

      return ppath;

   }


} // namespace draw2d_quartz2d



