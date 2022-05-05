//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"


void os_post_quit();


void ansios_sigchld_handler(int sig);


void apex_application_run(const char * pszAppName, const char * pszProgName);


bool ns_open_file(const char * psz);


namespace acme
{


   namespace apple
   {


      node::node()
      {

         m_pAcmePosix = this;

      }


      node::~node()
      {

      }


      int node::node_init_check(int * pi, char *** ppz)
      {

         return 0;

      }


      void node::initialize(::object * pobject)
      {

         ::acme::node::initialize(pobject);

      }


      void node::install_sigchld_handler()
      {


      }
   
   
      string node::audio_get_default_library_name()
      {

         return "audio_core_audio";

      }

   
      string node::multimedia_audio_mixer_get_default_library_name()
      {

         return "audio_mixer_core_audio";

      }
   
   
      string node::veriwell_multimedia_music_midi_get_default_library_name()
      {

         return "music_midi_core_midi";

      }
   
   
      void node::node_post(const ::procedure & routineParam)
      {
         
         auto routine = routineParam;
         
         ns_main_async(^{
            
            try
            {
               
               routine();
               
            }
            catch (...)
            {
            
            }
            
         });

         //return ::success;

      }

   
      void node::shell_open(const ::file::path & path, const ::string & strParams, const ::file::path & pathFolder)
      {
         
         ns_open_file(path);

      }


   } // namespace apple


} // namespace acme





CGContextRef CreateARGBBitmapContext (CGImageRef inImage, int cx, int cy)
{

   CGContextRef    context = nullptr;

   CGColorSpaceRef colorSpace;

   //void *          bitmapData;

   int             bitmapByteCount;

   int             bitmapBytesPerRow;

   bitmapBytesPerRow   = (cx * 4);

   bitmapByteCount     = (bitmapBytesPerRow * cy);

   colorSpace = CGColorSpaceCreateDeviceRGB();

   if (colorSpace == nullptr)
   {

      output_debug_string("CreateARGBBitmapContext: Error allocating color space\n");

      return nullptr;

   }

   //   bitmapData = malloc( bitmapByteCount );
   //
   //   if (bitmapData == nullptr)
   //   {
   //
   //      output_debug_string("CreateARGBBitmapContext: Memory not allocated!");
   //
   //      CGColorSpaceRelease( colorSpace );
   //
   //      return nullptr;
   //
   //   }
   //
   //   __memset(bitmapData, 0, bitmapByteCount);

   // Create the bitmap context. We want pre-multiplied argb, 8-bits
   // per component. Regardless of what the source image format is
   // (CMYK, Grayscale, and so on) it will be converted over to the format
   // specified here by CGBitmapContextCreate.
   context =
   CGBitmapContextCreate (
   nullptr,
   cx,
   cy,
   8,
   bitmapBytesPerRow,
   colorSpace,
   kCGImageAlphaPremultipliedLast);

   //   if (context == nullptr)
   //   {
   //
   //      free (bitmapData);
   //
   //      output_debug_string("CreateARGBBitmapContext: Context not created!");
   //
   //   }

   CGColorSpaceRelease( colorSpace );

   return context;
}




bool GetImagePixelData(unsigned int * pcr, int cx, int cy, int iScan, CGImageRef inImage)
{

   CGContextRef cgctx = CreateARGBBitmapContext(inImage, cx, cy);

   if (cgctx == nullptr)
   {

      return false;

   }

   CGRect rectangle = {{0,0},{(CGFloat)cx,(CGFloat)cy}};

   CGContextDrawImage(cgctx, rectangle, inImage);

   void *data = CGBitmapContextGetData (cgctx);

   u8 * pdest = (u8 * ) pcr;

   if (data != nullptr)
   {

      for(int y = cy - 1; y >= 0; y--)
      {

         u8 * pline = (u8 *) &((unsigned int*)data)[y * cx];

         ::memcpy_dup(pdest, pline, cx* 4);

         pdest += iScan;

      }

   }

   CGContextRelease(cgctx);

   return data != nullptr;

}

