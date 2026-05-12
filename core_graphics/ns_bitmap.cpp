//
//  ns_bitmap.cpp
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 04:23
//  <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "ns_bitmap.h"

void ns_bitmap_release(void * & pNSBitmap);

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


} //  namespace core_graphics



