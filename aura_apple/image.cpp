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

   ::acme::malloc < image32_t * > pdst;

   pdst.alloc(pimage->scan_size() * pimage->height());

   if(pdst == nullptr)
   {

      return 0;

   }
   
   pimage->map();

   pdst->_001ProperCopyColorref(pimage->width(), pimage->height(), pimage->scan_size(), pimage->get_data(), pimage->scan_size());

   CGColorSpaceRef colorspace = CGColorSpaceCreateDeviceRGB();

   CGContextRef context = CGBitmapContextCreate(
                          pdst,
                          pimage->width(),
                          pimage->height(), 8,
                          pimage->scan_size(), colorspace, kCGImageAlphaPremultipliedLast);

   CGColorSpaceRelease(colorspace);

   if(context == nullptr)
   {

      return nullptr;


   }

   CGImageRef cgimage = CGBitmapContextCreateImage(context);

   CGContextRelease(context);

   return cgimage;

}



