#include "framework.h"


namespace draw2d_quartz2d
{


   region::region()
   {

   }


   region::~region()
   {

   }


   ::e_status region::destroy()
   {

      auto estatusOsData = destroy_os_data();
      
      auto estatusDestroy = ::draw2d::region::destroy();
      
      return estatusOsData && estatusDestroy;

   }


   ::e_status region::destroy_os_data()
   {
      
      if(m_path != nullptr)
      {

         CGPathRelease(m_path);

         m_path = nullptr;

      }
      
      return ::success;
      
   }


   bool region::create(::draw2d::graphics * pgraphics, i8 iCreate)
   {

      m_path = CGPathCreateMutable();

      if(m_eregion == ::draw2d::e_region_rect)
      {

         CGRect rectangle;

         rectangle.origin.x = m_x1;
         rectangle.origin.y = m_y1;
         rectangle.size.width = m_x2 - m_x1;
         rectangle.size.height = m_y2 - m_y1;
         
         CGPathAddRect (m_path, nullptr, rectangle);

      }
      else if(m_eregion == ::draw2d::e_region_polygon)
      {

         CGPathMoveToPoint(m_path, nullptr, m_lppoints[0].x, m_lppoints[0].y);

         for(i32 i = 1; i < m_nCount; i++)
         {

            CGPathAddLineToPoint(m_path, nullptr, m_lppoints[i].x, m_lppoints[i].y);

         }

      }
      else if(m_eregion == ::draw2d::e_region_ellipse)
      {

         CGRect rectangle;

         rectangle.origin.x = m_x1;
         rectangle.origin.y = m_y1;
         rectangle.size.width = m_x2 - m_x1;
         rectangle.size.height = m_y2 - m_y1;

         CGPathAddEllipseInRect(m_path, nullptr, rectangle);

      }
      else if(m_eregion == ::draw2d::e_region_combine)
      {

         throw ::exception(error_not_supported, "not supported");

      }

      CGPathCloseSubpath(m_path);
      
      CGAffineTransform transformTranslation = CGAffineTransformMakeTranslation(m_pointOffset.x, m_pointOffset.y);
      
      m_path = CGPathCreateMutableCopyByTransformingPath(m_path, &transformTranslation);

      return true;

   }


   void * region::detach()
   {

      void * ppath = m_path;

      m_path = nullptr;

      return ppath;

   }


} // namespace draw2d_quartz2d



