//
//  imsage.h
//  nano_graphics_quartz2d
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 06/06/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  Created by camilo on 2026-06-06 00:14 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#pragma once


#include "acme/nano/graphics/image.h"


namespace quartz2d
{


   namespace nano
   {


      namespace graphics
      {
         

         class CLASS_DECL_NANO_GRAPHICS_QUARTZ2D image :
            virtual public ::nano::graphics::image
         {
         public:
            
            
            ::pointer < ::core_graphics::cg_image > m_pcgimage;
            
            
            image();
            ~image() override;
            
            void load_image_file(const void *p, memsize size) override;
            
            void _draw_in_context(::quartz2d::nano::graphics::context * pcontext,  const ::f64_rectangle & rectangle);
            void _draw_in_context(::quartz2d::nano::graphics::context * pcontext, const ::f64_point & point, const ::f64_rectangle & rectangle);

         };


      } // namespace graphics


   } // namespace nano


} // namespace quartz2d



