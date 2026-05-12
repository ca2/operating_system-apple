//
//  ns_bitmap.h
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026-05-12 04:21
//  <3ThomasBorregaardSørensen!!
//
#pragma once


namespace core_graphics
{


   class CLASS_CORE_GRAPHICS ns_bitmap :
      virtual public ::particle
   {
   public:
      
      void * m_pNSBitmap;
      
      
      ns_bitmap();
      ~ns_bitmap();
      
      
      virtual ::i32 get_size();
      
      
      
   };

} // namespace core_graphics




