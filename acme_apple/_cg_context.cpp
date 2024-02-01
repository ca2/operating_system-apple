//
//  _cg_context.cpp
//  acme_apple
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 11/04/23.
//  from acme_apple/node.dpp
//  <3ThomasBorregaardSorensen!!
//
#include "framework.h"


//#include <CoreGraphics/CoreGraphics.h>
//#include <CoreImage/CoreImage.h>

//
//CGContextRef CreateARGBBitmapContext (CGImageRef inImage, int cx, int cy)
//{
//
//   CGContextRef    context = nullptr;
//
//   CGColorSpaceRef colorSpace;
//
//   //void *          bitmapData;
//
//   int             bitmapByteCount;
//
//   int             bitmapBytesPerRow;
//
//   bitmapBytesPerRow   = (cx * 4);
//
//   bitmapByteCount     = (bitmapBytesPerRow * cy);
//
//   colorSpace = CGColorSpaceCreateDeviceRGB();
//
//   if (colorSpace == nullptr)
//   {
//
//      output_debug_string("CreateARGBBitmapContext: Error allocating color space\n");
//
//      return nullptr;
//
//   }
//
//   //   bitmapData = malloc( bitmapByteCount );
//   //
//   //   if (bitmapData == nullptr)
//   //   {
//   //
//   //      output_debug_string("CreateARGBBitmapContext: Memory not allocated!");
//   //
//   //      CGColorSpaceRelease( colorSpace );
//   //
//   //      return nullptr;
//   //
//   //   }
//   //
//   //   __memset(bitmapData, 0, bitmapByteCount);
//
//   // Create the bitmap context. We want pre-multiplied argb, 8-bits
//   // per component. Regardless of what the source image format is
//   // (CMYK, Grayscale, and so on) it will be converted over to the format
//   // specified here by CGBitmapContextCreate.
//   context =
//   CGBitmapContextCreate (
//   nullptr,
//   cx,
//   cy,
//   8,
//   bitmapBytesPerRow,
//   colorSpace,
//   kCGImageAlphaPremultipliedLast);
//
//   //   if (context == nullptr)
//   //   {
//   //
//   //      free (bitmapData);
//   //
//   //      output_debug_string("CreateARGBBitmapContext: Context not created!");
//   //
//   //   }
//
//   CGColorSpaceRelease( colorSpace );
//
//   return context;
//}
//
//
//
//
