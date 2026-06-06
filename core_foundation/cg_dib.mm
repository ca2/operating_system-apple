//
//  cg_dib.mm
//  core_graphics
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2026 May
//
#include <CoreGraphics/CoreGraphics.h>
#include "_mm.h"
#include "cg_context.h"
#include "cg_image.h"


void cg_dib_release(cg_dib_t & cgdib)
{

   cgdib.m_pcgimage.release();
   //cg_image_release(cgdib.m_cgimage);

   //cg_context_release(cgdib.m_cgcontext);
   cgdib.m_pcgcontext.release();

   if(cgdib.m_p)
   {
      free(cgdib.m_p);
      cgdib.m_p = nullptr;
   }
   
}

bool cg_dib_create_from_cg_image(cg_dib_t & cgdib, cg_image_t sourceImage)
{
   
   cg_dib_release(cgdib);
   //cg_dib_t cgdib{};
  

    if(sourceImage.m_u == 0)
    {
        return false;
    }

    size_t width  = CGImageGetWidth((CGImageRef)sourceImage.m_u);
    size_t height = CGImageGetHeight((CGImageRef)sourceImage.m_u);

    size_t bytesPerPixel = 4;
    size_t bytesPerRow = width * bytesPerPixel;

    void * data = calloc(height, bytesPerRow);

    if(data == NULL)
    {
        return false;
    }

    CGColorSpaceRef colorSpace =
        CGColorSpaceCreateDeviceRGB();

    CGContextRef context =
        CGBitmapContextCreate(
            data,
            width,
            height,
            8,
            bytesPerRow,
            colorSpace,
            kCGImageAlphaPremultipliedLast
            | kCGBitmapByteOrder32Big);

    CGColorSpaceRelease(colorSpace);

    if(context == NULL)
    {
        free(data);
        return false;
    }

    CGContextDrawImage(
        context,
        CGRectMake(0, 0, width, height),
        (CGImageRef)sourceImage.m_u);

    CGImageRef image =
        CGBitmapContextCreateImage(context);

    cgdib.m_p = data;
    cgdib.m_cgsize.w = width;
    cgdib.m_cgsize.h = height;
    cgdib.m_iBytesPerRow = bytesPerRow;
   //::system()->construct_newø(cgdib.m_pcgcontext);
     // cgdib.m_pcgcontext->m_cgcontext.m_u = (::uptr) context;
   //::system()->construct_newø(cgdib.m_pcgimage);
   //cgdib.m_pcgimage->m_cgimage.m_u = (::uptr) image;
   cgdib.m_pcgcontext = cg_context_from_cg_context_uptr((::uptr) context);
   cgdib.m_pcgimage = cg_image_from_cg_image_uptr((::uptr) image);
   
   
    return true;
}



bool cg_dib_create(cg_dib_t &cgdib, cg_size size)
{
   
   cg_dib_release(cgdib);
   
   size_t width  = (int) size.w;
   size_t height = (int) size.h;

   size_t bytesPerPixel = 4;
   size_t bytesPerRow = width * bytesPerPixel;

   void * data = calloc(height, bytesPerRow);

   if(data == NULL)
   {
      return false;
   }

   CGColorSpaceRef colorSpace =
        CGColorSpaceCreateDeviceRGB();
   
   
   //bOpaque = false;

   CGContextRef context =
        CGBitmapContextCreate(
            data,
            width,
            height,
            8,
            bytesPerRow,
            colorSpace,
            //(bOpaque ?
             //kCGImageAlphaNoneSkipFirst :
             kCGImageAlphaPremultipliedFirst
            | kCGBitmapByteOrder32Little);

    CGColorSpaceRelease(colorSpace);

    if(context == NULL)
    {
        free(data);
        return false;
    }

    //CGContextDrawImage(
      //  context,
       // CGRectMake(0, 0, width, height),
        //(CGImageRef)sourceImage.m_u);

   CGImageRef cgimageref = CGBitmapContextCreateImage(context);

   cgdib.m_p = data;
   cgdib.m_cgsize.w = width;
   cgdib.m_cgsize.h = height;
   cgdib.m_iBytesPerRow = bytesPerRow;
//   ::system()->construct_newø(cgdib.m_pcgcontext);
//      cgdib.m_pcgcontext->m_cgcontext.m_u = (::uptr) context;
//   ::system()->construct_newø(cgdib.m_pcgimage);
//   cgdib.m_pcgimage->m_cgimage.m_u = (::uptr) image;
   cgdib.m_pcgcontext = cg_context_from_cg_context_uptr((::uptr) context);
   cgdib.m_pcgimage = cg_image_from_cg_image_uptr((::uptr) cgimageref);

   return true;
   
}

