// Created by camilo on 2026-01-06 21:18 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "typeface.h"
//#include <fontconfig/fontconfig.h>
#include <CoreText/CoreText.h>
#include <CoreFoundation/CoreFoundation.h>


namespace typeface_quartz2d
{


   typeface::typeface()
   {

   }


   typeface::~typeface()
   {


   }



::file::path typeface::_get_font_file_path_by_font_name(const ::scoped_string &scopedstrFontName)
{
   ::file::path path;

   CFStringRef cfFontName =
      CFStringCreateWithCString(
         kCFAllocatorDefault,
         scopedstrFontName.c_str(),
         kCFStringEncodingUTF8);

   if (!cfFontName)
      return path;

   // Create descriptor from PostScript or display name
   CTFontDescriptorRef desc =
      CTFontDescriptorCreateWithNameAndSize(cfFontName, 0.0);

   CFRelease(cfFontName);

   if (!desc)
      return path;

   // Create actual font
   CTFontRef font = CTFontCreateWithFontDescriptor(desc, 0.0, nullptr);
   CFRelease(desc);

   if (!font)
      return path;

   // Get file URL
   CFURLRef url =
      (CFURLRef)CTFontCopyAttribute(font, kCTFontURLAttribute);

   CFRelease(font);

   if (!url)
      return path;

   char buffer[PATH_MAX];
   if (CFURLGetFileSystemRepresentation(url, true,
                                        (UInt8 *)buffer,
                                        sizeof(buffer)))
   {
      path = buffer;
   }

   CFRelease(url);
   return path;
}


} // namespace typeface_fontconfig


