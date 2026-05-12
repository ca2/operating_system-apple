//
//  ns_bitmap.cpp
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 04:23
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "ns_bitmap.h"

void ns_bitmap_release(void * & pNS);
void ns_bitmap_get_size(void * pNS, ::i32 & w,::i32 & h);

namespace core_graphics
{

   ns_bitmap::ns_bitmap()
   {
   
      m_pNSBitmap = nullptr;
      
   }


   ns_bitmap::~ns_bitmap()
   {
   
      ns_bitmap_release(m_pNSBitmap);
   
   }


   ::i32_size ns_bitmap::get_size()
   {
   
      ::i32 w = 0;
      ::i32 h = 0;
      
      ns_bitmap_get_size(m_pNSBitmap, w, h);
      
      return {w, h};
      
   }


} //  namespace core_graphics



