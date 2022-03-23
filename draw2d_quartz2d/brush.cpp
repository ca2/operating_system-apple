#include "framework.h"


namespace draw2d_quartz2d
{
   
   
   brush::brush()
   {
      
      m_colorspaceref = nullptr;
      
      m_colorref = nullptr;
      
      m_gradientref = nullptr;
      
   }
   
   
   brush::~brush()
   {
   }
   

   void brush::dump(dump_context & dumpcontext) const
   {
      
      ::draw2d::object::dump(dumpcontext);
      
   }

   
   void brush::destroy()
   {
      
//      auto estatusOsData =
      destroy_os_data();
      
//      /auto estatusDestroy =
      ::draw2d::brush::destroy();
      
//      return estatusOsData && estatusDestroy;
      
   }


   void brush::destroy_os_data()
   {
      
      if(m_gradientref != nullptr)
      {
         
         CGGradientRelease(m_gradientref);
         
         m_gradientref = nullptr;
         
      }
      
      if(m_colorref != nullptr)
      {
         
         CGColorRelease(m_colorref);
         
         m_colorref = nullptr;
         
      }
      
      if(m_colorspaceref != nullptr)
      {
         
         CGColorSpaceRelease(m_colorspaceref);
         
         m_colorspaceref = nullptr;
         
      }
      
      //return ::success;
      
   }

   
   void brush::create(::draw2d::graphics * pgraphics, i8 iCreate)
   {
      
      if(m_ebrush == ::draw2d::e_brush_linear_gradient_point_color || m_ebrush == ::draw2d::e_brush_radial_gradient_color || m_ebrush == ::draw2d::e_brush_box_gradient)
      {
         
         CGFloat locations[2];
         CGFloat components[8];
         
         //      CGColorSpaceRef colorspace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
         
         if(m_colorspaceref == nullptr)
         {
         
            m_colorspaceref = CGColorSpaceCreateDeviceRGB();
            
         }
         
         components[0] = m_color1.red / 255.f;
         components[1] = m_color1.green / 255.f;
         components[2] = m_color1.blue / 255.f;
         components[3] = m_color1.alpha / 255.f;
         components[4] = m_color2.red / 255.f;
         components[5] = m_color2.green / 255.f;
         components[6] = m_color2.blue / 255.f;
         components[7] = m_color2.alpha / 255.f;
         
         locations[0] = 0.0;
         locations[1] = 1.0;
         
         m_gradientref = CGGradientCreateWithColorComponents(m_colorspaceref, components, locations, 2);
         
         m_osdata[0] = m_gradientref;
         
      }
      else if(m_ebrush == ::draw2d::e_brush_solid)
      {

         CGFloat components[4];
         
         //      CGColorSpaceRef colorspace = CGColorSpaceCreateWithName(kCGColorSpaceGenericRGB);
         
         if(m_colorspaceref == nullptr)
         {
            
            m_colorspaceref = CGColorSpaceCreateDeviceRGB();
            
         }

         components[0] = m_color.red / 255.f;
         components[1] = m_color.green / 255.f;
         components[2] = m_color.blue / 255.f;
         components[3] = m_color.alpha / 255.f;
         
         m_colorref = CGColorCreate(m_colorspaceref, components);
         
         m_osdata[0] = m_colorref;
         
      }
      
      //return true;
      
   }
   

} // namespace draw2d_quartz2d



