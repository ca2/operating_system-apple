// Create on 2021-03-22 09:12 <3ThomasBS_ // at Linux(Question)
// Recreated on 2021-05-16 15:07 <3ThomasBS_ // for macOS
// From windowing_ios by camilo on 2022-05-11 06:19 PM <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "path_system.h"

//enum
//{
//   e_anonymouse_enum,
//   
//};
//typedef UInt16 UniChar;
//inline int operator -(UniChar ush, decltype(e_anonymouse_enum) e) { return ush - (int) e; }
//#include <Carbon/Carbon.h>


string apple_app_module_path();
enum_status ns_create_alias(const char * pszLink, const char * pszSource);
enum_status ns_symbolic_link_destination(char ** ppszDestination, const char * pszLink);

namespace acme_apple
{


   
   path_system::path_system()
   {

      //m_pplatformpath = this;

   }


   path_system::~path_system()
   {


   }


//   ::file::path path_system::app_module()
//   {
//
//      ::file::path path = apple_app_module_path();
//
//      return path;
//
//   }
//


//   void path_system::create_symbolic_link(const char * pszLink, const char * pszSource)
//   {
//
//      if(!ns_create_alias(pszLink, pszSource))
//      {
//
//         throw ::exception(error_failed);
//
//      }
//
//      //return success;
//
//   }
//
//
//   bool path_system::is_symbolic_link(const char * pszLink)
//   {
//
//      auto estatus = ns_symbolic_link_destination(nullptr, pszLink);
//
//      if(!estatus)
//      {
//
//         return estatus;
//
//      }
//
//      return estatus;
//
//   }
//
//
//   ::file::path path_system::symbolic_link_destination(const char * pszLink)
//   {
//
//      string strDestination;
//
//      char * pszDestination = nullptr;
//
//      auto estatus = ns_symbolic_link_destination(&pszDestination, pszLink);
//
//      strDestination = ::string_from_strdup(pszDestination);
//
//      if(!estatus)
//      {
//
//         return "";
//
//      }
//
//      return strDestination;
//
//   }
//
//
//   bool path_system::has_custom_icon(const char * path)
//   {
//
////      FSRef ref;
////
////      FSCatalogInfo info = {};
////
////      //path = (const UInt8 *)[path fileSystemRepresentation]
////
////#pragma clang diagnostic push
////#pragma clang diagnostic ignored "-Wdeprecated-declarations"
////      if (FSPathMakeRef((const UInt8 *) path, &ref, NULL) == noErr)
////#pragma clang diagnostic pop
////      {
////
////#pragma clang diagnostic push
////#pragma clang diagnostic ignored "-Wdeprecated-declarations"
////         if (FSGetCatalogInfo(&ref, kFSCatInfoFinderInfo, &info, NULL, NULL, NULL) == noErr)
////#pragma clang diagnostic pop
////         {
////
////            FileInfo *fileInfo = (FileInfo *)(&info.finderInfo);
////
////            if(fileInfo->finderFlags & kHasCustomIcon)
////            {
////
////               return true;
////
////            }
////
////         }
////
////      }
//
//      return false;
//
//   }


} // namespace acme_apple



