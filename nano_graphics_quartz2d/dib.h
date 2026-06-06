//
//  dib.h
//  nano_graphics_quartz2d
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 06/06/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  Created by camilo on 2026-06-06 02:51 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#pragma once


#include "acme/nano/graphics/dib.h"
#include "acme/prototype/geometry2d/size.h"


namespace quartz2d
{



   namespace nano
   {


      namespace graphics
      {


         class CLASS_DECL_NANO_GRAPHICS_QUARTZ2D dib :
         virtual public ::nano::graphics::dib
         {
         public:
            
            ::memory m_memory;
            ::i32_size m_size;
            int m_iBytesPerRow;
            ::pointer < class context > m_pcontext;
            ::pointer < class image > m_pimage;

            dib();
            ~dib();
            
            ::i32_size size() const override;
            
            
            void create_image(const ::i32_size & size) override;
            
            ::nano::graphics::image * get_image2() override;
            ::nano::graphics::image * fetch_image() override;
            ::nano::graphics::context * get_context() override;
            void * get_buffer() override;
            
            void load_image_from_file(::file::file * pfile) override;
            void load_image_file(const void *p, memsize size) override;
            
         };


      } // namespace graphics


   } // namespace nano


} // namespace quartz2d

