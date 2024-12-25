//
// Created by camilo on 31/01/2022 20:15 <3ThomasBorregaardSorensen!! Thomas Likes number 5!!
//
#pragma once


#include "acme/nano/graphics/device.h"


#include <CoreGraphics/CoreGraphics.h>

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


class keep_cgcontext
{
public:
   
   CGContextRef m_cgcontext;
   
   keep_cgcontext(CGContextRef cgcontext):
      m_cgcontext(cgcontext)
   {
      
      CGContextSaveGState(m_cgcontext);

   }
   
   ~keep_cgcontext()
   {
      // Restore the CGContext state
      CGContextRestoreGState(m_cgcontext);
      
   }

   
};


namespace quartz2d
{

   namespace nano
   {

  
      namespace graphics
      {


   class CLASS_DECL_NANO_GRAPHICS_QUARTZ2D device :
      virtual public ::nano::graphics::device
   {
   public:


      CGContextRef                  m_cgcontext;
      bool                          m_bOwn;

      
      device();
      device(CGContextRef pdc);
      ~device() override;

      void attach(void * posdata, const ::int_size & size) override;
      void _draw_text(const ::string & str, const ::int_rectangle & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano::graphics::brush * pnanobrushBack, ::nano::graphics::brush * pnanobrushText, ::nano::graphics::font * pnanofont) override;
      
      ::int_size get_text_extents(const ::string & str, ::nano::graphics::font * pnanofont) override;

      void rectangle(const ::int_rectangle & rectangle, ::nano::graphics::brush * pnanobrush, ::nano::graphics::pen * pnanopen) override;

      
      void draw(::nano::graphics::icon * picon, int x, int y, int cx, int cy) override;
      
      
      void _set_source(const ::color::color & color);


      void _set_fill_color(const ::color::color & color);
      
      
      //void _select_font(::nano::graphics::font * pnanofont);
      
      void translate(int x, int y) override;
      
   };



      } //namespace user


   } //namespace nano


} // namespace quartz2d





