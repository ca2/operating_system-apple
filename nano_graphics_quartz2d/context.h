//
// Created by camilo on 31/01/2022 20:15 <3ThomasBorregaardSorensen!! Thomas Likes number 5!!
//
#pragma once


#include "acme/nano/graphics/context.h"


//#include <CoreGraphics/CoreGraphics.h>

template < typename CORE_FOUNDATION_TYPE >
class core_foundation_reference
{
public:
   
   CORE_FOUNDATION_TYPE      m_cftype;
   
   core_foundation_reference()
   {
      m_cftype = nullptr;
   }
   core_foundation_reference(CORE_FOUNDATION_TYPE cftype)
   {
      m_cftype = cftype;
   }

   ~core_foundation_reference()
   {
    
      if(m_cftype)
      {
       
         CFRelease(m_cftype);
         
      }
      
   }
   
   
   operator CORE_FOUNDATION_TYPE()
   {
    
      return m_cftype;
      
   }
      
   
};

template < typename CORE_FOUNDATION_TYPE >
::core_foundation_reference < CORE_FOUNDATION_TYPE > as_CFRef(CORE_FOUNDATION_TYPE cftype)
{
 
   return ::core_foundation_reference < CORE_FOUNDATION_TYPE >(cftype);
   
}

//
//class keep_cgcontext
//{
//public:
//   
//   CGContextRef m_cgcontext;
//   
//   keep_cgcontext(CGContextRef cgcontext):
//      m_cgcontext(cgcontext)
//   {
//      
//      CGContextSaveGState(m_cgcontext);
//
//   }
//   
//   ~keep_cgcontext()
//   {
//      // Restore the CGContext state
//      CGContextRestoreGState(m_cgcontext);
//      
//   }
//
//   
//};


namespace quartz2d
{

   namespace nano
   {

  
      namespace graphics
      {


   class CLASS_DECL_NANO_GRAPHICS_QUARTZ2D context :
      virtual public ::nano::graphics::context
   {
   public:


      /////CGContextRef                  m_cgcontext;
      ::pointer < ::core_graphics::cg_context > m_pcgcontext;
      bool                          m_bOwn;
      
      ::pointer < pen > m_ppen;
      ::pointer < brush > m_pbrush;
      ::pointer < font > m_pfont;

      
      context();
      //context(CGContextRef pdc);
      ~context() override;

      
      ::pointer < ::nano::graphics::image > create_bitmap_context(void * pdata,
                                                                 const ::i32_size & size, int iBytesPerRow) override;
      
      void update_bitmap_context_image(::pointer < ::nano::graphics::image > & pimage) override;
      
      
      void set_blend_mode(::nano::graphics::enum_blend_mode eblendmode) override;
      void set_smoothing_mode(::nano::graphics::enum_smoothing_mode esmoothingmode) override;

      void set_pen(::nano::graphics::pen * ppen) override;
      void set_brush(::nano::graphics::brush * pbrush) override;
      void set_font(::nano::graphics::font * pfont) override;

      
      void line(const ::f64_point& point1, const ::f64_point& point2) override;
      
      void attach(void * posdata, const ::i32_size & size, ::i32 iType) override;
      void _draw_text(const ::scoped_string & scopedstr, const ::f64_rectangle & rectangleText,
                      const ::e_draw_text & edrawtext, const ::e_align & ealign) override;
      
      ::f64_size get_text_extents(const ::scoped_string & scopedstr) override;

      void rectangle(const ::f64_rectangle & rectangle) override;
      
      void ellipse(const ::f64_rectangle & rectangle) override;

      
      void draw_icon(int x, int y, int cx, int cy, ::nano::graphics::icon * picon) override;
      void draw_image(const ::f64_rectangle & rectangle, ::nano::graphics::image * pimage) override;
      void draw_image(const ::f64_point & point, const ::f64_rectangle & rectangle, ::nano::graphics::image * pimage) override;

      
      void _set_source(const ::color::color & color);


      void _set_brush(brush * pbrush);
      
      void _set_pen(pen * ppen);
      
      
      //void _select_font(::nano::graphics::font * pnanofont);
      
      void translate(::f64 x, ::f64 y) override;
      
      void do_path(::nano::graphics::path *ppath) override;
      
   };



      } //namespace user


   } //namespace nano


} // namespace quartz2d





