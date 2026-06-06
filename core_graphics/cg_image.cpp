//
//  cg_image.cpp
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 04:23
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "cg_image.h"
#include "acme/prototype/geometry2d/size.h"


namespace core_graphics
{

   cg_image::cg_image()
   {
   
//      m_pNS = nullptr;
      
   }


   cg_image::~cg_image()
   {
   
      cg_image_release(m_cgimage);
   
   }


   ::i32_size cg_image::get_size()
   {
   
      auto s = cg_image_get_size(m_cgimage);
      
      return {(::i32) s.w,(::i32)s.h};
      
   }


   void cg_image::initialize_dib(const ::i32_size & size)
   {
      
      cg_size cgsize;
      
      cgsize.w = size.cx;
      
      cgsize.h = size.cy;
      
      m_cgimage = cg_image_create(cgsize);
      
   }
::pointer < cg_image > cg_image_from_cg_image_uptr(::uptr u)
{
   auto pcgimage = ::system()->create_newø<cg_image>();
   pcgimage->m_cgimage.m_u = u;
   return pcgimage;
}

} //  namespace core_graphics



