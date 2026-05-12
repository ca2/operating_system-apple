//
//  ns_image.cpp
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 04:23
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "ns_image.h"
#include "acme/prototype/geometry2d/size.h"


namespace core_graphics
{

   ns_image::ns_image()
   {
   
      m_pNS = nullptr;
      
   }


   ns_image::~ns_image()
   {
   
      ns_image_release(m_pNS);
   
   }


   ::i32_size ns_image::get_size()
   {
   
      ::i32 w = 0;
      ::i32 h = 0;
      
      ns_image_get_size(m_pNS, w, h);
      
      return {w, h};
      
   }


} //  namespace core_graphics



