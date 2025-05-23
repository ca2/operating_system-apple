//
//  visual_apple_image.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 21/10/17. Thomas Boregaard Soerensen <3
//
#include "framework.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/graphics/image/encoding_options.h"
#include "aura/platform/context.h"
#include <CoreGraphics/CoreGraphics.h>


CFDataRef CopyImagePixels(CGImageRef inImage);

void * file_memory_to_image_data(int & width, int & height, int & iScan, const void * pdata, unsigned long int_size);

void * cg_image_get_image_data(int & width, int & height, int & iScan, CGImageRef image);

void * nscursor_system(enum_cursor ecursor);

CGImageRef cgimageref_from_image(const ::image::image * pimage);

//void ns_set_cursor_cgimageref(CGImageRef image, int cx, int cy, int xHotSpot, int yHotSpot);

//void * nscursor_from_cgimageref(CGImageRef image, int cx, int cy, int xHotSpot, int yHotSpot);

void * get_png_image_data(unsigned long & size, CGImageRef image);
void * get_jpeg_image_data(unsigned long & size, CGImageRef image);


namespace coreimage_imaging
{


   void image_context::save_image(memory & memory, ::image::image * pimage, const ::image::encoding_options & encodingoptions)
   {

      if(pimage->is_empty())
      {

         throw exception(error_invalid_parameter);

      }

      switch (encodingoptions.m_eformat)
      {
      case ::image::e_format_jpeg:
      {

         unsigned long size;

         ::acme::malloc < color32_t * > p;

         CGImageRef cgimage = cgimageref_from_image(pimage);

         p = get_jpeg_image_data(size, cgimage);
         
         CGImageRelease(cgimage);

         memory.assign(p, size);


      }
      break;
         case ::image::e_format_none:
         case ::image::e_format_png:
            
         {

            unsigned long size;

            ::acme::malloc < color32_t * > p;

            CGImageRef cgimage = cgimageref_from_image(pimage);

            p = get_png_image_data(size, cgimage);
            
            CGImageRelease(cgimage);

            memory.assign(p, size);


         }
         break;
      default:
      {

         ::image::image_context::save_image(memory, pimage, encodingoptions);

      }
            break;

      }


      //return true;

   }


   void image_context::_load_image(::image::image * pimage, const ::payload & varFile, const ::image::load_options & options)
   {
      
      if(::is_null(pimage))
      {
         
         throw exception(error_invalid_parameter);
         
      }
      
      memory memory;
      
      auto papplication = application();
      
      if(options.toy)
      {
         
         papplication->file()->safe_get_memory(varFile, memory);
         
      }
      else
      {
         
         papplication->file()->as_memory(varFile, memory);

   
      }
      
//      if(!bOk)
//      {
//
//         pimage->m_estatus = error_not_found;
//
//         pimage->set_nok();
//
//         return;
//
//      }

      if(memory.is_empty())
      {
         
         pimage->m_estatus = error_invalid_empty_argument;
         
         pimage->set_nok();
         
         return;
         
      }

      auto pszData = memory.data();

      auto size = memory.size();

      char pszPngSignature []= {(char)137, 80, 78 ,71, 13 ,10, 26 ,10};

      bool bPng = size > sizeof(pszPngSignature)
      && strncmp((const char *) pszData, pszPngSignature, sizeof(pszPngSignature)) == 0;

      bool bJpegBegins = memory.begins("\x0FF\x0D8");

      bool bJpegEnds = memory.ends("\x0FF\x0D9");

      bool bGif87a = memory.begins("GIF87a");

      bool bGif89a = memory.begins("GIF89a");

      bool bJpeg =  bJpegBegins && bJpegEnds;

      bool bJfif = memory.begins("JFIF");

      bool bExif = memory.begins("Exif");

      bool bGif = bGif87a || bGif89a;

      bool bBinary = pszData && *pszData == '\0';

      if(!bPng
      && !bBinary
      && !bJpeg
      && !bJfif
      && !bExif
      && !bGif
      )
      {

         //estatus =
         
         this->load_svg(pimage, memory);

         if (::is_set(pimage) && pimage->is_ok())
         {

            return;

         }

      }
      else if (bGif)
      {

      //m_psystem->file_system()->put_contents("/home/camilo/a.gif", memory);

         _load_multi_frame_image(pimage, memory);

         //if (!)
 /*        {
            pimage->set_nok();
            return pimage->m_estatus;
         }*/

         pimage->on_load_image();

         pimage->set_ok_flag();

         pimage->m_estatus = ::success;

         return;

         // return pimage->m_estatus;

      }
      
      int w = 0;

      int h = 0;

      int iScan = 0;

      ::acme::malloc < image32_t * > pimage32;

      pimage32 = file_memory_to_image_data(w, h, iScan, memory.data(), memory.size());
      
      if(pimage32 == nullptr)
      {
         
         pimage->set_nok();

         pimage->m_estatus = ::error_failed;

         return;

      }
      
      pimage->create({w, h});
      
      pimage->map();
      
      pimage->image32()->vertical_swap_copy(w, h, pimage->scan_size(), pimage32, iScan);
      
      pimage->set_ok_flag();
      
      //return true;

   }


} // namespace coreimage_imaging


//void * cg_image_get_image_data(int & width, int & height, int & iScan, CGImageRef image)
//{
//
//   if(image == nullptr)
//   {
//
//      return nullptr;
//
//   }
//
//   //https://www.raywenderlich.com/69855/image-processing-in-ios-part-1-raw-bitmap-modification
//   // 1.
//   width = (int) CGImageGetWidth(image);
//   height = (int) CGImageGetHeight(image);
//
//   // 2.
//   long bytesPerPixel = 4;
//   long bytesPerRow = bytesPerPixel * width;
//   long bitsPerComponent = 8;
//
//   unsigned int * pixels;
//   pixels = (unsigned int *) calloc(height * width, sizeof(unsigned int));
//   
//   iScan = width * sizeof(unsigned int);
//
//   // 3.
//   CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
//   CGContextRef context = CGBitmapContextCreate(pixels, width, height, bitsPerComponent, bytesPerRow, colorSpace,
//                                                kCGImageAlphaPremultipliedLast);///kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
//
//   // 4.
//   CGContextDrawImage(context, CGRectMake(0, 0, width, height), image);
//
//   // 5. Cleanup
//   CGColorSpaceRelease(colorSpace);
//
//   CGContextRelease(context);
//
//   return pixels;
//
//}




