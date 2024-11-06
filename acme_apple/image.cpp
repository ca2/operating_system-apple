//
//  image.cpp
//  acme_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 01/06/22. 01:08AM
//
//
//  image.cpp
//  acme_macos(acme_ios)
//
//  Created by Camilo Sasuke on 2021-06-01 19:57 BRT <3ThomasBS_!!
//
//
//  image.cpp
//  acme_macos
//
//  Created by Camilo Sasuke on 2021-06-01 19:57 BRT <3ThomasBS_!!
//
#include "framework.h"
#include "image.h"


void * cg_image_get_image_data(int & width, int & height, int & iScan, CGImageRef image)
{

   if(image == nullptr)
   {

      return nullptr;

   }

   //https://www.raywenderlich.com/69855/image-processing-in-ios-part-1-raw-bitmap-modification
   // 1.
   width = (int) CGImageGetWidth(image);
   height = (int) CGImageGetHeight(image);

   // 2.
   long bytesPerPixel = 4;
   long bytesPerRow = bytesPerPixel * width;
   long bitsPerComponent = 8;

   unsigned int * pixels;
   pixels = (unsigned int *) calloc(height * width, sizeof(unsigned int));
   
   iScan = width * sizeof(unsigned int);

   // 3.
   CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
   CGContextRef context = CGBitmapContextCreate(pixels, width, height, bitsPerComponent, bytesPerRow, colorSpace, kCGImageAlphaPremultipliedLast
// kCGBitmapByteOrder32Big
                                                );

   // 4.
   CGContextDrawImage(context, CGRectMake(0, 0, width, height), image);

   // 5. Cleanup
   CGColorSpaceRelease(colorSpace);

   CGContextRelease(context);

   return pixels;

}

