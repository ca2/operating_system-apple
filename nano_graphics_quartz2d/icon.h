// Created by camilo on 2024-09-13 07:18 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/nano/graphics/icon.h"
//#include <gtk/gtk.h>
//#include <QPixmap>



namespace quartz2d
{

   namespace nano
   {

  
      namespace graphics
   {
      
      class CLASS_DECL_NANO_GRAPHICS_QUARTZ2D icon :
      virtual public ::nano::graphics::icon
      {
         public:
         
         
         //GdkPaintable *  m_pgdkpaintable;
         //QPixmap *m_pqpixmap;
#ifdef __OBJC__
         NSImage * m_pnsimage;
#else
         void * m_pNSImage;
#endif
         icon();
         ~icon() override;
         
         void load_image_file(const void *p, memsize size) override;

         
         ///void _create() override;
         //virtual void __create();
         
         //void __icon_release();
         
         void _draw_in_context(::quartz2d::nano::graphics::device * pdevice, int x, int y, int cx, int cy);
         
      };
      } // namespace graphics
      } // namespace nano
      } // namespace quartz2d



