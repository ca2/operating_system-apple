//
//  image.cpp
//  aura_macos
//
//  Created by Camilo Sasuke on 29/05/21 14:30 BRT <3ThomasBS_!!
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"
#include "aura/graphics/draw2d/_draw2d.h"


CGImageRef cgimageref_from_image(const ::image * pimage)
{

   ::acme::malloc < color32_t * > pdst;

   pdst.alloc(pimage->scan_size() * pimage->height());

   if(pdst == nullptr)
   {

      return nullptr;

   }
   
   pimage->map();

   _001ProperCopyColorref(pdst, pimage->width(), pimage->height(), pimage->scan_size(), pimage->get_data(), pimage->scan_size());

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



