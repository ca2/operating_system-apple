//
//  ns_image.mm
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/05/26.
//
#include <AppKit/AppKit.h>
#include "_mm.h"

CGImageRef CreateRGBAImage(int width, int height)
{
    size_t bitsPerComponent = 8;
    size_t bytesPerPixel = 4;
    size_t bytesPerRow = width * bytesPerPixel;

    CGColorSpaceRef colorSpace =
        CGColorSpaceCreateDeviceRGB();

    // Allocate pixel buffer
    void * pixelData =
        calloc(height, bytesPerRow);

    // RGBA 8-bit per component
    CGBitmapInfo bitmapInfo =
        kCGImageAlphaPremultipliedLast
        | kCGBitmapByteOrder32Big;

    CGContextRef context =
        CGBitmapContextCreate(
            pixelData,
            width,
            height,
            bitsPerComponent,
            bytesPerRow,
            colorSpace,
            bitmapInfo);

    CGColorSpaceRelease(colorSpace);

    if(context == NULL)
    {
        free(pixelData);
        return NULL;
    }

    // Optional: clear to transparent black
    CGContextClearRect(
        context,
        CGRectMake(0, 0, width, height));

    CGImageRef image =
        CGBitmapContextCreateImage(context);

    CGContextRelease(context);

    // IMPORTANT:
    // image now owns/copies the bitmap internally,
    // so pixelData can usually be freed here.
    free(pixelData);

    return image;
}

cg_image_t cg_image_create(cg_size size)
{
   auto cgimage = CreateRGBAImage(size.w, size.h);
   
   return {(::uptr) cgimage};
   
}


void cg_image_from_cg_bitmap_context(cg_image_t & cgimage, cg_context_t cgcontext)
{

   cg_image_release(cgimage);
   
   auto cgcontextref = (CGContextRef)cgcontext.m_u;
   
   auto cgimageref = CGBitmapContextCreateImage(cgcontextref);
   
   cgimage.m_u = (::uptr)cgimageref;
   
}


void cg_image_release(cg_image_t & cgimage)
{
 
   if(cgimage.is_set())
   {
      
      CGImageRelease(CGIMAGE(cgimage));
      
      cgimage.clear();
      
   }
}


cg_size cg_image_get_size(cg_image_t cgimage)
{
   
   cg_size size;
   
   size.w  = (::i32) CGImageGetWidth(CGIMAGE(cgimage));
   size.h = (::i32) CGImageGetHeight(CGIMAGE(cgimage));
   
   return size;
   
}
