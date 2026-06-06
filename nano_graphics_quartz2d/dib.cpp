//
//  dib.cpp
//  nano_graphics_quartz2d
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 06/06/26.
//  Copyright © 2026 ca2 Software Development. All rights reserved.
//  Created by camilo on 2026-06-06 00:52 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
//
#include "framework.h"
#include "context.h"
#include "dib.h"
#include "image.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/filesystem/file/memory_file.h"


namespace quartz2d
{


   namespace nano
   {


      namespace graphics
      {


         dib::dib()
         {
            
         }


         dib::~dib()
         {
            
            
         }

         ::i32_size dib::size() const
         {
            
            return m_size;
            
         }


         void dib::create_image(const ::i32_size & size)
         {
            
            m_iBytesPerRow = size.cx * 4;
            
            m_size = size;
            
            construct_newø(m_pcontext);
            
            m_memory.set_size(m_iBytesPerRow* size.cy);
            
            construct_newø(m_pimage);
            
            auto pimage = m_pcontext->create_bitmap_context(m_memory.data(), size, m_iBytesPerRow);
            
            m_pimage = pimage;
            
         }

      
      ::nano::graphics::image * dib::get_image2()
         {
            
         return m_pimage;
            
         }

      ::nano::graphics::image * dib::fetch_image()
         {
         
         ::pointer < ::nano::graphics::image > pimage;
         
         pimage = m_pimage;
            
         m_pcontext->update_bitmap_context_image(pimage);
         
         m_pimage = pimage;
         
         return m_pimage;
            
         }


      ::nano::graphics::context * dib::get_context()
         {
            
         return m_pcontext;
            
         }


         void * dib::get_buffer()
         {
            
            return m_memory.data();
            
         }


         void dib::load_image_from_file(::file::file * pfile)
         {
            
            auto memory = pfile->as_memory();
            
            load_image_file(memory.data(), memory.size());
            
         }


         void dib::load_image_file(const void *p, memsize size)
         {
            
            auto pfile = create_memory_file({p, size});
            
            load_image_from_file(pfile);
            
         }


      } // namespace graphics


   } // namespace nano


} // namespace quartz2d

