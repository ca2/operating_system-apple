#include "framework.h"
#include "brush.h"


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
      
      destroy();
      
   }
   

//   void brush::dump(dump_context & dumpcontext) const
//   {
//      
//      ::draw2d::object::dump(dumpcontext);
//      
//   }
//
//   
   void brush::destroy()
   {
      
      destroy_os_data();
      
      ::draw2d::brush::destroy();
      
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
      
   }

   
   void brush::create(::draw2d::graphics * pgraphics, i8 iCreate)
   {
      
      if(m_ebrush == ::draw2d::e_brush_linear_gradient_point_color || m_ebrush == ::draw2d::e_brush_radial_gradient_color || m_ebrush == ::draw2d::e_brush_box_gradient)
      {
         
         CGFloat locations[2];
         CGFloat components[8];
         
         if(m_colorspaceref == nullptr)
         {
         
            m_colorspaceref = CGColorSpaceCreateDeviceRGB();
            
         }
         
         components[0] = m_color1.f32_red();
         components[1] = m_color1.f32_green();
         components[2] = m_color1.f32_blue();
         components[3] = m_color1.f32_opacity();
         components[4] = m_color2.f32_red();
         components[5] = m_color2.f32_green();
         components[6] = m_color2.f32_blue();
         components[7] = m_color2.f32_opacity();
         
         locations[0] = 0.0;
         locations[1] = 1.0;
         
         if(m_gradientref)
         {
            
            throw "";
            
         }
         
         m_gradientref = CGGradientCreateWithColorComponents(m_colorspaceref, components, locations, 2);
         
         m_osdata[0] = m_gradientref;
         
      }
      else if(m_ebrush == ::draw2d::e_brush_solid)
      {

         CGFloat components[4];
         
         if(m_colorspaceref == nullptr)
         {
            
            m_colorspaceref = CGColorSpaceCreateDeviceRGB();
            
         }

         components[0] = m_color.f32_red();
         components[1] = m_color.f32_green();
         components[2] = m_color.f32_blue();
         components[3] = m_color.f32_opacity();
         
         if(m_colorref)
         {
            
            throw "";
            
         }
         
         m_colorref = CGColorCreate(m_colorspaceref, components);
         
         m_osdata[0] = m_colorref;
         
      }
      
   }
   

} // namespace draw2d_quartz2d



