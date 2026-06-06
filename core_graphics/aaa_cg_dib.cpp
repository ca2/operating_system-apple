//
//  cg_dib.cpp
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026 May
//
#include "framework.h"
#include "cg_context.h"
#include "cg_dib.h"
#include "cg_image.h"
#include "acme/prototype/geometry2d/size.h"


namespace core_graphics
{

   cg_dib::cg_dib()
   {
   
//      m_pNS = nullptr;
      
   }


   cg_dib::~cg_dib()
   {
   
      
      cg_dib_release(m_cgdib);
   
   }


   ::i32_size cg_dib::get_size()
   {
   
      //auto s = cg_image_get_size(m_cgimage);
      
      return {(::i32) m_cgdib.m_cgsize.w,(::i32)m_cgdib.m_cgsize.h};
      
   }


   void * cg_dib::get_buffer()
   {
   
      return m_cgdib.m_p;
      
   }


   void cg_dib::initialize_dib(const ::i32_size & size)
   {
      
      cg_dib_release(m_cgdib);
      
      cg_size cgsize;
      
      cgsize.w = size.cx;
      cgsize.h = size.cy;

      cg_dib_create(m_cgdib, cgsize);

   }

   void cg_dib::initialize_from_cg_image(cg_image * pcgimage)
   {
      
      cg_dib_release(m_cgdib);

      cg_dib_create_from_cg_image(m_cgdib, pcgimage->m_cgimage);
      
   }

   void cg_dib::update_image()
{
      
      defer_construct_newø(m_cgdib.m_pcgimage);
      if(m_cgdib.m_pcgimage->m_cgimage.m_u)
      {
         cg_image_release(m_cgdib.m_pcgimage->m_cgimage);
      }
      cg_image_from_cg_bitmap_context(m_cgdib.m_pcgimage->m_cgimage, m_cgdib.m_pcgcontext->m_cgcontext);
//      CGColorSpaceRef cs = CGColorSpaceCreateDeviceRGB();
//
//      CGDataProviderRef provider =
//          CGDataProviderCreateWithData(
//              NULL,
//              pixels,
//              stride * height,
//              NULL);
//
//      CGImageRef image =
//          CGImageCreate(
//              width,
//              height,
//              8,                  // bits/component
//              32,                 // bits/pixel
//              stride,
//              cs,
//              kCGImageAlphaFirst | kCGBitmapByteOrder32Little,
//              provider,
//              NULL,
//              false,
//              kCGRenderingIntentDefault);
      //return {};
      
   }

} //  namespace core_graphics



