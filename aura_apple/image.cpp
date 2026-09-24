//
//  image.cpp
//  aura_macos
//
//  Created by Camilo Sasuke on 29/05/21 14:30 BRT <3ThomasBS_!!
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"
#include "aura/graphics/image/image.h"
#include <CoreGraphics/CoreGraphics.h>


CGImageRef cgimageref_from_image(const ::image::image * pimage)
{
   
   auto ppixmapImage = ((::image::image *) pimage)->map();

   ::acme::malloc < image32_t * > pdst;

   pdst.alloc(ppixmapImage->m_iScan * pimage->height());

   if(pdst == nullptr)
   {

      return 0;

   }
   
   pdst->_001ProperCopyColorref(ppixmapImage->width(), ppixmapImage->height(), ppixmapImage->scan_size(), ppixmapImage->data(), ppixmapImage->scan_size());

   CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();

   CGContextRef context = CGBitmapContextCreate(
                          pdst,
                                                ppixmapImage->width(),
                                                ppixmapImage->height(), 8,
                                                ppixmapImage->scan_size(), colorspace, kCGImageAlphaPremultipliedLast);

   CGColorSpaceRelease(colorspace);

   if(context == nullptr)
   {

      return nullptr;


   }

   CGImageRef cgimage = CGBitmapContextCreateImage(context);

   CGContextRelease(context);

   return cgimage;

}



