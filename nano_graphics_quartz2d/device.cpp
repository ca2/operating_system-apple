//
// Created by camilo on 31/01/2022 20:15 <3ThomasBorregaardSorensen!! Thomas Likes number 5!!
//
#include "framework.h"
#include "device.h"
#include "icon.h"
#include "acme/nano/graphics/font.h"
#include "acme/nano/graphics/brush.h"
#include "acme/nano/graphics/pen.h"
#include "acme/prototype/geometry2d/rectangle.h"


//void ns_draw_image(CGContextRef cgcontextref, void * pNSImage, int x, int y, int cx);


namespace quartz2d
{

   namespace nano
   {

  
      namespace graphics
      {



   device::device()
   {
      
      m_bOwn = true;
      
      auto colorspace = CGColorSpaceCreateDeviceRGB();
      
      int width = 256;
      
      int height = 256;
      
      int bitsPerComponent = 8;
      
      int bytesPerRow = width * 4;

      m_pdc = CGBitmapContextCreate(
         nullptr,
         width, height,
         bitsPerComponent, bytesPerRow,
         colorspace, kCGImageAlphaPremultipliedLast);
      
      CGColorSpaceRelease(colorspace);

   }


   device::device(CGContextRef pdc)
   {
      
      m_bOwn = false;

      m_pdc = pdc;

   }


   device::~device()
   {
      
      if(m_bOwn)
      {

         if(m_pdc)
         {
          
            CGContextRelease(m_pdc);
            
         }
         
      }

   }


   void device::_draw_text(const ::string & str, const ::int_rectangle & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano::graphics::brush * pnanobrushBack, ::nano::graphics::brush * pnanobrushText, ::nano::graphics::font * pnanofont)
   {
      
      _select_font(pnanofont);
      
      float w, h;

      w = rectangleText.width();

      h = rectangleText.height();
      
      _select_font(pnanofont);

      CGContextSetTextPosition(m_pdc, 0, 0);
      CGContextSetTextDrawingMode (m_pdc, kCGTextInvisible);
      CGContextShowText (m_pdc, str, str.length());
      CGPoint pointSize = CGContextGetTextPosition(m_pdc);
      pointSize.y = pnanofont->m_iFontSize;

      CGContextSetTextDrawingMode (m_pdc, kCGTextFill);
      CGAffineTransform trans = CGAffineTransformMakeScale(1, -1);
      CGContextSetTextMatrix(m_pdc, trans);
      CGContextSetRGBFillColor (m_pdc, __expand_float_rgba(pnanobrushText->m_color));

      double x = rectangleText.left();
      
      double y = rectangleText.top();

      if(ealign & e_align_horizontal_center)
      {

         x += ((double) rectangleText.width() - pointSize.x) / 2.0;

      }
      else if(ealign & e_align_right)
      {

         x += (double) rectangleText.width() - pointSize.x;

      }

      if(ealign & e_align_vertical_center)
      {

         y += ((double) rectangleText.height() - pointSize.y) / 2.0;

      }
      else if(ealign & e_align_bottom)
      {

         y += (double) rectangleText.height() - pointSize.y;

      }
      
      y += pointSize.y;

      CGContextShowTextAtPoint (m_pdc, x, y, str, str.length());

   }


   ::int_size device::get_text_extents(const ::string & str, ::nano::graphics::font * pnanofont)
   {
      
      _select_font(pnanofont);

      CGContextSetTextPosition(m_pdc, 0, 0);
      CGContextSetTextDrawingMode (m_pdc, kCGTextInvisible);//5
      CGContextShowText (m_pdc, str, str.length());//10
      CGPoint pointSize = CGContextGetTextPosition(m_pdc);

      ::int_size size;
      
      size.cx() = pointSize.x;
      size.cy() = pnanofont->m_iFontSize;
      
      return size;

   }


   void device::rectangle(const ::int_rectangle & rectangle, ::nano::graphics::brush * pnanobrush, ::nano::graphics::pen * pnanopen)
   {

      int iWidth = pnanopen ? pnanopen->m_iWidth : 0;

      CGRect rect;
      
      rect.origin.x = rectangle.left();
      rect.origin.y = rectangle.top();
      rect.size.width = rectangle.width();
      rect.size.height = rectangle.height();

      if (pnanobrush && pnanobrush->m_color.has_opacity())
      {
   
         _set_fill_color(pnanobrush->m_color);

         CGContextFillRect(m_pdc, rect);

      }

      if(iWidth > 0)
      {
         
         CGContextBeginPath(m_pdc);
         
         CGContextAddRect(m_pdc, rect);
         
         CGContextSetRGBStrokeColor(m_pdc, __expand_float_rgba(pnanopen->m_color));
         
         CGContextSetLineWidth(m_pdc, pnanopen->m_iWidth);
         
         CGContextStrokePath(m_pdc);

      }

   }

      
      void device::attach(void * posdata)
      {
         
         m_bOwn = false;

         m_pdc=(CGContextRef)posdata;
         
      }
      
      
      void device::draw(::nano::graphics::icon * picon, int x, int y, int cx, int cy)
      {
         
         ::cast < ::quartz2d::nano::graphics::icon > pquartz2dicon = picon;
         
         pquartz2dicon->_draw_in_context(this, x, y, cx, cy);
         
      }


   void device::_set_source(const ::color::color & color)
   {


   }


   void device::_set_fill_color(const ::color::color & color)
   {

      CGContextSetRGBFillColor(m_pdc, __expand_float_rgba(color));

   }

   
   void device::_select_font(::nano::graphics::font * pnanofont)
   {
      
      CGContextSelectFont (m_pdc,
                   pnanofont->m_strFontName.c_str(),
                   pnanofont->m_iFontSize,
                   kCGEncodingMacRoman);

   }

      
      void device::translate(int x, int y)
      {
        
         CGContextTranslateCTM(m_pdc, x, y);
         
      }
      

      } //namespace user


   } //namespace nano


} // namespace quartz2d



