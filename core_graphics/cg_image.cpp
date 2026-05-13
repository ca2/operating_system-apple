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
#include "_mm.h"


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


} //  namespace core_graphics



